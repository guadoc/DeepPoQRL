################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/deck_lib/Card.cpp \
../src/deck_lib/Deck.cpp \
../src/deck_lib/Hand.cpp \
../src/deck_lib/HandTest.cpp \
../src/deck_lib/deck_toolbox.cpp 

OBJS += \
./src/deck_lib/Card.o \
./src/deck_lib/Deck.o \
./src/deck_lib/Hand.o \
./src/deck_lib/HandTest.o \
./src/deck_lib/deck_toolbox.o 

CPP_DEPS += \
./src/deck_lib/Card.d \
./src/deck_lib/Deck.d \
./src/deck_lib/Hand.d \
./src/deck_lib/HandTest.d \
./src/deck_lib/deck_toolbox.d 


# Each subdirectory must supply rules for building sources it contributes
src/deck_lib/%.o: ../src/deck_lib/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/micha/workspace/libtorch/include/torch/csrc/api/include -I/usr/include/python3.6m -I"/home/micha/workspace/matplotlib-cpp-master" -I/home/micha/workspace/DeepPoQRL/src -I/usr/include -I"/home/micha/workspace/libtorch/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


