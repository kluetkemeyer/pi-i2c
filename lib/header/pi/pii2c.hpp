#ifndef __PI_I2C__H__
#define __PI_I2C__H__
 
#include <stdint.h>
#include "pi/pii2cbus.hpp"
#include <bcm2835.h>

namespace pi 
{

	class I2C_Device
	{
		private:
			const uint8_t m_addr;
			
		protected:
			I2C_Bus *bus;
			void _lockBus() const;
			void _releaseBus() const;
			
		public:
			static const uint8_t I2C_REASON_OK = BCM2835_I2C_REASON_OK;
			
			I2C_Device(uint8_t addr);
			uint8_t getSlaveAddress() const { return m_addr; }

			uint8_t read_reg_byte(const char reg, uint8_t *errorCode) const;
			uint16_t read_reg_word(const char reg, uint8_t *errorCode) const;
			uint32_t read_reg_dword(const char reg, uint8_t *errorCode) const;
			uint8_t read_reg_byte_rs(const char reg, uint8_t *errorCode) const;
			uint16_t read_reg_word_rs(const char reg, uint8_t *errorCode) const;
			uint32_t read_reg_dword_rs(const char reg, uint8_t *errorCode) const;
			
			void write_reg_byte(char reg, uint8_t val, uint8_t *errorCode) const;
			void write_reg_word(char reg, uint16_t val, uint8_t *errorCode) const;
			void write_reg_dword(char reg, uint32_t val, uint8_t *errorCode) const;
	};

}
#endif
