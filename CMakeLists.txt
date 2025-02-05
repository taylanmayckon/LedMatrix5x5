# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.0.0)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(LedMatrix5x5 C CXX ASM)

pico_sdk_init()

add_executable(LedMatrix5x5
    LedMatrix5x5.c
    libs/teclado_matricial/teclado_matricial.c
    libs/tecla_d/animacao.c
    libs/tecla_jogo_velha/tecla_jogo_velha.c
    libs/tecla_1/tecla_1.c
    libs/tecla_A/led_animation.c
    libs/animacao-2/animacao-2.c
    libs/tecla-b/tecla-b.c
    libs/teclac/tecla_c.c
)

# Adiciona diretórios de inclusão
include_directories(
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/libs/teclado_matricial
    ${CMAKE_CURRENT_LIST_DIR}/libs/tecla_d
    ${CMAKE_CURRENT_LIST_DIR}/libs/tecla_jogo_velha
    ${CMAKE_CURRENT_LIST_DIR}/libs/tecla_1
    ${CMAKE_CURRENT_LIST_DIR}/libs/tecla_A
    ${CMAKE_CURRENT_LIST_DIR}/libs/animacao-2
    ${CMAKE_CURRENT_LIST_DIR}/libs/tecla-b
    ${CMAKE_CURRENT_LIST_DIR}/libs/teclac
)

# Adiciona o arquivo PIO
pico_generate_pio_header(LedMatrix5x5 ${CMAKE_CURRENT_LIST_DIR}/pio_matrix.pio)


pico_enable_stdio_usb(LedMatrix5x5 1)
pico_enable_stdio_uart(LedMatrix5x5 0)


target_link_libraries(LedMatrix5x5
    pico_stdlib
    hardware_pio
    hardware_clocks
	hardware_adc
)

pico_add_extra_outputs(LedMatrix5x5)