# Copyright (c) 2020 ARM Limited. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.18.2 FATAL_ERROR)

if(POLICY CMP0076)
    cmake_policy(SET CMP0076 NEW)
endif()


add_library(mbed-os-cmsis OBJECT)

mbed_set_cpu_core_options(mbed-os-cmsis ${MBED_TOOLCHAIN})
mbed_set_toolchain_options(mbed-os-cmsis)
mbed_set_language_standard(mbed-os-cmsis)
mbed_set_profile_options(mbed-os-cmsis ${MBED_TOOLCHAIN})

add_subdirectory(CMSIS_5)
add_subdirectory(device)
