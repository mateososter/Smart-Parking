################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include inc/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Estacionamiento.axf

# Tool invocations
Estacionamiento.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\Home\Documents\MCUXpressoIDE_10.0.0_344\workspace\CMSIS_CORE_LPC17xx\Debug" -L"C:\Users\Home\Documents\MCUXpressoIDE_10.0.0_344\workspace\libLCD\Debug" -L"C:\Users\Home\Documents\MCUXpressoIDE_10.0.0_344\workspace\lpc_board_nxp_lpcxpresso_1769\Debug" -L"C:\Users\Home\Documents\MCUXpressoIDE_10.0.0_344\workspace\lpc_chip_175x_6x\Debug" -Xlinker -Map="Estacionamiento.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m3 -mthumb -T "Estacionamiento_Debug.ld" -o "Estacionamiento.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) Estacionamiento.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "Estacionamiento.axf"; # arm-none-eabi-objcopy -v -O binary "Estacionamiento.axf" "Estacionamiento.bin" ; # checksum -p LPC1769 -d "Estacionamiento.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
