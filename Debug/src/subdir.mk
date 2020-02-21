################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/PQL.cpp \
../src/toolbox.cpp 

OBJS += \
./src/PQL.o \
./src/toolbox.o 

CPP_DEPS += \
./src/PQL.d \
./src/toolbox.d 


# Each subdirectory must supply rules for building sources it contributes
src/PQL.o: ../src/PQL.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/micha/workspace/libtorch/include/torch/csrc/api/include -I$(ProjectDir) -I/usr/include -I/usr/include/python3.6m -I"/home/micha/workspace/libtorch/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/PQL.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/micha/workspace/libtorch/include/torch/csrc/api/include -I/usr/include/python3.6m -I"/home/micha/workspace/matplotlib-cpp-master" -I/home/micha/workspace/DeepPoQRL/src -I/usr/include -I"/home/micha/workspace/libtorch/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


