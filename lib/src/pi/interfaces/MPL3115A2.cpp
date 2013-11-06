#include "pi/interfaces/MPL3115A2.hpp"
#include <cstdio>

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
			inAltMode = currentCtrl & MPL_CTRL_REG1_ALT ? true : false;
			
			if (altMode == inAltMode) {
				_releaseBus();
				return;
			}
			
			isActive = currentCtrl & MPL_CTRL_REG1_SBYB;
			if (isActive && altMode != inAltMode) {
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
			
			printf("mode: %i\noversample: %i\n", isAltMode, oversample);
			oversample >>= 3;
			oversample = (int) (100.5 + (1 << oversample) * 1000/128);
			printf("mode: %i\noversample: %i\n", isAltMode, oversample);
			
		}
		
		void MPL3115A2::readTemperatureAndPressure() 
		{
			changeMode(false);
			readAnyData();
		}
	}
}
