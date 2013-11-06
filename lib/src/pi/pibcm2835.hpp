#ifndef __PI_BCM2835__H__
#define __PI_BCM2835__H__

#include "singleton.hpp"

namespace pi {

	class BCM2835 : public Singleton <BCM2835> 
	{
		friend class Singleton <BCM2835>;
		
		public:
			~BCM2835() { }
		
		protected:
			BCM2835() { init(); }
			
		private:
			void init();
	};

}

#endif
