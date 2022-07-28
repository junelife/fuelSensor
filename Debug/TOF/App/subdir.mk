################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../TOF/App/app_tof.c 

OBJS += \
./TOF/App/app_tof.o 

C_DEPS += \
./TOF/App/app_tof.d 


# Each subdirectory must supply rules for building sources it contributes
TOF/App/%.o TOF/App/%.su: ../TOF/App/%.c TOF/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G030xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I../TOF/App -I../TOF/Target -I../Drivers/BSP/custom -I../Drivers/BSP/Components/vl53l4cd/modules -I../Drivers/BSP/Components/vl53l4cd/porting -I../Drivers/BSP/Components/vl53l4cd -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-TOF-2f-App

clean-TOF-2f-App:
	-$(RM) ./TOF/App/app_tof.d ./TOF/App/app_tof.o ./TOF/App/app_tof.su

.PHONY: clean-TOF-2f-App

