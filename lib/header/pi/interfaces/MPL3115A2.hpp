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
				float d_pressure;
				float d_temperature;
				void init();
		
			protected:			
				MPL3115A2(uint8_t addr);
				
				void changeMode(const bool altMode);
				void readAnyData();
				
				void setPressure(char msb, char csb, char lsb);
				void setTemperature(char msb, char lsb);
				
			public:
				MPL3115A2();
				~MPL3115A2();
				
				uint8_t getStatus();
				uint8_t getErrorCode() const { return error; }
				uint8_t whoAmI();
				
				float getPressure() const { return d_pressure; }
				float getTemperature() const { return d_temperature; }
				
				void setActive(uint8_t active);
				void readTemperatureAndPressure();
		};
		
	}
}

#endif
