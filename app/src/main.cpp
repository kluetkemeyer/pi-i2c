#include <bcm2835.h>
#include <cstdio>
#include "pi/pii2c.hpp"

int main(int charc, char **charv) {
	
	uint8_t addr = 0x60;
	
	printf("initializing bcm2835...\n");
	
	bcm2835_init();
	bcm2835_i2c_begin();
	
	pi::I2C_Device *dev = new pi::I2C_Device(addr);
	
	
	bcm2835_i2c_end();

	return 0;
}
