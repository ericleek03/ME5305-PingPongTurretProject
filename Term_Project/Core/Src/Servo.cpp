/*
 * Servo.cpp
 *
 *  Created on: Nov 12, 2026
 *      Author: poker
 */
#include "Servo.h"

Servo::Servo(TIM_HandleTypeDef* htim, uint16_t channel, uint16_t minAngle, uint16_t maxAngle) : htim_ (htim), channel_(channel), minAngle_(minAngle), maxAngle_(maxAngle) {}


void Servo::start(){
	HAL_TIM_PWM_Start(htim_, channel_);
}


void Servo::write(uint16_t angle){
	if (angle < minAngle){
		angle = minAngle;
	}
	else if (angle > maxAngle){
		angle = maxAngle;
	}
	currentAngle = angle;

	pulseUs_ = 1000 + (angle * 1000 / 180.0f );
	__HAL_TIM_SET_COMPARE(htim, channel, pulseUs);
}

uint16_t Servo::getAngle() const{
	return currentAngle_;
}

