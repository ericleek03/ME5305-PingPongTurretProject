/*
 * yawmotor.cpp
 *
 *  Created on: Nov 17, 2026
 *      Author: poker
 */

#include "yawmotor.h"



yawmotor::yawmotor(TIM_HandleTypeDef *htim, uint32_t fwd_channel, uint32_t rev_channel)
    : htim_(htim), fwd_channel_(fwd_channel), rev_channel_(rev_channel)
{}

void yawmotor::init(){
//	motor->htim = htim;
//	motor->fwd_channel = fwd_channel;
//	motor->rev_channel = rev_channel;
//	motor->duty_cycle = 0;
//	motor->enabled = 0;

	    /* Force a known, safe starting state: both channels at 0% duty
	     * (Stop mode: IN1 = IN2 = L) before anything is ever enabled. */
	__HAL_TIM_SET_COMPARE(htim_, fwd_channel_, 0);
	__HAL_TIM_SET_COMPARE(htim_, rev_channel_, 0);
	duty_cycle_ = 0;
	enabled_ = 0;
}



uint32_t yawmotor::Motor_GetPeriodTicks() const
{
    return __HAL_TIM_GET_AUTORELOAD(htim_) + 1U;
}

/*void motor::Motor_Init(Motor_HandleTypeDef *motor, TIM_HandleTypeDef *htim,
                 uint32_t fwd_channel, uint32_t rev_channel)
{
    motor->htim = htim;
    motor->fwd_channel = fwd_channel;
    motor->rev_channel = rev_channel;
    motor->duty_cycle = 0;
    motor->enabled = 0;

      //Force a known, safe starting state: both channels at 0% duty
     // (Stop mode: IN1 = IN2 = L) before anything is ever enabled.
    __HAL_TIM_SET_COMPARE(motor->htim, motor->fwd_channel, 0);
    __HAL_TIM_SET_COMPARE(motor->htim, motor->rev_channel, 0);
}*/

void yawmotor::Motor_Enable()
{
    HAL_TIM_PWM_Start(htim_, fwd_channel_);
    HAL_TIM_PWM_Start(htim_, rev_channel_);
    enabled_ = 1;
}

void yawmotor::Motor_Disable()
{
    /* Zero the duty first so there's no glitch on the way down, then
     * stop generating PWM on both channels entirely. */
    __HAL_TIM_SET_COMPARE(htim_, fwd_channel_, 0);
    __HAL_TIM_SET_COMPARE(htim_, rev_channel_, 0);

    HAL_TIM_PWM_Stop(htim_, fwd_channel_);
    HAL_TIM_PWM_Stop(htim_, rev_channel_);

    duty_cycle_ = 0;
    enabled_ = 0;
}

void yawmotor::Motor_SetDutyCycle(int8_t duty_cycle)
{
    /* Clamp to the valid range used by the "Mnxy" command format. */
    if (duty_cycle > 100) {
        duty_cycle = 100;
    } else if (duty_cycle < -100) {
        duty_cycle = -100;
    }

    duty_cycle_ = duty_cycle;

    uint32_t period = Motor_GetPeriodTicks();
    uint32_t magnitude = (duty_cycle < 0) ? (uint32_t)(-duty_cycle)
                                           : (uint32_t)duty_cycle;
    uint32_t pulse = (magnitude * period) / 100U;

    if (duty_cycle >= 0) {
        /* Forward: IN1 pulsed at the commanded duty, IN2 held low. */
        __HAL_TIM_SET_COMPARE(htim_, fwd_channel_, pulse);
        __HAL_TIM_SET_COMPARE(htim_, rev_channel_, 0);
    } else {
        /* Reverse: IN2 pulsed at the commanded duty, IN1 held low. */
        __HAL_TIM_SET_COMPARE(htim_, fwd_channel_, 0);
        __HAL_TIM_SET_COMPARE(htim_, rev_channel_, pulse);
    }
}
