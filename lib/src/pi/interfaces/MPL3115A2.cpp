#include <cstdio>
#include <unistd.h>
#include "pi/interfaces/MPL3115A2.hpp"

#define MPL_ADDR 0x60

#define MPL_REG_STATUS			 	0x00
#define MPL_REG_OUT_P_MSB           0x01
#define MPL_REG_OUT_P_CSB           0x02
#define MPL_REG_OUT_P_LSB           0x03
#define MPL_REG_OUT_T_MSB           0x04
#define MPL_REG_OUT_T_LSB           0x05
#define MPL_REG_WHO_AM_I            0x0C
#define MPL_REG_CTRL_REG1           0x26

#define MPL_CTRL_REG1_SBYB			0x01
#define MPL_CTRL_REG1_OST			0x02
#define MPL_CTRL_REG1_ALT			0x80

#define MPL_OVERSAMPLE_MASK			0b00111000


namespace pi 
{
	namespace interfaces 
	{
	
		MPL3115A2::MPL3115A2(): I2C_Device(MPL_ADDR) 
		{
			init();
		}
		
		MPL3115A2::MPL3115A2(const uint8_t addr): I2C_Device(addr) 
		{ 
			init();
		}
		
		MPL3115A2::~MPL3115A2()
		{
		}
		
		void MPL3115A2::init()
		{
			error = 0x00;
		}
		
		uint8_t MPL3115A2::getStatus()
		{	
			return read_reg_byte(MPL_REG_STATUS, &error);
		}
		
		void MPL3115A2::setActive(uint8_t active)
		{
			_lockBus();
			if (active) {
				char regMask = MPL_CTRL_REG1_SBYB;
				error = _changeRegOr_rs(MPL_REG_CTRL_REG1, &regMask, 1);
			} else {
				char regMask = ~MPL_CTRL_REG1_SBYB;
				error = _changeRegAnd_rs(MPL_REG_CTRL_REG1, &regMask, 1);
			}
			_releaseBus();
		}
		
		uint8_t MPL3115A2::whoAmI()
		{
			return read_reg_byte_rs(MPL_REG_WHO_AM_I, &error);
		}
		
		void MPL3115A2::changeMode(const bool altMode)
		{
			char currentCtrl = 0x00;
			bool isActive = false;
			bool inAltMode = false;
			
			_lockBus();
			bus->read_register_rs(MPL_REG_CTRL_REG1, &currentCtrl, 1);
			inAltMode = currentCtrl & MPL_CTRL_REG1_ALT;
			
			if ((altMode && inAltMode) || (!altMode && !inAltMode)) {
				_releaseBus();
				return;
			}
			
			isActive = currentCtrl & MPL_CTRL_REG1_SBYB;
			if (isActive) {
				_releaseBus();
				fprintf(stderr, "Cannot change mode in activity\n");
				return;
			}
			
			if (altMode) {
				currentCtrl |= MPL_CTRL_REG1_ALT;
			} else {
				currentCtrl &= ~MPL_CTRL_REG1_ALT;
			}
			
			bus->write_register(MPL_REG_CTRL_REG1, &currentCtrl, 1);
			_releaseBus();
		}
		
		void MPL3115A2::readAnyData()
		{
			char ctrl, isAltMode, restoreCtrl;
			int32_t oversample;
			
			_lockBus();
			bus->read_register_rs(MPL_REG_CTRL_REG1, &ctrl, 1);
			_releaseBus();
			
			isAltMode = ctrl & MPL_CTRL_REG1_ALT;
			oversample = ctrl & MPL_OVERSAMPLE_MASK;
			restoreCtrl = ctrl & ~MPL_CTRL_REG1_OST; 
			
			oversample >>= 3;
			oversample = (int) (100.5 + oversample * 1000/128);
			
			_lockBus();
			ctrl &= ~MPL_CTRL_REG1_OST;
			bus->write_register(MPL_REG_CTRL_REG1, &ctrl, 1);
			ctrl |= MPL_CTRL_REG1_OST;
			bus->write_register(MPL_REG_CTRL_REG1, &ctrl, 1);
			_releaseBus();
			
			usleep(oversample);
			
			char status;
			do {
				_lockBus();
				bus->read_register_rs(MPL_REG_STATUS, &status, 1);
				_releaseBus();
				
				if (!(status & 0x08))
					usleep(500);
			} while(!(status & 0x08));
			
			
			char data[5];
			_lockBus();
			bus->read_register_rs(MPL_REG_OUT_P_MSB, data, 5);
			_releaseBus();
			
			if (isAltMode)
			{
				setAltitude(data[0], data[1], data[2]);
			}
			else
			{
				setPressure(data[0], data[1], data[2]);
			}
			setTemperature(data[3], data[4]);
		}
		
		void MPL3115A2::readTemperatureAndPressure() 
		{
			changeMode(false);
			readAnyData();
		}
		
		void MPL3115A2::setPressure(const char msb, const char csb, const char lsb)
		{
			float v = 0;
			v = msb << 10;
			v += csb << 2;
			v += (lsb >> 6) & 0b00000011;
			if (lsb & 0x20)
				v += 0.5;
			if (lsb & 0x10)
				v += 0.25;
			
			d_pressure = v;
		}
		
		void MPL3115A2::setTemperature(char msb, const char lsb)
		{
			float v = 0;
			if (msb > 127) {
				v = 0xFFFF & ~msb;
				v += 1;
				v *= -1;
			} else {
				v = msb;
			}
			if (lsb & 0x80)	v += 0.5;
			if (lsb & 0x40)	v += 0.25;
			if (lsb & 0x20)	v += 0.125;
			if (lsb & 0x10)	v += 0.0625;
			
			d_temperature = v;
		} 
		
		void MPL3115A2::setAltitude(char msb, char csb, char lsb) {
			uint16_t rp = (msb << 8) + csb;
			float v = msb > 127
				? -1*(1+(0xffff & ~rp))
				: rp;
			
			if (lsb & 0x80)	v += 0.5;
			if (lsb & 0x40)	v += 0.25;
			if (lsb & 0x20)	v += 0.125;
			if (lsb & 0x10)	v += 0.0625;	
			
			//printf("Alt readings: 0x%02x 0x%02x 0x%02x\n", msb, csb, lsb);
			
			d_altitude = v;
		}
		
		void MPL3115A2::readAltitudeAndPressure()
		{
			changeMode(true);
			readAnyData();
		}
		
		void MPL3115A2::readAllData()
		{
			changeMode(false);
			readAnyData();
			changeMode(true);
			readAnyData();
		}
	}
}
