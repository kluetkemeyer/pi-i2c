#include "pi/pibcm2835.hpp"
#include "pi/pii2cbus.hpp"
#include <bcm2835.h>

namespace pi
{

	I2C_Bus::~I2C_Bus() 
	{
	}
	
	void I2C_Bus::init() 
	{
		BCM2835::instance();
		
		bcm2835_i2c_begin();
	}


}
