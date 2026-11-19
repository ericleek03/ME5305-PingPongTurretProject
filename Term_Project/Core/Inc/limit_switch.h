#ifndef INC_LIMIT_SWITCH_H_
#define INC_LIMIT_SWITCH_H_

#include "stm32f4xx_hal.h"

// Active-low limit switch (Rev 1F: LIM_A = PA2, LIM_B = PA3, 10k pull-up + 1 ms RC).
// GPIO mode/pull is set by CubeMX in MX_GPIO_Init(); this class only reads it.
class LimitSwitch{
public:
	LimitSwitch(GPIO_TypeDef *port, uint16_t pin, bool activeLow = true);

	void read(void);                          // poll the pin and update the state
	bool get(void) const {return _state;}     // true = switch pressed
	void EXTI_Callback(void);                 // call from HAL_GPIO_EXTI_Callback if EXTI is used

private:
	GPIO_TypeDef *_port;
	uint16_t _pin;
	bool _activeLow;
	volatile bool _state;
};

#endif /* INC_LIMIT_SWITCH_H_ */
