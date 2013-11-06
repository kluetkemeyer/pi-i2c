#include <stdint.h>
#include <cstdio>
#include "pi/interfaces/MPL3115A2.hpp"

int main(int charc, char **charv) {
	
	pi::interfaces::MPL3115A2 sensor;
	uint8_t status = sensor.getStatus();
	uint8_t error = sensor.getErrorCode();
	
	
	printf("status: 0x%02x [%x]\n", status, error);
	
	sensor.setActive(1);
	
	printf("status: 0x%02x [%x]\n", status, error);

	return 0;
}
