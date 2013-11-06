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
				
				uint8_t c_gyroScaleRange;
				uint8_t c_accelScaleRange;
				
				int16_t d_gyro[3];
				int16_t d_accel[3];
				float d_temp;
				
				void parseData(int16_t *parsed, char *raw, uint32_t len);				
			protected:
				void setRawGyroData(char *data);
				void setRawAccelData(char *data);
				void setRawTempData(char *data);
				
			public:
				const static uint8_t ACCEL_SCALE_RANGE_2G = 0;
				const static uint8_t ACCEL_SCALE_RANGE_4G = 1;
				const static uint8_t ACCEL_SCALE_RANGE_8G = 2;
				const static uint8_t ACCEL_SCALE_RANGE_16G = 3;
				
				const static uint8_t GYRO_SCALE_RANGE_250 = 0;
				const static uint8_t GYRO_SCALE_RANGE_500 = 1;
				const static uint8_t GYRO_SCALE_RANGE_1000 = 2;
				const static uint8_t GYRO_SCALE_RANGE_2000 = 3;
				
				const static uint32_t AXIS_X = 0;
				const static uint32_t AXIS_Y = 1;
				const static uint32_t AXIS_Z = 2;
				
				
				MPU6050();
				MPU6050(const bool addressBit);
				~MPU6050();
				
				uint8_t getWhoAmI() const;
				
				uint8_t getGyroScaleRange() const { return c_gyroScaleRange; }
				uint8_t getAccelScaleRange() const { return c_accelScaleRange; } 
				
				void setGyroScaleRange(const uint8_t range) { c_gyroScaleRange = range; }
				void setAccelScaleRange(const uint8_t range) { c_accelScaleRange = range; }
				
				void getConfiguration();
				void setConfiguration() const;
				
				uint16_t getRotation(const uint32_t axis) const { return d_gyro[axis]; }
				uint16_t getAcceleration(const uint32_t axis) const { return d_accel[axis]; }
				float getTemperature() const { return d_temp; }
				
				void readRotation();
				void readAcceleration();
				void readTemperature();
				void readAllData();
				
		};
	}
}

#endif
