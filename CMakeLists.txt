cmake_minimum_required(VERSION 3.13)
project(coding_challange_sounds)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.68 REQUIRED COMPONENTS filesystem program_options unit_test_framework)

add_executable(sounds-router src/main.cpp src/command/Arguments.h src/app/Calc.h src/app/model/Factory.h src/app/model/Executor.h src/app/model/AudioSourceRouter.h src/app/model/AudioSource.h src/app/model/AudioSourceStorage.h src/app/model/SourceReference.h)
target_link_libraries(sounds-router Boost::filesystem Boost::program_options)

add_executable(test src/test.cpp src/app/model/Helper.h src/app/model/AudioSource.cpp src/app/model/AudioSourceRouter.cpp src/app/model/AudioSourceStorage.cpp src/app/model/Factory.cpp src/app/model/Helper.cpp src/app/model/SourceReference.cpp src/command/Commands.h src/command/Params.h src/command/Commands.cpp src/command/Params.cpp)
target_link_libraries(test Boost::filesystem Boost::program_options Boost::unit_test_framework)
