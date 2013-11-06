#include <stdint.h>
#include <cstdio>
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
	
	sensor.readTemperatureAndPressure();

	return 0;
}
