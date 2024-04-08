################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Adc.c \
../src/Adc_PbCfg.c \
../src/Buzzer.c \
../src/Dio.c \
../src/ExtInt.c \
../src/Functions.c \
../src/Gpt.c \
../src/Gpt_PbCfg.c \
../src/Icu.c \
../src/LPM.c \
../src/Led.c \
../src/Pwm.c \
../src/Uart.c \
../src/Wdt.c \
../src/main.c 

OBJS += \
./src/Adc.o \
./src/Adc_PbCfg.o \
./src/Buzzer.o \
./src/Dio.o \
./src/ExtInt.o \
./src/Functions.o \
./src/Gpt.o \
./src/Gpt_PbCfg.o \
./src/Icu.o \
./src/LPM.o \
./src/Led.o \
./src/Pwm.o \
./src/Uart.o \
./src/Wdt.o \
./src/main.o 

C_DEPS += \
./src/Adc.d \
./src/Adc_PbCfg.d \
./src/Buzzer.d \
./src/Dio.d \
./src/ExtInt.d \
./src/Functions.d \
./src/Gpt.d \
./src/Gpt_PbCfg.d \
./src/Icu.d \
./src/LPM.d \
./src/Led.d \
./src/Pwm.d \
./src/Uart.d \
./src/Wdt.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\embedded\EclipseProjects\Mobile_Controlled_Home\inc" -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


