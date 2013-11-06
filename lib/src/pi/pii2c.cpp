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
		uint8_t error;
		error = bus->read_register(reg, (char *) (void *) &result, 1);
		if (errorCode) {
			*errorCode = error;
		}
		_releaseBus();
		return result;
	}
	
	uint16_t I2C_Device::read_reg_word(const char reg, uint8_t *errorCode) const
	{
		_lockBus();
		uint16_t result;
		uint8_t error;
		error = bus->read_register(reg, (char *) (void *) &result, 2);
		if (errorCode) {
			*errorCode = error;
		}
		_releaseBus();
		return result;
	}
	
	uint32_t I2C_Device::read_reg_dword(const char reg, uint8_t *errorCode) const
	{
		_lockBus();
		uint32_t result;
		uint8_t error;
		error = bus->read_register(reg, (char *) (void *) &result, 4);
		if (errorCode) {
			*errorCode = error;
		}
		_releaseBus();
		return result;
	}
	
	uint8_t I2C_Device::read_reg_byte_rs(const char reg, uint8_t *errorCode) const
	{
		_lockBus();
		uint8_t result;
		uint8_t error;
		error = bus->read_register_rs(reg, (char *) (void *) &result, 1);
		if (errorCode) {
			*errorCode = error;
		}
		_releaseBus();
		return result;
	}
	
	uint16_t I2C_Device::read_reg_word_rs(const char reg, uint8_t *errorCode) const
	{
		_lockBus();
		uint16_t result;
		uint8_t error;
		error = bus->read_register_rs(reg, (char *) (void *) &result, 2);
		if (errorCode) {
			*errorCode = error;
		}
		_releaseBus();
		return result;
	}
	
	uint32_t I2C_Device::read_reg_dword_rs(const char reg, uint8_t *errorCode) const
	{
		_lockBus();
		uint32_t result;
		uint8_t error;
		error = bus->read_register_rs(reg, (char *) (void *) &result, 4);
		if (errorCode) {
			*errorCode = error;
		}
		_releaseBus();
		return result;
	}
	
	void I2C_Device::write_reg_byte(char reg, uint8_t val, uint8_t *errorCode) const
	{
		_lockBus();
		uint8_t error;
		error = bus->write_register(reg, (char *) (void *) &val, 1);
		if (errorCode) {
			*errorCode = error;
		}
		_releaseBus();
	}
	
	void I2C_Device::write_reg_word(char reg, uint16_t val, uint8_t *errorCode) const
	{
		_lockBus();
		uint8_t error;
		error = bus->write_register(reg, (char *) (void *) &val, 2);
		if (errorCode) {
			*errorCode = error;
		}
		_releaseBus();
	}
	
	void I2C_Device::write_reg_dword(char reg, uint32_t val, uint8_t *errorCode) const
	{
		_lockBus();
		uint8_t error;
		error = bus->write_register(reg, (char *) (void *) &val, 4);
		if (errorCode) {
			*errorCode = error;
		}
		_releaseBus();
	}
	
	
	uint8_t I2C_Device::_changeRegOr_rs(const char reg, const char* maskBuf, const uint32_t len) const
	{
		uint8_t error = 0;
		char *buffer = (char *) calloc(sizeof(*buffer), len);
		if (!buffer) {
			return I2C_REASON_OK+1;
		}
		error = bus->read_register_rs(reg, buffer, len);
		if (error != I2C_REASON_OK) {
			free(buffer);
			return error;
		}
		uint32_t i;
		for(i=0; i<len; ++i) {
			buffer[i] |= maskBuf[i];
		}
		
		error = bus->write_register(reg, buffer, len);
		free(buffer);
		return error;
	}
	
	uint8_t I2C_Device::_changeRegAnd_rs(const char reg, const char* maskBuf, const uint32_t len) const
	{
		uint8_t error = 0;
		char *buffer = (char *) calloc(sizeof(*buffer), len);
		if (!buffer) {
			return I2C_REASON_OK+1;
		}
		error = bus->read_register_rs(reg, buffer, len);
		if (error != I2C_REASON_OK) {
			free(buffer);
			return error;
		}
		uint32_t i;
		for(i=0; i<len; ++i) {
			buffer[i] &= maskBuf[i];
		}
		
		error = bus->write_register(reg, buffer, len);
		free(buffer);
		return error;
	}
	
	uint8_t I2C_Device::_changeRegOr(const char reg, const char* maskBuf, const uint32_t len) const
	{
		uint8_t error = 0;
		char *buffer = (char *) calloc(sizeof(*buffer), len);
		if (!buffer) {
			return I2C_REASON_OK+1;
		}
		error = bus->read_register(reg, buffer, len);
		if (error != I2C_REASON_OK) {
			free(buffer);
			return error;
		}
		uint32_t i;
		for(i=0; i<len; ++i) {
			buffer[i] |= maskBuf[i];
		}
		
		error = bus->write_register(reg, buffer, len);
		free(buffer);
		return error;
	}
	
	uint8_t I2C_Device::_changeRegAnd(const char reg, const char* maskBuf, const uint32_t len) const
	{
		uint8_t error = 0;
		char *buffer = (char *) calloc(sizeof(*buffer), len);
		if (!buffer) {
			return I2C_REASON_OK+1;
		}
		error = bus->read_register(reg, buffer, len);
		if (error != I2C_REASON_OK) {
			free(buffer);
			return error;
		}
		uint32_t i;
		for(i=0; i<len; ++i) {
			buffer[i] &= maskBuf[i];
		}
		
		error = bus->write_register(reg, buffer, len);
		free(buffer);
		return error;
	}
}
