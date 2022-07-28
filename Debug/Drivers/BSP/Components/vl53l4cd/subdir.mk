################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/vl53l4cd/vl53l4cd.c 

OBJS += \
./Drivers/BSP/Components/vl53l4cd/vl53l4cd.o 

C_DEPS += \
./Drivers/BSP/Components/vl53l4cd/vl53l4cd.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/vl53l4cd/%.o Drivers/BSP/Components/vl53l4cd/%.su: ../Drivers/BSP/Components/vl53l4cd/%.c Drivers/BSP/Components/vl53l4cd/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G030xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I../TOF/App -I../TOF/Target -I../Drivers/BSP/custom -I../Drivers/BSP/Components/vl53l4cd/modules -I../Drivers/BSP/Components/vl53l4cd/porting -I../Drivers/BSP/Components/vl53l4cd -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-vl53l4cd

clean-Drivers-2f-BSP-2f-Components-2f-vl53l4cd:
	-$(RM) ./Drivers/BSP/Components/vl53l4cd/vl53l4cd.d ./Drivers/BSP/Components/vl53l4cd/vl53l4cd.o ./Drivers/BSP/Components/vl53l4cd/vl53l4cd.su

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-vl53l4cd

