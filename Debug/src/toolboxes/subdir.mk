################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/toolboxes/toolbox.cpp 

OBJS += \
./src/toolboxes/toolbox.o 

CPP_DEPS += \
./src/toolboxes/toolbox.d 


# Each subdirectory must supply rules for building sources it contributes
src/toolboxes/%.o: ../src/toolboxes/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/micha/workspace/libtorch/include/torch/csrc/api/include -I/home/micha/workspace/DeepPoQRL/src -I/usr/include -I"/home/micha/workspace/libtorch/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


