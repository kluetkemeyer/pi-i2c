
#include "pi/interfaces/MPU6050.hpp"
#include "pi/pii2c.hpp"

#define MPU_ADDR 				0x68

namespace pi
{
	namespace interfaces
	{
	
	
		void MPU6050::init()
		{
		}
		
		MPU6050::MPU6050(const bool addressBit): 
				I2C_Device(MPU_ADDR + (addressBit ? 1 : 0))
		{
			init();
		}
		
		MPU6050::MPU6050():
				I2C_Device(MPU_ADDR)
		{
			init();
		}
		
		MPU6050::~MPU6050()
		{
		}
		
	}
	
}
