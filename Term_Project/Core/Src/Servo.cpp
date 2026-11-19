/*
 * Servo.cpp
 *
 *  Created on: Nov 12, 2026
 *      Author: poker
 *
 *  Timer must run with a 1 us tick and 20 ms period (PSC = 95, ARR = 19999
 *  at a 96 MHz timer clock) so the compare value is the pulse width in us.
 */
#include "Servo.h"

Servo::Servo(TIM_HandleTypeDef* htim, uint32_t channel, uint16_t minAngle, uint16_t maxAngle)
	: htim_(htim), channel_(channel), minAngle_(minAngle), maxAngle_(maxAngle),
	  pulseUs_(1000), currentAngle_(0) {}

void Servo::start(){
	write(minAngle_);                 // gate closed before the PWM output turns on
	HAL_TIM_PWM_Start(htim_, channel_);
}

void Servo::write(uint16_t angle){
	if (angle < minAngle_){
		angle = minAngle_;
	}
	else if (angle > maxAngle_){
		angle = maxAngle_;
	}
	currentAngle_ = angle;

	pulseUs_ = 1000U + ((uint32_t)angle * 1000U) / 180U;
	__HAL_TIM_SET_COMPARE(htim_, channel_, pulseUs_);
}

uint16_t Servo::getAngle() const{
	return currentAngle_;
}
