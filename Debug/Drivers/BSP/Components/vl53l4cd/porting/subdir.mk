################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/vl53l4cd/porting/platform.c 

OBJS += \
./Drivers/BSP/Components/vl53l4cd/porting/platform.o 

C_DEPS += \
./Drivers/BSP/Components/vl53l4cd/porting/platform.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/vl53l4cd/porting/%.o Drivers/BSP/Components/vl53l4cd/porting/%.su: ../Drivers/BSP/Components/vl53l4cd/porting/%.c Drivers/BSP/Components/vl53l4cd/porting/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G030xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I../TOF/App -I../TOF/Target -I../Drivers/BSP/custom -I../Drivers/BSP/Components/vl53l4cd/modules -I../Drivers/BSP/Components/vl53l4cd/porting -I../Drivers/BSP/Components/vl53l4cd -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-vl53l4cd-2f-porting

clean-Drivers-2f-BSP-2f-Components-2f-vl53l4cd-2f-porting:
	-$(RM) ./Drivers/BSP/Components/vl53l4cd/porting/platform.d ./Drivers/BSP/Components/vl53l4cd/porting/platform.o ./Drivers/BSP/Components/vl53l4cd/porting/platform.su

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-vl53l4cd-2f-porting

