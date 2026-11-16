/*
 * BLDCMotor.cpp
 *
 *  Created on: Nov 12, 2026
 *      Author: poker
 */

#include "BLDCMotor.h"

BLDCMotor::BLDCMotor(TIM_HandleTypeDef* htim, uint32_t channel, uint16_t minPulse, uint16_t maxPulse);

void BLDCMotor::start(){
	HAL_TIM_PWM_START(_htim, channel);
	stop();
}


void BLDCMotor::arm(){
	setPulseWidth(_minPulse);
	HAL_Delay(2000); // 2 second delay to arm the ESC
}


void BLDCMotor::setPulseWidth(uint16_t pulseUs){
	if (pulseUs < _minPulse) {pulseUs = minPulse;}
	else if (pulseUs > maxPulse) {pulseUs = maxPulse;}

	__HAL_TIM_SET_COMPARE(_htim, _channel, pulseUs);
}


void BLDC::setThrottle(uint8_t percent){

	if (percent > 100) {percent = 100;}

	uint16_t pulse = _minPulse + ((uint32_t)percent * (_maxPulse -_minPulse))/100;
	setPulseWidth(pulse);
}

void BLDCMotor::stop(){
	setPulseWidth(_minPulse);
}
