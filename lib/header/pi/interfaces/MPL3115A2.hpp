#ifndef __PI__INTERFACES__MPL3115A2__H__
#define __PI__INTERFACES__MPL3115A2__H__

#include "pi/pii2c.hpp"

namespace pi 
{
	namespace interfaces 
	{

		class MPL3115A2: public I2C_Device
		{
			private:
				uint8_t error;
				void init();
		
			protected:			
				MPL3115A2(uint8_t addr);
				
				void changeMode(const bool altMode);
				void readAnyData();
				
			public:
				MPL3115A2();
				~MPL3115A2();
				
				uint8_t getStatus();
				uint8_t getErrorCode() const { return error; }
				uint8_t whoAmI();
				
				void setActive(uint8_t active);
				void readTemperatureAndPressure();
		};
		
	}
}

#endif
