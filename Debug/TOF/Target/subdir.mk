################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../TOF/Target/app_tof_pin_conf.c \
../TOF/Target/custom_ranging_sensor.c 

OBJS += \
./TOF/Target/app_tof_pin_conf.o \
./TOF/Target/custom_ranging_sensor.o 

C_DEPS += \
./TOF/Target/app_tof_pin_conf.d \
./TOF/Target/custom_ranging_sensor.d 


# Each subdirectory must supply rules for building sources it contributes
TOF/Target/%.o TOF/Target/%.su: ../TOF/Target/%.c TOF/Target/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G030xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I../TOF/App -I../TOF/Target -I../Drivers/BSP/custom -I../Drivers/BSP/Components/vl53l4cd/modules -I../Drivers/BSP/Components/vl53l4cd/porting -I../Drivers/BSP/Components/vl53l4cd -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-TOF-2f-Target

clean-TOF-2f-Target:
	-$(RM) ./TOF/Target/app_tof_pin_conf.d ./TOF/Target/app_tof_pin_conf.o ./TOF/Target/app_tof_pin_conf.su ./TOF/Target/custom_ranging_sensor.d ./TOF/Target/custom_ranging_sensor.o ./TOF/Target/custom_ranging_sensor.su

.PHONY: clean-TOF-2f-Target

