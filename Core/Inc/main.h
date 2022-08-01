/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "stm32g0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdbool.h"
#include "VL53L4CD_api.h"
#include <stdio.h>

#define DEBUG_STATE
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define RS485_RECEIVER_EN_Pin GPIO_PIN_14
#define RS485_RECEIVER_EN_GPIO_Port GPIOC
#define RS485_DRIVER_EN_Pin GPIO_PIN_15
#define RS485_DRIVER_EN_GPIO_Port GPIOC
#define AN_BOARD_REV_Pin GPIO_PIN_0
#define AN_BOARD_REV_GPIO_Port GPIOA
#define AN_PERSONALITY_ID_Pin GPIO_PIN_1
#define AN_PERSONALITY_ID_GPIO_Port GPIOA
#define TOF_XSHUT_Pin GPIO_PIN_2
#define TOF_XSHUT_GPIO_Port GPIOA
#define TOF_HARDWARE_INTERRUPT_Pin GPIO_PIN_3
#define TOF_HARDWARE_INTERRUPT_GPIO_Port GPIOA
#define TOF_HARDWARE_INTERRUPT_EXTI_IRQn EXTI2_3_IRQn
#define PWM_RED_Pin GPIO_PIN_6
#define PWM_RED_GPIO_Port GPIOA
#define PWM_GREEN_Pin GPIO_PIN_7
#define PWM_GREEN_GPIO_Port GPIOA
#define PWM_BLUE_Pin GPIO_PIN_0
#define PWM_BLUE_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
#define SENSOR_ADDRESS 0x52
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
