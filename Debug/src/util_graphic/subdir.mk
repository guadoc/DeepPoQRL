################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/util_graphic/GUI.cpp \
../src/util_graphic/graphic_toolbox.cpp 

OBJS += \
./src/util_graphic/GUI.o \
./src/util_graphic/graphic_toolbox.o 

CPP_DEPS += \
./src/util_graphic/GUI.d \
./src/util_graphic/graphic_toolbox.d 


# Each subdirectory must supply rules for building sources it contributes
src/util_graphic/%.o: ../src/util_graphic/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/micha/workspace/libtorch/include/torch/csrc/api/include -I/usr/include/python3.6m -I"/home/micha/workspace/matplotlib-cpp-master" -I/home/micha/workspace/DeepPoQRL/src -I/usr/include -I"/home/micha/workspace/libtorch/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


