################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/tests/unit_tests/test_abstract_player.cpp \
../src/tests/unit_tests/test_abstract_table.cpp \
../src/tests/unit_tests/test_deck.cpp \
../src/tests/unit_tests/test_hand.cpp \
../src/tests/unit_tests/test_optim_hand.cpp \
../src/tests/unit_tests/test_player_bot.cpp \
../src/tests/unit_tests/test_player_qlearner.cpp \
../src/tests/unit_tests/test_player_v2.cpp \
../src/tests/unit_tests/test_plot.cpp \
../src/tests/unit_tests/test_stat_player.cpp \
../src/tests/unit_tests/test_table_log.cpp \
../src/tests/unit_tests/test_table_train.cpp 

OBJS += \
./src/tests/unit_tests/test_abstract_player.o \
./src/tests/unit_tests/test_abstract_table.o \
./src/tests/unit_tests/test_deck.o \
./src/tests/unit_tests/test_hand.o \
./src/tests/unit_tests/test_optim_hand.o \
./src/tests/unit_tests/test_player_bot.o \
./src/tests/unit_tests/test_player_qlearner.o \
./src/tests/unit_tests/test_player_v2.o \
./src/tests/unit_tests/test_plot.o \
./src/tests/unit_tests/test_stat_player.o \
./src/tests/unit_tests/test_table_log.o \
./src/tests/unit_tests/test_table_train.o 

CPP_DEPS += \
./src/tests/unit_tests/test_abstract_player.d \
./src/tests/unit_tests/test_abstract_table.d \
./src/tests/unit_tests/test_deck.d \
./src/tests/unit_tests/test_hand.d \
./src/tests/unit_tests/test_optim_hand.d \
./src/tests/unit_tests/test_player_bot.d \
./src/tests/unit_tests/test_player_qlearner.d \
./src/tests/unit_tests/test_player_v2.d \
./src/tests/unit_tests/test_plot.d \
./src/tests/unit_tests/test_stat_player.d \
./src/tests/unit_tests/test_table_log.d \
./src/tests/unit_tests/test_table_train.d 


# Each subdirectory must supply rules for building sources it contributes
src/tests/unit_tests/%.o: ../src/tests/unit_tests/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/micha/workspace/libtorch/include/torch/csrc/api/include -I/usr/include/python3.6m -I"/home/micha/workspace/matplotlib-cpp-master" -I/home/micha/workspace/DeepPoQRL/src -I/usr/include -I"/home/micha/workspace/libtorch/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/tests/unit_tests/test_abstract_table.o: ../src/tests/unit_tests/test_abstract_table.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/micha/workspace/libtorch/include/torch/csrc/api/include -I/usr/include -I"/home/micha/workspace/libtorch/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/tests/unit_tests/test_abstract_table.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/tests/unit_tests/test_table_train.o: ../src/tests/unit_tests/test_table_train.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/micha/workspace/libtorch/include/torch/csrc/api/include -I"/home/micha/workspace/DeepPoQRL" -I/usr/include -I"/home/micha/workspace/libtorch/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/tests/unit_tests/test_table_train.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


