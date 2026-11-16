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

	//  we want the system to get a get an angle and produce a pulse width at 0 and 2000 us at 180 at 50 hz

	uint16_t getAngle() const;

private:
	TIM_HandleTypeDef* htim_;
	uint32_t channel_;
	uint16_t minAngle_;
	uint16_t maxAngle_;
	uint32_t pulseUs_;
	uint16_t currentAngle_;

};



#endif /* INC_SERVO_H_ */
