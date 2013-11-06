#ifndef __PI_I2C__H__
#define __PI_I2C__H__
 
#include <stdint.h>

namespace pi {

class I2C_Device
{
	private:
		uint8_t m_addr;
		
	public:
		I2C_Device(uint8_t addr);
		
};

}
#endif
