# Copyright (c) 2020 ARM Limited. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

if(POLICY CMP0076)
    cmake_policy(SET CMP0076 NEW)
endif()

add_library(cmsis STATIC)

include(${MBED_CONFIG_PATH}/mbed_config.cmake)

include(${MBED_ROOT}/cmake/toolchain.cmake)
mbed_set_toolchain_options(cmsis)

include(${MBED_ROOT}/cmake/profile.cmake)
mbed_set_profile_options(cmsis ${MBED_TOOLCHAIN})

include(${MBED_ROOT}/cmake/util.cmake)

mbed_add_cmake_directory_if_labels("TARGET")

target_include_directories(cmsis
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(cmsis
    PUBLIC
        mbed-os
)
