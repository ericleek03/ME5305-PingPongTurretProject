// Host-side stand-in for the STM32 HAL used ONLY by the software check.
// Models a timer as a struct holding CCR1-4, CNT and ARR so driver math can run on a PC.
#pragma once
#include <stdint.h>
typedef struct { uint32_t ccr[4]; uint32_t cnt; uint32_t arr; int pwm_on[4]; int enc_on; } TIM_HandleTypeDef;
typedef struct { int dummy; } GPIO_TypeDef;
typedef enum { GPIO_PIN_RESET = 0, GPIO_PIN_SET } GPIO_PinState;
#define TIM_CHANNEL_1 0x00U
#define TIM_CHANNEL_2 0x04U
#define TIM_CHANNEL_3 0x08U
#define TIM_CHANNEL_4 0x0CU
#define TIM_CHANNEL_ALL 0x3CU
#define __HAL_TIM_SET_COMPARE(h,ch,v) ((h)->ccr[(ch)>>2] = (uint32_t)(v))
#define __HAL_TIM_GET_COUNTER(h) ((h)->cnt)
#define __HAL_TIM_SET_COUNTER(h,v) ((h)->cnt = (uint32_t)(v))
#define __HAL_TIM_GET_AUTORELOAD(h) ((h)->arr)
extern uint32_t mock_tick;
extern GPIO_PinState mock_pin;
static inline uint32_t HAL_GetTick(void){ return mock_tick; }
static inline int HAL_TIM_PWM_Start(TIM_HandleTypeDef*h,uint32_t ch){ h->pwm_on[ch>>2]=1; return 0; }
static inline int HAL_TIM_PWM_Stop(TIM_HandleTypeDef*h,uint32_t ch){ h->pwm_on[ch>>2]=0; return 0; }
static inline int HAL_TIM_Encoder_Start(TIM_HandleTypeDef*h,uint32_t){ h->enc_on=1; return 0; }
static inline GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef*,uint16_t){ return mock_pin; }
