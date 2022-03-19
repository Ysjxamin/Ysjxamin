################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CODE/button.c \
../CODE/buzzer.c \
../CODE/display.c \
../CODE/elec.c \
../CODE/encoder.c \
../CODE/motor.c \
../CODE/timer_pit.c \
../CODE/ym_control.c \
../CODE/ym_hardware_init.c \
../CODE/ym_kalman.c \
../CODE/ym_test.c 

OBJS += \
./CODE/button.o \
./CODE/buzzer.o \
./CODE/display.o \
./CODE/elec.o \
./CODE/encoder.o \
./CODE/motor.o \
./CODE/timer_pit.o \
./CODE/ym_control.o \
./CODE/ym_hardware_init.o \
./CODE/ym_kalman.o \
./CODE/ym_test.o 

COMPILED_SRCS += \
./CODE/button.src \
./CODE/buzzer.src \
./CODE/display.src \
./CODE/elec.src \
./CODE/encoder.src \
./CODE/motor.src \
./CODE/timer_pit.src \
./CODE/ym_control.src \
./CODE/ym_hardware_init.src \
./CODE/ym_kalman.src \
./CODE/ym_test.src 

C_DEPS += \
./CODE/button.d \
./CODE/buzzer.d \
./CODE/display.d \
./CODE/elec.d \
./CODE/encoder.d \
./CODE/motor.d \
./CODE/timer_pit.d \
./CODE/ym_control.d \
./CODE/ym_hardware_init.d \
./CODE/ym_kalman.d \
./CODE/ym_test.d 


# Each subdirectory must supply rules for building sources it contributes
CODE/%.src: ../CODE/%.c CODE/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fC:/Users/huawei/AURIX-v1.5.4-workspace/Seekfree_TC264_RTThread_Smart_Car_Demo/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

CODE/%.o: ./CODE/%.src CODE/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


