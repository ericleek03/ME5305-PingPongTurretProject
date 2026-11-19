/*
 * Servo.h
 *
 *  Created on: Nov 12, 2026
 *      Author: poker
 */

#ifndef INC_SERVO_H_
#define INC_SERVO_H_

#include "stm32f4xx_hal.h"

class Servo{
public:
	Servo(TIM_HandleTypeDef* htim, uint32_t channel, uint16_t minAngle, uint16_t maxAngle);
	void start();
	void write(uint16_t angle);

	// Angle in degrees (0-180) maps linearly to 1000-2000 us at 50 Hz.
	// SG90 endpoints are provisional until checked on the ball gate.

	uint16_t getAngle() const;
	uint32_t pulseWidth() const { return pulseUs_; }

private:
	TIM_HandleTypeDef* htim_;
	uint32_t channel_;
	uint16_t minAngle_;
	uint16_t maxAngle_;
	uint32_t pulseUs_;
	uint16_t currentAngle_;

};



#endif /* INC_SERVO_H_ */
