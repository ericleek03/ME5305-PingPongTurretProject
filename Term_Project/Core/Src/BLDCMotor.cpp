/*
 * BLDCMotor.cpp
 *
 *  Created on: Nov 12, 2026
 *      Author: poker
 *
 *  ESC (Readytosky 35A BLHeli_S) driver. Timer must be set up for a 1 us tick
 *  (96 MHz timer clock, PSC = 95) and a 50 Hz frame (ARR = 19999), so the
 *  compare value equals the pulse width in microseconds.
 */

#include "BLDCMotor.h"

BLDCMotor::BLDCMotor(TIM_HandleTypeDef* htim, uint32_t channel, uint16_t minPulse, uint16_t maxPulse)
	: _htim(htim), _channel(channel), _minPulse(minPulse), _maxPulse(maxPulse),
	  _pulseUs(minPulse), _armStartMs(0), _armStarted(false) {}

void BLDCMotor::start(){
	stop();                               // load min pulse before the output turns on
	HAL_TIM_PWM_Start(_htim, _channel);
}

// Starts the arming period. Does not block; poll isArmed() from the ESC task.
void BLDCMotor::arm(){
	setPulseWidth(_minPulse);
	_armStartMs = HAL_GetTick();
	_armStarted = true;
}

bool BLDCMotor::isArmed() const{
	return _armStarted && (HAL_GetTick() - _armStartMs >= ARM_TIME_MS);
}

void BLDCMotor::setPulseWidth(uint16_t pulseUs){
	if (pulseUs < _minPulse) {pulseUs = _minPulse;}
	else if (pulseUs > _maxPulse) {pulseUs = _maxPulse;}

	_pulseUs = pulseUs;
	__HAL_TIM_SET_COMPARE(_htim, _channel, pulseUs);
}

void BLDCMotor::setThrottle(uint8_t percent){
	if (percent > 100) {percent = 100;}
	// Throttle above zero is ignored until the ESC has finished arming.
	if (!isArmed()) {percent = 0;}

	uint16_t pulse = _minPulse + ((uint32_t)percent * (_maxPulse - _minPulse))/100;
	setPulseWidth(pulse);
}

void BLDCMotor::stop(){
	setPulseWidth(_minPulse);
}
