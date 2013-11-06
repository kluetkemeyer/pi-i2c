#include "pi/pibcm2835.hpp"
#include "bcm2835.h"

namespace pi {

	void BCM2835::init() 
	{
		bcm2835_init();
	}

}
