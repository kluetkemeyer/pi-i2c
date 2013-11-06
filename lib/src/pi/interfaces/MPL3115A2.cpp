#include "pi/interfaces/MPL3115A2.hpp"


#define MPL_ADDR 0x60

#define MPL_REG_STATUS 0x00

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
	}
}
