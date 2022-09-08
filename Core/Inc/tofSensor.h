/*
 * tofSensor.h
 *
 * Copyright © Weber Stephen Products LLC., 2022 All Rights Reserved No part of this file may be
 * distributed, reproduced, or used by entities other than Stephen Products LLC. without express
 * written permission. All Rights Reserved UNPUBLISHED, LICENSED SOFTWARE IS CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Weber Stephen Products LLC.
 *
 *  Created on: July 28, 2022
 *  	Author: Bold Erdene Chinbat
 */

#ifndef INC_TOFSENSOR_H_
#define INC_TOFSENSOR_H_

#include "main.h"

void tofInit(void);
void tofTask(void);
uint16_t tofGetDistance(void);

#endif /* INC_TOFSENSOR_H_ */
