# Copyright (c) 2020 ARM Limited. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.18.2 FATAL_ERROR)

if(POLICY CMP0076)
    cmake_policy(SET CMP0076 NEW)
endif()

add_library(mbed-os-cmsis-device-rtos OBJECT)

mbed_set_cpu_core_options(mbed-os-cmsis-device-rtos ${MBED_TOOLCHAIN})
mbed_set_toolchain_options(mbed-os-cmsis-device-rtos)
mbed_set_language_standard(mbed-os-cmsis-device-rtos)
mbed_set_profile_options(mbed-os-cmsis-device-rtos ${MBED_TOOLCHAIN})

if(${MBED_TOOLCHAIN} STREQUAL "GCC_ARM")
    target_sources(mbed-os-cmsis-device-rtos
        PRIVATE
            TOOLCHAIN_GCC_ARM/mbed_boot_gcc_arm.c
    )
elseif(${MBED_TOOLCHAIN} STREQUAL "ARM")
    target_sources(mbed-os-cmsis-device-rtos
        PRIVATE
            TOOLCHAIN_ARM_STD/mbed_boot_arm_std.c
    )
elseif(${MBED_TOOLCHAIN} STREQUAL "IAR")
    target_sources(mbed-os-cmsis-device-rtos
        PRIVATE
            TOOLCHAIN_IAR/mbed_boot_iar.c
    )
endif()

target_include_directories(mbed-os-cmsis-device-rtos
    PUBLIC
        include
)

target_sources(mbed-os-cmsis-device-rtos
    PRIVATE
        source/mbed_boot.c
        source/mbed_rtos_rtx.c
        source/mbed_rtx_handlers.c
        source/mbed_rtx_idle.cpp
)
