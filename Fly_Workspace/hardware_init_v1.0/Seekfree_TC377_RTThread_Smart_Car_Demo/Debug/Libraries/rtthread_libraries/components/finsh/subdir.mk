################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/rtthread_libraries/components/finsh/cmd.c \
../Libraries/rtthread_libraries/components/finsh/finsh_compiler.c \
../Libraries/rtthread_libraries/components/finsh/finsh_error.c \
../Libraries/rtthread_libraries/components/finsh/finsh_heap.c \
../Libraries/rtthread_libraries/components/finsh/finsh_init.c \
../Libraries/rtthread_libraries/components/finsh/finsh_node.c \
../Libraries/rtthread_libraries/components/finsh/finsh_ops.c \
../Libraries/rtthread_libraries/components/finsh/finsh_parser.c \
../Libraries/rtthread_libraries/components/finsh/finsh_token.c \
../Libraries/rtthread_libraries/components/finsh/finsh_var.c \
../Libraries/rtthread_libraries/components/finsh/finsh_vm.c \
../Libraries/rtthread_libraries/components/finsh/msh.c \
../Libraries/rtthread_libraries/components/finsh/msh_file.c \
../Libraries/rtthread_libraries/components/finsh/shell.c \
../Libraries/rtthread_libraries/components/finsh/symbol.c 

OBJS += \
./Libraries/rtthread_libraries/components/finsh/cmd.o \
./Libraries/rtthread_libraries/components/finsh/finsh_compiler.o \
./Libraries/rtthread_libraries/components/finsh/finsh_error.o \
./Libraries/rtthread_libraries/components/finsh/finsh_heap.o \
./Libraries/rtthread_libraries/components/finsh/finsh_init.o \
./Libraries/rtthread_libraries/components/finsh/finsh_node.o \
./Libraries/rtthread_libraries/components/finsh/finsh_ops.o \
./Libraries/rtthread_libraries/components/finsh/finsh_parser.o \
./Libraries/rtthread_libraries/components/finsh/finsh_token.o \
./Libraries/rtthread_libraries/components/finsh/finsh_var.o \
./Libraries/rtthread_libraries/components/finsh/finsh_vm.o \
./Libraries/rtthread_libraries/components/finsh/msh.o \
./Libraries/rtthread_libraries/components/finsh/msh_file.o \
./Libraries/rtthread_libraries/components/finsh/shell.o \
./Libraries/rtthread_libraries/components/finsh/symbol.o 

COMPILED_SRCS += \
./Libraries/rtthread_libraries/components/finsh/cmd.src \
./Libraries/rtthread_libraries/components/finsh/finsh_compiler.src \
./Libraries/rtthread_libraries/components/finsh/finsh_error.src \
./Libraries/rtthread_libraries/components/finsh/finsh_heap.src \
./Libraries/rtthread_libraries/components/finsh/finsh_init.src \
./Libraries/rtthread_libraries/components/finsh/finsh_node.src \
./Libraries/rtthread_libraries/components/finsh/finsh_ops.src \
./Libraries/rtthread_libraries/components/finsh/finsh_parser.src \
./Libraries/rtthread_libraries/components/finsh/finsh_token.src \
./Libraries/rtthread_libraries/components/finsh/finsh_var.src \
./Libraries/rtthread_libraries/components/finsh/finsh_vm.src \
./Libraries/rtthread_libraries/components/finsh/msh.src \
./Libraries/rtthread_libraries/components/finsh/msh_file.src \
./Libraries/rtthread_libraries/components/finsh/shell.src \
./Libraries/rtthread_libraries/components/finsh/symbol.src 

C_DEPS += \
./Libraries/rtthread_libraries/components/finsh/cmd.d \
./Libraries/rtthread_libraries/components/finsh/finsh_compiler.d \
./Libraries/rtthread_libraries/components/finsh/finsh_error.d \
./Libraries/rtthread_libraries/components/finsh/finsh_heap.d \
./Libraries/rtthread_libraries/components/finsh/finsh_init.d \
./Libraries/rtthread_libraries/components/finsh/finsh_node.d \
./Libraries/rtthread_libraries/components/finsh/finsh_ops.d \
./Libraries/rtthread_libraries/components/finsh/finsh_parser.d \
./Libraries/rtthread_libraries/components/finsh/finsh_token.d \
./Libraries/rtthread_libraries/components/finsh/finsh_var.d \
./Libraries/rtthread_libraries/components/finsh/finsh_vm.d \
./Libraries/rtthread_libraries/components/finsh/msh.d \
./Libraries/rtthread_libraries/components/finsh/msh_file.d \
./Libraries/rtthread_libraries/components/finsh/shell.d \
./Libraries/rtthread_libraries/components/finsh/symbol.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/rtthread_libraries/components/finsh/%.src: ../Libraries/rtthread_libraries/components/finsh/%.c Libraries/rtthread_libraries/components/finsh/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc37x "-fD:/·ÉË¼/AURIX Workspace/Seekfree_TC377_RTThread_Smart_Car_Demo/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

Libraries/rtthread_libraries/components/finsh/%.o: ./Libraries/rtthread_libraries/components/finsh/%.src Libraries/rtthread_libraries/components/finsh/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


