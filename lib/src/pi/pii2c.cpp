#include "pi/pii2c.hpp"

namespace pi 
{

	I2C_Device::I2C_Device(uint8_t addr): m_addr(addr)
	{
		bus = I2C_Bus::instance();
	}
	
	void I2C_Device::_lockBus() const
	{
		bus->blockBus(m_addr);
	}
	
	void I2C_Device::_releaseBus() const
	{
		bus->unblockBus();
	}

	uint8_t I2C_Device::read_reg_byte(const char reg, uint8_t *errorCode) const
	{
		_lockBus();
		uint8_t result;
		*errorCode = bus->read_register(reg, (char *) (void *) &result, 1);
		_releaseBus();
		return result;
	}
	
	uint16_t I2C_Device::read_reg_word(const char reg, uint8_t *errorCode) const
	{
		_lockBus();
		uint16_t result;
		*errorCode = bus->read_register(reg, (char *) (void *) &result, 2);
		_releaseBus();
		return result;
	}
	
	uint32_t I2C_Device::read_reg_dword(const char reg, uint8_t *errorCode) const
	{
		_lockBus();
		uint32_t result;
		*errorCode = bus->read_register(reg, (char *) (void *) &result, 4);
		_releaseBus();
		return result;
	}
	
	uint8_t I2C_Device::read_reg_byte_rs(const char reg, uint8_t *errorCode) const
	{
		_lockBus();
		uint8_t result;
		*errorCode = bus->read_register_rs(reg, (char *) (void *) &result, 1);
		_releaseBus();
		return result;
	}
	
	uint16_t I2C_Device::read_reg_word_rs(const char reg, uint8_t *errorCode) const
	{
		_lockBus();
		uint16_t result;
		*errorCode = bus->read_register_rs(reg, (char *) (void *) &result, 2);
		_releaseBus();
		return result;
	}
	
	uint32_t I2C_Device::read_reg_dword_rs(const char reg, uint8_t *errorCode) const
	{
		_lockBus();
		uint32_t result;
		*errorCode = bus->read_register_rs(reg, (char *) (void *) &result, 4);
		_releaseBus();
		return result;
	}
	
	void I2C_Device::write_reg_byte(char reg, uint8_t val, uint8_t *errorCode) const
	{
		_lockBus();
		*errorCode = bus->write_register(reg, (char *) (void *) &val, 1);
		_releaseBus();
	}
	
	void I2C_Device::write_reg_word(char reg, uint16_t val, uint8_t *errorCode) const
	{
		_lockBus();
		*errorCode = bus->write_register(reg, (char *) (void *) &val, 2);
		_releaseBus();
	}
	
	void I2C_Device::write_reg_dword(char reg, uint32_t val, uint8_t *errorCode) const
	{
		_lockBus();
		*errorCode = bus->write_register(reg, (char *) (void *) &val, 4);
		_releaseBus();
	}
}
