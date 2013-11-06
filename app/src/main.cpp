#include <bcm2835.h>
#include <cstdio>
#include "pi/pii2c.hpp"

int main(int charc, char **charv) {
	
	pi::I2C_Device *dev = new pi::I2C_Device(0x60);
	uint8_t error = 0;
	uint8_t status = dev->read_reg_byte(0x00, &error);
	
	
	printf("status: 0x%02x [%x]\n", status, error);

	return 0;
}
