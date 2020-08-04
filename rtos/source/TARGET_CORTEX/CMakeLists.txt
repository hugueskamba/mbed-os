# Copyright (c) 2020 ARM Limited. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

if(POLICY CMP0076)
    cmake_policy(SET CMP0076 NEW)
endif()

add_library(rtos STATIC)

include(${MBED_CONFIG_PATH}/mbed_config.cmake)

include(${MBED_ROOT}/cmake/toolchain.cmake)
mbed_set_toolchain_options(rtos)

include(${MBED_ROOT}/cmake/profile.cmake)
mbed_set_profile_options(rtos ${MBED_TOOLCHAIN})

include(${MBED_ROOT}/cmake/util.cmake)

add_subdirectory(rtx5)

target_include_directories(rtos
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        rtx4
)

target_sources(rtos
    PRIVATE
        mbed_boot.c
        mbed_rtos_rtx.c
        mbed_rtx_handlers.c
        mbed_rtx_idle.cpp
)

if(${MBED_TOOLCHAIN} STREQUAL "GCC_ARM")
    target_sources(rtos
        PRIVATE
            TOOLCHAIN_GCC_ARM/mbed_boot_gcc_arm.c
    )
elseif(${MBED_TOOLCHAIN} STREQUAL "ARM")
    target_sources(rtos
        PRIVATE
            TOOLCHAIN_ARM_STD/mbed_boot_arm_std.c
    )
elseif(${MBED_TOOLCHAIN} STREQUAL "IAR")
    target_sources(rtos
        PRIVATE
            TOOLCHAIN_IAR/mbed_boot_iar.c
    )
endif()

target_link_libraries(rtos
    PUBLIC
        cmsis
)
