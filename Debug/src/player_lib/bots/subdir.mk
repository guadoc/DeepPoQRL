################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/player_lib/bots/PlayerBotV1.cpp \
../src/player_lib/bots/PlayerBotV2.cpp \
../src/player_lib/bots/PlayerBotV21.cpp 

OBJS += \
./src/player_lib/bots/PlayerBotV1.o \
./src/player_lib/bots/PlayerBotV2.o \
./src/player_lib/bots/PlayerBotV21.o 

CPP_DEPS += \
./src/player_lib/bots/PlayerBotV1.d \
./src/player_lib/bots/PlayerBotV2.d \
./src/player_lib/bots/PlayerBotV21.d 


# Each subdirectory must supply rules for building sources it contributes
src/player_lib/bots/%.o: ../src/player_lib/bots/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/micha/workspace/libtorch/include/torch/csrc/api/include -I/usr/include/python3.6m -I"/home/micha/workspace/matplotlib-cpp-master" -I/home/micha/workspace/DeepPoQRL/src -I/usr/include -I"/home/micha/workspace/libtorch/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


