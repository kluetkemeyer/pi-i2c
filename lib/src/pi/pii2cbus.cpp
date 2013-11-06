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
		bus_slaveAddr = 0;
	}

	void I2C_Bus::blockBus(const uint8_t slaveAddr)
	{
		bus_lock.lock();
		if (bus_slaveAddr != slaveAddr) {
			bus_slaveAddr = slaveAddr;
			bcm2835_i2c_setSlaveAddress(slaveAddr);
		}
	}
	
	void I2C_Bus::unblockBus()
	{
		bus_lock.unlock();
	}
	
	uint8_t I2C_Bus::read(char *buf, const uint32_t len) const
	{
		return bcm2835_i2c_read(buf, len);
	}
		
	uint8_t I2C_Bus::read_register(const char reg, char *buf, const uint32_t len) const
	{
		uint8_t status = bcm2835_i2c_write(&reg, 1);
		if (status != BCM2835_I2C_REASON_OK)
		{
			return status;
		}
		return bcm2835_i2c_read(buf, len);
	}
		
	uint8_t I2C_Bus::read_register_rs(char reg, char *buf, const uint32_t len) const
	{
		return bcm2835_i2c_read_register_rs(&reg, buf, len);
	}
	
	uint8_t I2C_Bus::write(const char *buf, const uint32_t len) const
	{
		return bcm2835_i2c_write(buf, len);
	}
	
	uint8_t I2C_Bus::write_register(char reg, const char *buf, const uint32_t len) const
	{
		uint8_t status = bcm2835_i2c_write(&reg, 1);
		if (status != BCM2835_I2C_REASON_OK)
		{
			return status;
		}
		return bcm2835_i2c_write(buf, len);
	}

}
