#include "pi/pii2c.hpp"

namespace pi 
{

	I2C_Device::I2C_Device(uint8_t addr) 
	{
		m_addr = addr;
		bus = I2C_Bus::instance();
		
	}

}
