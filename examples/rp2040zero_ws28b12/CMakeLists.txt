cmake_minimum_required(VERSION 3.14)

project(rp2040zero_ws28b12)

add_executable(${PROJECT_NAME}
    main.c
)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/generated)

pico_generate_pio_header(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/generated)

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC
    pico_stdlib
    hardware_pio
    FreeRTOS
)

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

pico_add_extra_outputs(${PROJECT_NAME})
