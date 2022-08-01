/*
 * crc16.c
 *
 * Copyright © Weber Stephen Products LLC., 2022 All Rights Reserved No part of this file may be
 * distributed, reproduced, or used by entities other than Stephen Products LLC. without express
 * written permission. All Rights Reserved UNPUBLISHED, LICENSED SOFTWARE IS CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Weber Stephen Products LLC.
 *
 *  Created on: July 28, 2022
 *  	Author: Bold Erdene Chinbat
 */

// Local includes
#include <tofSensor.h>
#include "main.h"

static bool dataReady;
VL53L4CD_ResultsData_t results; /* Results data from VL53L4CD */

void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == TOF_HARDWARE_INTERRUPT_Pin) {
    	dataReady = true;
    }
}

// Sensor init function
void tofInit(void) {
    /* Toggle Xshut pin to reset the sensor */

	// Turn OFF sensor
    HAL_GPIO_WritePin(GPIOA, TOF_XSHUT_Pin, GPIO_PIN_RESET);
    HAL_Delay(5);

    // Turn ON sensor
    HAL_GPIO_WritePin(GPIOA, TOF_XSHUT_Pin, GPIO_PIN_SET);
    HAL_Delay(5);

    VL53L4CD_SensorInit(SENSOR_ADDRESS);

    /* Program the highest possible TimingBudget, without enabling the
     * low power mode. This should give the best accuracy */
    VL53L4CD_SetRangeTiming(SENSOR_ADDRESS, 200, 0);

    VL53L4CD_StartRanging(SENSOR_ADDRESS);
}

// This function is called from main loop
void tofTask(void) {
    if (dataReady) {
    	dataReady = false;

        /* Read measured distance. RangeStatus = 0 means valid data */
        VL53L4CD_GetResult(SENSOR_ADDRESS, &results);
#ifdef DEBUG_STATE
        printf("Distance = %5umm\n", results.distance_mm);
#endif

        /* (Mandatory) Clear HW interrupt to restart measurements */
        VL53L4CD_ClearInterrupt(SENSOR_ADDRESS);
    }
}

// Function to get Sensor readings
uint16_t tofGetDistance(void) {
	return results.distance_mm;
}
