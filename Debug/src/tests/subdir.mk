################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/tests/graphic_session.cpp \
../src/tests/test_bot_functionalities.cpp \
../src/tests/training_session.cpp 

OBJS += \
./src/tests/graphic_session.o \
./src/tests/test_bot_functionalities.o \
./src/tests/training_session.o 

CPP_DEPS += \
./src/tests/graphic_session.d \
./src/tests/test_bot_functionalities.d \
./src/tests/training_session.d 


# Each subdirectory must supply rules for building sources it contributes
src/tests/%.o: ../src/tests/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/micha/workspace/libtorch/include/torch/csrc/api/include -I/usr/include/python3.6m -I"/home/micha/workspace/matplotlib-cpp-master" -I/home/micha/workspace/DeepPoQRL/src -I/usr/include -I"/home/micha/workspace/libtorch/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


