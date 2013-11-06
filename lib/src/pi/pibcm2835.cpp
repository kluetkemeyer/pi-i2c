#include "pi/pibcm2835.hpp"
#include "bcm2835.h"
#include <unistd.h>
#include <sys/types.h>
#include <cstdio>
#include <cstdlib>

namespace pi {

	void BCM2835::init() 
	{
		uid_t uid = getuid();
		if (uid != 0) {
			fprintf(stderr, "Failed to start IO connection\nForgotten to run the application as root?...\n\n");
			std::exit(1);
		}
		
		bcm2835_init();
	}

}
