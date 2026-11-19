/*
 * BLDCMotor.h
 *
 *  Created on: Nov 12, 2026
 *      Author: poker
 */


#ifndef INC_BLDCMOTOR_H_
#define INC_BLDCMOTOR_H_

#include "stm32f4xx_hal.h"

class BLDCMotor{
public:
	BLDCMotor(TIM_HandleTypeDef* htim, uint32_t channel, uint16_t minPulse = 1000, uint16_t maxPulse = 2000);
	void start();
	void arm();
	void setThrottle(uint8_t percent);
	void setPulseWidth(uint16_t pulseUs);
	void stop();

	// Non-blocking arm check: true once the ESC has seen min pulse for ARM_TIME_MS.
	bool isArmed() const;
	uint16_t pulseWidth() const { return _pulseUs; }

	static const uint32_t ARM_TIME_MS = 2000;  // provisional, BLHeli_S arming wait


private:
	TIM_HandleTypeDef* _htim;
	uint32_t _channel;

	uint16_t _minPulse;
	uint16_t _maxPulse;
	uint16_t _pulseUs;
	uint32_t _armStartMs;
	bool _armStarted;

};



#endif /* INC_BLDCMOTOR_H_ */
