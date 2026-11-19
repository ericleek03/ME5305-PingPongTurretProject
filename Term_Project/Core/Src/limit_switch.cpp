/*
 * limit_switch.cpp
 *
 *  Created on: Nov 18, 2026
 *      Author: poker
 */

#include "limit_switch.h"


LimitSwitch::LimitSwitch(GPIO_TypeDef* port, uint16_t pin, bool active_low) : port_(port), pin_(pin), active_low_(active_low){}
bool LimitSwitch::init(){
	GPIO_InitTypeDef cfg = {0};
	cfg.Pin = pin_;
	cfg.Mode = GPIO_MODE_INPUT;
	cfg.Pull = active_low_ ? GPIO_PULLUP : GPIO_PULLDOWN; // found online
	HAL_GPIO_Init(port_, &cfg);

	read();
}



void LimitSwitch::read(){
	bool high = (HAL_GPIO_ReadPin(port_,pin_) == GPIO_PIN_SET);
	state_ = active_low_ ? !high : high;

	if (state_) {
		latched_ = true;
	}

}


void LimitSwitch::clean(){
	latched_ =false;

}
