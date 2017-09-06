################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../inc/pwm.c \
../inc/uart.c 

OBJS += \
./inc/pwm.o \
./inc/uart.o 

C_DEPS += \
./inc/pwm.d \
./inc/uart.d 


# Each subdirectory must supply rules for building sources it contributes
inc/%.o: ../inc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -D__LPC17XX__ -D__REDLIB__ -I"C:\Users\Home\Documents\MCUXpressoIDE_10.0.0_344\workspace\CMSIS_CORE_LPC17xx\inc" -I"C:\Users\Home\Documents\MCUXpressoIDE_10.0.0_344\workspace\libLCD\inc" -I"C:\Users\Home\Documents\MCUXpressoIDE_10.0.0_344\workspace\Estacionamiento\inc" -I"C:\Users\Home\Documents\MCUXpressoIDE_10.0.0_344\workspace\lpc_board_nxp_lpcxpresso_1769\inc" -I"C:\Users\Home\Documents\MCUXpressoIDE_10.0.0_344\workspace\lpc_chip_175x_6x\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


