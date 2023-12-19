cmake_minimum_required(VERSION 3.14)

set(PROJECT_NAME "rp2040test")

add_compile_definitions($<$<CONFIG:Debug>:DEBUG=1>)

set(PICO_SDK_PATH "${CMAKE_SOURCE_DIR}/pico-sdk")
set(ENV{PICO_SDK_PATH} "${CMAKE_SOURCE_DIR}/pico-sdk")

set(FREERTOS_PATH "${CMAKE_SOURCE_DIR}/FreeRTOS-Kernel")
set(FREERTOS_CFG "${CMAKE_SOURCE_DIR}/Config")

include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(${PROJECT_NAME}
        LANGUAGES C CXX ASM
        DESCRIPTION "RP2040 examples"
)

pico_sdk_init()

add_library(FreeRTOS STATIC
    ${FREERTOS_PATH}/list.c
    ${FREERTOS_PATH}/queue.c
    ${FREERTOS_PATH}/tasks.c
    ${FREERTOS_PATH}/timers.c
    ${FREERTOS_PATH}/portable/MemMang/heap_3.c
    ${FREERTOS_PATH}/portable/GCC/ARM_CM0/port.c
)

target_include_directories(FreeRTOS PUBLIC
    ${FREERTOS_CFG}/
    ${FREERTOS_PATH}/include
    ${FREERTOS_PATH}/portable/GCC/ARM_CM0
)

add_subdirectory(examples)
