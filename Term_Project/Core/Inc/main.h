/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* application states ---*/

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
extern ADC_HandleTypeDef hadc1;
extern SPI_HandleTypeDef hspi2;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern UART_HandleTypeDef huart1;
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BTN_START_GPIO_EXTI0_Pin GPIO_PIN_0
#define BTN_START_GPIO_EXTI0_GPIO_Port GPIOA
#define E_STOP_SENSE_Pin GPIO_PIN_1
#define E_STOP_SENSE_GPIO_Port GPIOA
#define LIM_A_Pin GPIO_PIN_2
#define LIM_A_GPIO_Port GPIOA
#define LIM_B_Pin GPIO_PIN_3
#define LIM_B_GPIO_Port GPIOA
#define VIN_SENSE_Pin GPIO_PIN_4
#define VIN_SENSE_GPIO_Port GPIOA
#define BEAM_FEED_Pin GPIO_PIN_5
#define BEAM_FEED_GPIO_Port GPIOA
#define ENC_CS3_Pin GPIO_PIN_7
#define ENC_CS3_GPIO_Port GPIOA
#define FW_PWM3_Pin GPIO_PIN_0
#define FW_PWM3_GPIO_Port GPIOB
#define FW_PWM4_Pin GPIO_PIN_1
#define FW_PWM4_GPIO_Port GPIOB
#define ENC_CS1_Pin GPIO_PIN_12
#define ENC_CS1_GPIO_Port GPIOB
#define SERVO_Pin GPIO_PIN_8
#define SERVO_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define YAW_ENC_A_Pin GPIO_PIN_15
#define YAW_ENC_A_GPIO_Port GPIOA
#define YAW_ENC_B_Pin GPIO_PIN_3
#define YAW_ENC_B_GPIO_Port GPIOB
#define FW_PWM1_Pin GPIO_PIN_4
#define FW_PWM1_GPIO_Port GPIOB
#define FW_PWM2_Pin GPIO_PIN_5
#define FW_PWM2_GPIO_Port GPIOB
#define FW_PWM5_Pin GPIO_PIN_6
#define FW_PWM5_GPIO_Port GPIOB
#define FW_PWM6_Pin GPIO_PIN_7
#define FW_PWM6_GPIO_Port GPIOB
#define YAW_IN1_Pin GPIO_PIN_8
#define YAW_IN1_GPIO_Port GPIOB
#define YAW_IN2_Pin GPIO_PIN_9
#define YAW_IN2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
