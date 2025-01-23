cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)

project(LedMatrix5x5)

pico_sdk_init()

add_executable(LedMatrix5x5
    LedMatrix5x5.c
    libs/teclado_matricial/teclado_matricial.c
    tecla_d/animacao.c
)

target_include_directories(LedMatrix5x5 PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/libs/teclado_matricial
    ${CMAKE_CURRENT_LIST_DIR}/tecla_d
)

target_link_libraries(LedMatrix5x5
    pico_stdlib
    hardware_pio
    hardware_gpio
    hardware_adc
)

pico_add_extra_outputs(LedMatrix5x5)

pico_generate_pio_header(LedMatrix5x5 ${CMAKE_CURRENT_LIST_DIR}/pio_matrix.pio)
