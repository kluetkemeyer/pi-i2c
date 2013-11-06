#include <stdint.h>
#include <cstdio>
#include <unistd.h>
#include "pi/interfaces/MPU6050.hpp"

int main(int charc, char **charv) {
	
	pi::interfaces::MPU6050 sensor;
	
	printf("i2c slave address:   0x%02x\n", sensor.getSlaveAddress());
	printf("i2c device id:       0x%02x\n", sensor.whoAmI());
	
	sensor.setGyroScaleRange(pi::interfaces::MPU6050::GYRO_SCALE_RANGE_500);
	sensor.setAccelScaleRange(pi::interfaces::MPU6050::ACCEL_SCALE_RANGE_4G);
	sensor.setConfiguration();
	
	
	printf("       ||    x    |    y    |    z    |\n");
	printf("-------++---------+---------+---------+\n");
	printf(" temp. ||         acceleration        |\n");
	printf(" temp. ||           rotation          |\n");       
	while(1) {
		sensor.readAllData();
			
		printf("-------++---------+---------+---------+\n");
		printf(" %5.2f || %7i | %7i | %7i |\n       || %7i | %7i | %7i |\n",
			sensor.getTemperature(),
			sensor.getAcceleration(0), sensor.getAcceleration(1), sensor.getAcceleration(2),
			sensor.getRotation(0), sensor.getRotation(1), sensor.getRotation(2)
		);
			
		usleep(500000);
	}
	
	return 0;
}
