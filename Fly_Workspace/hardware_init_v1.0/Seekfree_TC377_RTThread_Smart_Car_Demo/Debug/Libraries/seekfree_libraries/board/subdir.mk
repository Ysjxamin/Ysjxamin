################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/seekfree_libraries/board/board.c 

OBJS += \
./Libraries/seekfree_libraries/board/board.o 

COMPILED_SRCS += \
./Libraries/seekfree_libraries/board/board.src 

C_DEPS += \
./Libraries/seekfree_libraries/board/board.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/seekfree_libraries/board/%.src: ../Libraries/seekfree_libraries/board/%.c Libraries/seekfree_libraries/board/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc37x "-fD:/·ÉË¼/AURIX Workspace/Seekfree_TC377_RTThread_Smart_Car_Demo/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

Libraries/seekfree_libraries/board/%.o: ./Libraries/seekfree_libraries/board/%.src Libraries/seekfree_libraries/board/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


