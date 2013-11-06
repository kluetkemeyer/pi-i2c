#ifndef __PI_I2CBUS__H__
#define __PI_I2CBUS__H__

namespace pi
{

	class I2C_Bus: public Singleton <I2C_Bus>
	{
		friend class Singleton <I2C_Bus>;
		public:
			~I2C_Bus();
		
		protected:
			I2C_Bus() { init(); }	
			
		private:
			void init();
	};
	
}


#endif
