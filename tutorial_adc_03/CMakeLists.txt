cmake_minimum_required(VERSION 3.12)

# Include build functions from Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

set(PROJECT_NAME tutorial_adc_03)

project(${PROJECT_NAME} C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(PICO_CXX_ENABLE_EXCEPTIONS 1)
set(PICO_CXX_ENABLE_RTTI 1) # Run-time type information

pico_sdk_init()

add_executable(${PROJECT_NAME}
main.cpp
)

# Make the stdio functions use USB rather than the serial pins
pico_enable_stdio_usb(${PROJECT_NAME} 0)
pico_enable_stdio_uart(${PROJECT_NAME} 1)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(${PROJECT_NAME} pico_stdlib hardware_adc)

# create map/bin/hex file etc.
pico_add_extra_outputs(${PROJECT_NAME})
