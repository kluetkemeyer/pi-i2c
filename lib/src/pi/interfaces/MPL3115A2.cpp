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
			error = 0;
		}
		
		uint8_t MPL3115A2::getStatus()
		{	
			return read_reg_byte(MPL_REG_STATUS, &error);
		}
		
		int8_t MPL3115A2::setActive(uint8_t active)
		{
			_lockBus();
			uint8_t reg = 0x00;
			error = bus->read_register_rs(MPL_REG_CTRL_REG1, (char*) (void*) &reg, 1);
			if (error != I2C_REASON_OK) {
				_releaseBus();
				return -1;
			}
			
			if (active) {
				reg |= MPL_CTRL_REG1_SBYB;
			} else {
				reg &= ~MPL_CTRL_REG1_SBYB;
			}
			
			error = bus->write_register(MPL_CTRL_REG1_SBYB, (char*) (void*) &reg, 1);
			_releaseBus();
			if (error != I2C_REASON_OK) {
				return -1;
			}
			
			return reg & MPL_CTRL_REG1_SBYB;
		}
	}
}
