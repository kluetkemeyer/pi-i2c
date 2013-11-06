#ifndef __PI__INTERFACES__MPU6050__H__
#define __PI__INTERFACES__MPU6050__H__

#include "pi/pii2c.hpp"

namespace pi 
{
	namespace interfaces 
	{

		class MPU6050: public I2C_Device
		{
			private:
				void init();
				
			protected:
				
			public:
				MPU6050();
				MPU6050(const bool addressBit);
				~MPU6050();
				
		};
	}
}

#endif
