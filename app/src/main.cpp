#include <stdint.h>
#include <cstdio>
#include <unistd.h>
#include "pi/interfaces/MPL3115A2.hpp"

int main(int charc, char **charv) {
	
	pi::interfaces::MPL3115A2 sensor;
	uint8_t status = sensor.getStatus();
	uint8_t error = sensor.getErrorCode();
	
	uint8_t tmp = sensor.getSlaveAddress();	
	printf("device address:  0x%02x [%u]\n", tmp, tmp);
	
	tmp = sensor.whoAmI();
	printf("device ID:       0x%02x [%u]\n", tmp, tmp);
	
	printf("status: 0x%02x [%x]\n", status, error);
	
	printf("temperature        | pressure\n");
	while(1) {
		sensor.readTemperatureAndPressure();
			
		printf("%18.2f | %18.2f\n", sensor.getTemperature(),
			sensor.getPressure());
			
		usleep(500);
	}
	//printf("temperature:     %.2f\n", sensor.getTemperature());
	//printf("pressure:        %.2f\n", sensor.getPressure());

	return 0;
}
