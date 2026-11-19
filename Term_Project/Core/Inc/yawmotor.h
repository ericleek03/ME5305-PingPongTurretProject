/*
 * yawmotor.h
 *
 *  Created on: Nov 17, 2026
 *      Author: poker
 */

#ifndef INC_YAWMOTOR_H_
#define INC_YAWMOTOR_H_

#include "stm32f4xx_hal.h"

class yawmotor{

public:
	yawmotor(TIM_HandleTypeDef *htim, uint32_t fwd_channel, uint32_t rev_channel);
	void init();
	void Motor_Enable();
	void Motor_Disable();
	void Motor_SetDutyCycle(int8_t duty_cycle);


	int8_t dutyCycle() const {return duty_cycle_;} // does not modify constant value being used
	bool Enable() const { return enabled_;} // can't change enable flag

private:
	uint32_t Motor_GetPeriodTicks() const;

	TIM_HandleTypeDef *htim_;
	uint32_t fwd_channel_;
	uint32_t rev_channel_;
	int8_t duty_cycle_ = 0;
	int8_t enabled_ = 0;


};



#endif /* INC_YAWMOTOR_H_ */
