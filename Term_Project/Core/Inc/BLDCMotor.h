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


private:
	TIM_HandleTypeDef* _htim;
	uint32_t _channel;

	uint16_t _minPulse;
	uint16_t _maxPulse;

};



#endif /* INC_BLDCMOTOR_H_ */
