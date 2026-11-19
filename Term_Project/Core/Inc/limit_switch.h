
#ifndef INC_LIMITSWITCH_H_
#define INC_LIMITSWITCH_H_

#include "stm32f4xx_hal.h"

class LimitSwitch{
public:
	LimitSwitch(GPIO_TypeDef *port, uint16_t pin, bool active_low = true);
	void init();
	void clean();
	void read()

	bool get() const {return state_;}
	bool latched() const {return latched_;}

private:

	GPIO_TypeDef *port_;
	uint16_t pin_;
	bool active_low_;
	bool state_ =false;
	bool latched_ = false;
};

#endif
