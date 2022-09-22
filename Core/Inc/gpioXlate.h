/*
 * gpioXlate.h
 *
 * Copyright © Weber Stephen Products LLC., 2022 All Rights Reserved No part of this file may be
 * distributed, reproduced, or used by entities other than Stephen Products LLC. without express
 * written permission. All Rights Reserved UNPUBLISHED, LICENSED SOFTWARE IS CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Weber Stephen Products LLC.
 *
 *  Created on: July 22, 2022
 *      Author: ronso
 */

#ifndef INC_GPIOXLATE_H_
#define INC_GPIOXLATE_H_


//GPIO USAGE
#define AN_BOARD_REV_GPIO_Port            GPIOA
#define AN_BOARD_REV_Pin                       GPIO_PIN_0
#define AN_PERSONALITY_ID_GPIO_Port       GPIOA
#define AN_PERSONALITY_ID_Pin                  GPIO_PIN_1
#define TOF_XSHUT_GPIO_Port               GPIOA
#define TOF_XSHUT_Pin                          GPIO_PIN_2
#define TOF_HARDWARE_INTERRUPT_GPIO_Port  GPIOA
#define TOF_HARDWARE_INTERRUPT_Pin             GPIO_PIN_3
#define PWM_RED_GPIO_Port                 GPIOA
#define PWM_RED_Pin                            GPIO_PIN_6
#define PWM_GREEN_GPIO_Port               GPIOA
#define PWM_GREEN_Pin                          GPIO_PIN_7
#define RS485_TX_PORT                     GPIOA
#define RS485_TX_PIN                           GPIO_PIN_9
#define RS485_RX_PORT                     GPIOA
#define RS485_RX_PIN                           GPIO_PIN_10
#define PWM_BLUE_GPIO_Port                GPIOB
#define PWM_BLUE_Pin                           GPIO_PIN_0
#define RS485_DE_PORT                     GPIOB
#define RS485_DE_PIN                           GPIO_PIN_3
#define I2C_PORT                          GPIOB
#define I2C_SCL_PIN                            GPIO_PIN_8
#define I2C_SDA_PIN                            GPIO_PIN_9

#define RS485_RECEIVER_EN_GPIO_Port       GPIOC
#define RS485_RECEIVER_EN_Pin                  GPIO_PIN_15



//Interrupt USAGE
#define TOF_HARDWARE_INTERRUPT_EXTI_IRQn EXTI2_3_IRQn




#endif /* INC_GPIOXLATE_H_ */
