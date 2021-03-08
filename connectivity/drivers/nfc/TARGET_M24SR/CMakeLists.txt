# Copyright (c) 2020-2021 ARM Limited. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

add_library(mbed-nfc-m24sr INTERFACE)

target_include_directories(mbed-nfc-m24sr
    INTERFACE
        include
        include/nfc
)

target_sources(mbed-nfc-m24sr
    INTERFACE
        source/m24sr_driver.cpp
)

target_link_libraries(mbed-nfc PRIVATE mbed-nfc-m24sr)
