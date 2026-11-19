#include "limit_switch.h"

LimitSwitch::LimitSwitch(GPIO_TypeDef *port, uint16_t pin, bool activeLow)
	: _port(port), _pin(pin), _activeLow(activeLow), _state(false) {}

void LimitSwitch::read(void){
	GPIO_PinState level = HAL_GPIO_ReadPin(_port, _pin);
	_state = _activeLow ? (level == GPIO_PIN_RESET) : (level == GPIO_PIN_SET);
}

void LimitSwitch::EXTI_Callback(void){
	read();
}
