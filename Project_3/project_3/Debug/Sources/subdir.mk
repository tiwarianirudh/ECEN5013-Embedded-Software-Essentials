################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/cbuff.c \
../Sources/main.c \
../Sources/messageint.c \
../Sources/profiler.c \
../Sources/pwm.c \
../Sources/spi.c \
../Sources/uart.c 

OBJS += \
./Sources/cbuff.o \
./Sources/main.o \
./Sources/messageint.o \
./Sources/profiler.o \
./Sources/pwm.o \
./Sources/spi.o \
./Sources/uart.o 

C_DEPS += \
./Sources/cbuff.d \
./Sources/main.d \
./Sources/messageint.d \
./Sources/profiler.d \
./Sources/pwm.d \
./Sources/spi.d \
./Sources/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


