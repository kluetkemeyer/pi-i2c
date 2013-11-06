#ifndef __PI_I2C__H__
#define __PI_I2C__H__
 
#include <stdint.h>
#include "pi/pii2cbus.hpp"

namespace pi 
{

	class I2C_Device
	{
		private:
			uint8_t m_addr;
			I2C_Bus *bus;
			
		public:
			I2C_Device(uint8_t addr);
			uint8_t getSlaveAddress() const { return m_addr; }
			
	};

}
#endif
