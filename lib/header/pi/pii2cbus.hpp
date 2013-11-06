#ifndef __PI_I2CBUS__H__
#define __PI_I2CBUS__H__

#include <boost/signals2/mutex.hpp>
#include <stdint.h>
#include "singleton.hpp"

namespace pi
{

	class I2C_Bus: public Singleton <I2C_Bus>
	{
		friend class Singleton <I2C_Bus>;
		public:
			~I2C_Bus();
			
			void blockBus(const uint8_t slaveAddr);
			void unblockBus();
		
			uint8_t read(char *buf, const uint32_t len) const;
			uint8_t read_register(const char reg, char *buf, const uint32_t len) const;
			uint8_t read_register_rs(char reg, char *buf, const uint32_t len) const;
			
			uint8_t write(const char *buf, const uint32_t len) const;
			uint8_t write_register(char reg, const char *buf, const uint32_t len) const;
			
		protected:
			I2C_Bus() { init(); }	
			
		private:
			boost::signals2::mutex bus_lock;
			uint8_t bus_slaveAddr;
			
			void init();
	};
	
}


#endif
