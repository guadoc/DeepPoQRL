################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/player_lib/AbstractPlayer.cpp \
../src/player_lib/PlayerBot.cpp \
../src/player_lib/PlayerGUI.cpp \
../src/player_lib/PlayerLogs.cpp \
../src/player_lib/PlayerQlearner.cpp \
../src/player_lib/PlayerRandom.cpp \
../src/player_lib/PlayerStat.cpp \
../src/player_lib/StatPlayer.cpp \
../src/player_lib/player_toolbox.cpp 

OBJS += \
./src/player_lib/AbstractPlayer.o \
./src/player_lib/PlayerBot.o \
./src/player_lib/PlayerGUI.o \
./src/player_lib/PlayerLogs.o \
./src/player_lib/PlayerQlearner.o \
./src/player_lib/PlayerRandom.o \
./src/player_lib/PlayerStat.o \
./src/player_lib/StatPlayer.o \
./src/player_lib/player_toolbox.o 

CPP_DEPS += \
./src/player_lib/AbstractPlayer.d \
./src/player_lib/PlayerBot.d \
./src/player_lib/PlayerGUI.d \
./src/player_lib/PlayerLogs.d \
./src/player_lib/PlayerQlearner.d \
./src/player_lib/PlayerRandom.d \
./src/player_lib/PlayerStat.d \
./src/player_lib/StatPlayer.d \
./src/player_lib/player_toolbox.d 


# Each subdirectory must supply rules for building sources it contributes
src/player_lib/%.o: ../src/player_lib/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/micha/workspace/libtorch/include/torch/csrc/api/include -I/usr/include/python3.6m -I"/home/micha/workspace/matplotlib-cpp-master" -I/home/micha/workspace/DeepPoQRL/src -I/usr/include -I"/home/micha/workspace/libtorch/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


