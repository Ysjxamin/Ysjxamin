################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/rtthread_libraries/src/clock.c \
../Libraries/rtthread_libraries/src/components.c \
../Libraries/rtthread_libraries/src/cpu.c \
../Libraries/rtthread_libraries/src/device.c \
../Libraries/rtthread_libraries/src/idle.c \
../Libraries/rtthread_libraries/src/ipc.c \
../Libraries/rtthread_libraries/src/irq.c \
../Libraries/rtthread_libraries/src/kservice.c \
../Libraries/rtthread_libraries/src/mem.c \
../Libraries/rtthread_libraries/src/memheap.c \
../Libraries/rtthread_libraries/src/mempool.c \
../Libraries/rtthread_libraries/src/object.c \
../Libraries/rtthread_libraries/src/scheduler.c \
../Libraries/rtthread_libraries/src/signal.c \
../Libraries/rtthread_libraries/src/slab.c \
../Libraries/rtthread_libraries/src/thread.c \
../Libraries/rtthread_libraries/src/timer.c 

OBJS += \
./Libraries/rtthread_libraries/src/clock.o \
./Libraries/rtthread_libraries/src/components.o \
./Libraries/rtthread_libraries/src/cpu.o \
./Libraries/rtthread_libraries/src/device.o \
./Libraries/rtthread_libraries/src/idle.o \
./Libraries/rtthread_libraries/src/ipc.o \
./Libraries/rtthread_libraries/src/irq.o \
./Libraries/rtthread_libraries/src/kservice.o \
./Libraries/rtthread_libraries/src/mem.o \
./Libraries/rtthread_libraries/src/memheap.o \
./Libraries/rtthread_libraries/src/mempool.o \
./Libraries/rtthread_libraries/src/object.o \
./Libraries/rtthread_libraries/src/scheduler.o \
./Libraries/rtthread_libraries/src/signal.o \
./Libraries/rtthread_libraries/src/slab.o \
./Libraries/rtthread_libraries/src/thread.o \
./Libraries/rtthread_libraries/src/timer.o 

COMPILED_SRCS += \
./Libraries/rtthread_libraries/src/clock.src \
./Libraries/rtthread_libraries/src/components.src \
./Libraries/rtthread_libraries/src/cpu.src \
./Libraries/rtthread_libraries/src/device.src \
./Libraries/rtthread_libraries/src/idle.src \
./Libraries/rtthread_libraries/src/ipc.src \
./Libraries/rtthread_libraries/src/irq.src \
./Libraries/rtthread_libraries/src/kservice.src \
./Libraries/rtthread_libraries/src/mem.src \
./Libraries/rtthread_libraries/src/memheap.src \
./Libraries/rtthread_libraries/src/mempool.src \
./Libraries/rtthread_libraries/src/object.src \
./Libraries/rtthread_libraries/src/scheduler.src \
./Libraries/rtthread_libraries/src/signal.src \
./Libraries/rtthread_libraries/src/slab.src \
./Libraries/rtthread_libraries/src/thread.src \
./Libraries/rtthread_libraries/src/timer.src 

C_DEPS += \
./Libraries/rtthread_libraries/src/clock.d \
./Libraries/rtthread_libraries/src/components.d \
./Libraries/rtthread_libraries/src/cpu.d \
./Libraries/rtthread_libraries/src/device.d \
./Libraries/rtthread_libraries/src/idle.d \
./Libraries/rtthread_libraries/src/ipc.d \
./Libraries/rtthread_libraries/src/irq.d \
./Libraries/rtthread_libraries/src/kservice.d \
./Libraries/rtthread_libraries/src/mem.d \
./Libraries/rtthread_libraries/src/memheap.d \
./Libraries/rtthread_libraries/src/mempool.d \
./Libraries/rtthread_libraries/src/object.d \
./Libraries/rtthread_libraries/src/scheduler.d \
./Libraries/rtthread_libraries/src/signal.d \
./Libraries/rtthread_libraries/src/slab.d \
./Libraries/rtthread_libraries/src/thread.d \
./Libraries/rtthread_libraries/src/timer.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/rtthread_libraries/src/%.src: ../Libraries/rtthread_libraries/src/%.c Libraries/rtthread_libraries/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fC:/Users/huawei/AURIX-v1.5.4-workspace/Seekfree_TC264_RTThread_Smart_Car_Demo/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

Libraries/rtthread_libraries/src/%.o: ./Libraries/rtthread_libraries/src/%.src Libraries/rtthread_libraries/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


