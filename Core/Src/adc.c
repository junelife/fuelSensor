/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    adc.c
  * @brief   This file provides code for the configuration
  *          of the ADC instances.
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
/* Includes ------------------------------------------------------------------*/
#include "adc.h"

/* USER CODE BEGIN 0 */

/* ADC Local defines
 *
 */
#define ADC_INTERRUPT_SAMPLE_COUNT 16
#define ADC_CHANNEL_COUNT ADC_END_OF_LIST
#define ADC_DMA_FULL_BUFFER_SIZE (ADC_INTERRUPT_SAMPLE_COUNT * ADC_CHANNEL_COUNT * 2)
#define ADC_DMA_HALF_BUFFER_SIZE (ADC_INTERRUPT_SAMPLE_COUNT * ADC_CHANNEL_COUNT)

#define ADC_VREFINT_CAL (*((uint16_t*) 0x1FFF75AA)) /* page. 22/94 --- DS12991 Rev 4 */
#define ADC_VREF 30000

#define ADC_RESOLUTION (4095 * ADC_INTERRUPT_SAMPLE_COUNT)

#define ADC_TS_CAL1 (*((uint16_t*) 0x1FFF75A8)) /* page. 22/94 --- DS12991 Rev 4 */

#define ADC_DECI_MILLI_VOLTAGE (pointerB->voltage = adc[ADC_INTERNAL_VREF].data.voltage * pointerB->raw / ADC_RESOLUTION)

/* ADC interrupts requests work to be done from RR loop
 * Here we defined different work options
 */
typedef enum {
	ADC_JOB_PENDING_NO,
	ADC_JOB_PENDING_FIRST_HALF,
	ADC_JOB_PENDING_SECOND_HALF,
} adcStatePendingToken;

/* ADC pending state
 *
 */
adcStatePendingToken adcPendingWorkState;

/* DMA peripheral defined buffer
 *
 */
uint16_t adc_value[ADC_DMA_FULL_BUFFER_SIZE];

/* ADC local variable Data Type
 *
 */
typedef struct {
	int voltage;
	int temperature;
	uint16_t ripple;
	uint16_t raw;
	uint8_t channel;
	adcStateToken state;
} adcDataType;

/* ADC peripheral related all variables are packets here
 *
 */
static union {
    uint8_t buf[sizeof(adcDataType)];
    adcDataType data;
} adc[ADC_CHANNEL_COUNT];

// Local function prototypes
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hdma_adc1);
void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hdma_adc1);
void ADC_Calculate(adcToken target, uint8_t offset);
void ADC_Sequence(int offset);
/* USER CODE END 0 */

ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

/* ADC1 init function */
void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.ScanConvMode = ADC_SCAN_SEQ_FIXED;
  hadc1.Init.EOCSelection = ADC_EOC_SEQ_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.LowPowerAutoPowerOff = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_EXTERNALTRIG_T1_TRGO2;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
  hadc1.Init.DMAContinuousRequests = ENABLE;
  hadc1.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  hadc1.Init.SamplingTimeCommon1 = ADC_SAMPLETIME_160CYCLES_5;
  hadc1.Init.OversamplingMode = ENABLE;
  hadc1.Init.Oversampling.Ratio = ADC_OVERSAMPLING_RATIO_256;
  hadc1.Init.Oversampling.RightBitShift = ADC_RIGHTBITSHIFT_8;
  hadc1.Init.Oversampling.TriggeredMode = ADC_TRIGGEREDMODE_SINGLE_TRIGGER;
  hadc1.Init.TriggerFrequencyMode = ADC_TRIGGER_FREQ_HIGH;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_1;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_TEMPSENSOR;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_VREFINT;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */
  HAL_ADCEx_Calibration_Start(&hadc1);

  if (HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc_value, ADC_DMA_FULL_BUFFER_SIZE) != HAL_OK) {
      Error_Handler();
  }
  /* USER CODE END ADC1_Init 2 */

}

void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspInit 0 */

  /* USER CODE END ADC1_MspInit 0 */

  /** Initializes the peripherals clocks
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
    PeriphClkInit.AdcClockSelection = RCC_ADCCLKSOURCE_SYSCLK;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    /* ADC1 clock enable */
    __HAL_RCC_ADC_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**ADC1 GPIO Configuration
    PA0     ------> ADC1_IN0
    PA1     ------> ADC1_IN1
    */
    GPIO_InitStruct.Pin = AN_BOARD_REV_Pin|AN_PERSONALITY_ID_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* ADC1 DMA Init */
    /* ADC1 Init */
    hdma_adc1.Instance = DMA1_Channel1;
    hdma_adc1.Init.Request = DMA_REQUEST_ADC1;
    hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;
    hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    hdma_adc1.Init.Mode = DMA_CIRCULAR;
    hdma_adc1.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_adc1) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(adcHandle,DMA_Handle,hdma_adc1);

  /* USER CODE BEGIN ADC1_MspInit 1 */

  /* USER CODE END ADC1_MspInit 1 */
  }
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{

  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspDeInit 0 */

  /* USER CODE END ADC1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC_CLK_DISABLE();

    /**ADC1 GPIO Configuration
    PA0     ------> ADC1_IN0
    PA1     ------> ADC1_IN1
    */
    HAL_GPIO_DeInit(GPIOA, AN_BOARD_REV_Pin|AN_PERSONALITY_ID_Pin);

    /* ADC1 DMA DeInit */
    HAL_DMA_DeInit(adcHandle->DMA_Handle);
  /* USER CODE BEGIN ADC1_MspDeInit 1 */

  /* USER CODE END ADC1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
/* ADC value process routine
 *
 */
void ADC_Calculate(adcToken target, uint8_t offset) {
    uint16_t sum = 0;
    uint16_t min = 4095;
    uint16_t max = 0;

    uint16_t *pointerA = &adc_value[offset + target];
    adcDataType *pointerB = &adc[target].data;

    for (int i = 0; i < ADC_INTERRUPT_SAMPLE_COUNT; i++) {
    	sum += *pointerA;

        if (min > *pointerA) {
        	min = *pointerA;
        }

        if (max < *pointerA) {
        	max = *pointerA;
        }

        pointerA += ADC_CHANNEL_COUNT;
    }
    pointerB->raw = sum;
    pointerB->ripple = max - min;

    switch (target) {
		case ADC_INTERNAL_VREF:
			pointerB->voltage = ADC_VREF * ADC_INTERRUPT_SAMPLE_COUNT * ADC_VREFINT_CAL / pointerB->raw;
			break;
		case ADC_INTERNAL_TEMP:
			// calculate voltage (DECI MILLI voltage)
			ADC_DECI_MILLI_VOLTAGE;

			pointerB->temperature = (pointerB->voltage - ADC_VREF * ADC_TS_CAL1 / 4095)  * 2 / 5 + 300;
			break;
		case ADC_PERSONALITY_ID:
			// calculate voltage (DECI MILLI voltage)
			ADC_DECI_MILLI_VOLTAGE;
			break;
		case ADC_BOARD_REV:
			// calculate voltage (DECI MILLI voltage)
			ADC_DECI_MILLI_VOLTAGE;
			break;
		default:
			Error_Handler();
    }

    if (1) {
		#ifdef DEBUG_STATE
        switch (target) {
			case ADC_INTERNAL_VREF:
				printf("VDDA %ddmV %d\n", pointerB->voltage, pointerB->ripple);
				break;
			case ADC_INTERNAL_TEMP:
				printf("TEMP %ddC %d\n", pointerB->temperature, pointerB->ripple);
				break;
    		case ADC_PERSONALITY_ID:
    			printf("PERSONALITY %ddmV %d\n", pointerB->voltage, pointerB->ripple);
    			break;
			case ADC_BOARD_REV:
				printf("BOARD REV %ddmV %d\n", pointerB->voltage, pointerB->ripple);
				break;
			default:
				Error_Handler();
        }
		#endif
    }
}

/* callback function for DMA, this function called when DMA peripheral fills whole defined buffer.
 * this function is triggered every 2 seconds
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hdma_adc1) {
	if (adcPendingWorkState == ADC_JOB_PENDING_NO) {
		adcPendingWorkState = ADC_JOB_PENDING_SECOND_HALF;
	} else {
		Error_Handler();
	}
}

/* callback function for DMA, this function called when DMA peripheral fills half of defined buffer.
 * this function is triggered every 2 seconds
 */
void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hdma_adc1) {
	if (adcPendingWorkState == ADC_JOB_PENDING_NO) {
		adcPendingWorkState = ADC_JOB_PENDING_FIRST_HALF;
	} else {
		Error_Handler();
	}
}

/* This function configures ADC peripheral channel by channel, Actual peripheral ADC DMA is running on all channel.
 * If no channel is configured main cpu has no load at all because it's all process is in peripheral controller
 */
adcStateToken ADC_Config_Single(adcToken target, adcStateToken state) {
	adc[target].data.state = state;
	return adc[target].data.state;
}

/* This function return last updated value on specific channel (adcToken)
 *
 */
uint16_t ADC_Value_Last_Get(adcToken target) {
	return adc[target].data.raw;
}

/* This function return last updated ripple on specific channel (adcToken)
 *
 */
uint16_t ADC_Ripple_Last_Get(adcToken target) {
	return adc[target].data.ripple;
}

/* This function returns ADC channel state on specific channel
 *
 */
adcStateToken ADC_Status_Single_Get(adcToken target) {
	return adc[target].data.state;
}

/* When ADC data ready by DMA following sequence will run
 *
 */
void ADC_Sequence(int offset) {
	// Following function call sequence is important! Don't change
	ADC_Calculate(ADC_INTERNAL_VREF, offset);
	ADC_Calculate(ADC_INTERNAL_TEMP, offset);
	ADC_Calculate(ADC_BOARD_REV, offset);
	ADC_Calculate(ADC_PERSONALITY_ID, offset);
}

/* ---------------------Round Robin Task Function---------------------
 *
 */
bool ADC_Task(void) {
	if (adcPendingWorkState == ADC_JOB_PENDING_NO) {
		return false;
	}

	if (adcPendingWorkState == ADC_JOB_PENDING_FIRST_HALF) {
		ADC_Sequence(0);
		adcPendingWorkState = ADC_JOB_PENDING_NO;
		return true;
	}

	if (adcPendingWorkState == ADC_JOB_PENDING_SECOND_HALF) {
		ADC_Sequence(ADC_DMA_HALF_BUFFER_SIZE);
		adcPendingWorkState = ADC_JOB_PENDING_NO;
		return true;
	}

	return false;
}
/* USER CODE END 1 */