#include <cstdio>

#include "pi/interfaces/MPU6050.hpp"
#include "pi/pii2c.hpp"

#define MPU_ADDR 						0x68

#define MPU_REG_SELF_TEXT_X				0x0D
#define MPU_REG_SELF_TEXT_Y				0x0E
#define MPU_REG_SELF_TEXT_Z				0x0F
#define MPU_REG_SELF_TEXT_A				0x10
#define MPU_REG_SMPLRT_DIV				0x19
#define MPU_REG_CONFIG					0x1A
#define MPU_REG_GYRO_CONFIG				0x1B
#define MPU_REG_ACCEL_CONFIG			0x1C
#define MPU_REG_FIFO_EN					0x23
#define MPU_REG_I2C_MST_CTRL			0x24
#define MPU_REG_I2C_SLV0_ADDR			0x25
#define MPU_REG_I2C_SLV0_REG			0x26
#define MPU_REG_I2C_SLV0_CTRL			0x27
#define MPU_REG_I2C_SLV1_ADDR			0x28
#define MPU_REG_I2C_SLV1_REG			0x29
#define MPU_REG_I2C_SLV1_CTRL			0x2A
#define MPU_REG_I2C_SLV2_ADDR			0x2B
#define MPU_REG_I2C_SLV2_REG			0x2C
#define MPU_REG_I2C_SLV2_CTRL			0x2D
#define MPU_REG_I2C_SLV3_ADDR			0x2E
#define MPU_REG_I2C_SLV3_REG			0x2F
#define MPU_REG_I2C_SLV3_CTRL			0x30
#define MPU_REG_I2C_SLV4_ADDR			0x31
#define MPU_REG_I2C_SLV4_REG			0x32
#define MPU_REG_I2C_SLV4_DO				0x33
#define MPU_REG_I2C_SLV4_CTRL			0x34
#define MPU_REG_I2C_SLV4_DI				0x35
#define MPU_REG_I2C_MST_STATUS			0x36
#define MPU_REG_INT_PIN_CFG				0x37
#define MPU_REG_INT_ENABLE				0x38
#define MPU_REG_INT_STATUS				0x3A
#define MPU_REG_ACCEL_XOUT_H			0x3B
#define MPU_REG_ACCEL_XOUT_L			0x3C
#define MPU_REG_ACCEL_YOUT_H			0x3D
#define MPU_REG_ACCEL_YOUT_L			0x3E
#define MPU_REG_ACCEL_ZOUT_H			0x3F
#define MPU_REG_ACCEL_ZOUT_L			0x40
#define MPU_REG_TEMP_OUT_H				0x41
#define MPU_REG_TEMP_OUT_L				0x42
#define MPU_REG_GYRO_XOUT_H				0x43
#define MPU_REG_GYRO_XOUT_L				0x44
#define MPU_REG_GYRO_YOUT_H				0x45
#define MPU_REG_GYRO_YOUT_L				0x46
#define MPU_REG_GYRO_ZOUT_H				0x47
#define MPU_REG_GYRO_ZOUT_L				0x48
#define MPU_REG_EXT_SENS_DATA_00		0x49
#define MPU_REG_EXT_SENS_DATA_01		0x4A
#define MPU_REG_EXT_SENS_DATA_02		0x4B
#define MPU_REG_EXT_SENS_DATA_03		0x4C
#define MPU_REG_EXT_SENS_DATA_04		0x4D
#define MPU_REG_EXT_SENS_DATA_05		0x4E
#define MPU_REG_EXT_SENS_DATA_06		0x4F
#define MPU_REG_EXT_SENS_DATA_07		0x50
#define MPU_REG_EXT_SENS_DATA_08		0x51
#define MPU_REG_EXT_SENS_DATA_09		0x52
#define MPU_REG_EXT_SENS_DATA_10		0x53
#define MPU_REG_EXT_SENS_DATA_11		0x54
#define MPU_REG_EXT_SENS_DATA_12		0x55
#define MPU_REG_EXT_SENS_DATA_13		0x56
#define MPU_REG_EXT_SENS_DATA_14		0x57
#define MPU_REG_EXT_SENS_DATA_15		0x58
#define MPU_REG_EXT_SENS_DATA_16		0x59
#define MPU_REG_EXT_SENS_DATA_17		0x5A
#define MPU_REG_EXT_SENS_DATA_18		0x5B
#define MPU_REG_EXT_SENS_DATA_19		0x5C
#define MPU_REG_EXT_SENS_DATA_20		0x5D
#define MPU_REG_EXT_SENS_DATA_21		0x5E
#define MPU_REG_EXT_SENS_DATA_22		0x5F
#define MPU_REG_EXT_SENS_DATA_23		0x60
#define MPU_REG_I2C_SLV0_DO				0x63
#define MPU_REG_I2C_SLV1_DO				0x64
#define MPU_REG_I2C_SLV2_DO				0x65
#define MPU_REG_I2C_SLV3_DO				0x66
#define MPU_REG_I2C_MST_DELAY_CTRL		0x67
#define MPU_REG_SIGNAL_PATH_RESET		0x68
#define MPU_REG_USER_CTRL				0x6A
#define MPU_REG_PWR_MGMT_1				0x6B
#define MPU_REG_PWR_MGMT_2				0x6C
#define MPU_REG_FIFO_COUNTH				0x72
#define MPU_REG_FIFO_COUNTL				0x73
#define MPU_REG_FIFO_R_W				0x74
#define MPU_REG_WHO_AM_I				0x75


namespace pi
{
	namespace interfaces
	{
	
	
		void MPU6050::init()
		{
			c_accelScaleRange = ACCEL_SCALE_RANGE_2G;
		}
		
		MPU6050::MPU6050(const bool addressBit): 
				I2C_Device(MPU_ADDR + (addressBit ? 1 : 0))
		{
			init();
		}
		
		MPU6050::MPU6050():
				I2C_Device(MPU_ADDR)
		{
			init();
		}
		
		MPU6050::~MPU6050()
		{
		}
		
		uint8_t MPU6050::getWhoAmI() const
		{
			return read_reg_byte(MPU_REG_WHO_AM_I, NULL);
		}
		
		void MPU6050::getConfiguration()
		{
		}
		
		void MPU6050::setConfiguration() const
		{
			char config[3];
			
			config[0] = config[1] = config[2] = 0;
			
			
			// gyroscope
			// set range
			config[1] |= (c_gyroScaleRange << 3) & 0b00011000;
			
			// accelerometer
			// set range
			config[2] |= (c_accelScaleRange << 3) & 0b00011000;
			
			
			_lockBus();
			bus->write_register(MPU_REG_CONFIG, config, 3);
			_releaseBus();
		}
		
		void MPU6050::parseData(int16_t *parsed, char *raw, uint32_t len)
		{
			while(len > 0) {
				parsed[0] = raw[0];
				parsed[0] <<= 8;
				parsed[0] |= raw[1];
				
				parsed += 1;
				raw += 2;
				--len;
			}
		}
			
		void MPU6050::readRotation()
		{
			char buffer[6];
			_lockBus();
			bus->read_register(MPU_REG_GYRO_XOUT_H, buffer, 6);
			_releaseBus();
			
			parseData(d_gyro, buffer, 3);
		}
		
		void MPU6050::readAcceleration()
		{
			char buffer[6];
			_lockBus();
			bus->read_register(MPU_REG_ACCEL_XOUT_H, buffer, 6);
			_releaseBus();
			
			parseData(d_accel, buffer, 3);
		}
		
		void MPU6050::readRotationAndAcceleration()
		{
			char buffer[14];
			_lockBus();
			bus->read_register(MPU_REG_ACCEL_XOUT_H, buffer, 14);
			_releaseBus();
			
			parseData(d_accel, buffer, 3);
			parseData(d_gyro, buffer+8, 3);
		}
		
	}
	
}
