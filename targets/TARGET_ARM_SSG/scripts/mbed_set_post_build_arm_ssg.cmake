# Copyright (c) 2021 ARM Limited. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

include(${MBED_PATH}/tools/cmake/mbed_set_post_build.cmake)

#
# Merge ARM MUSCA B1 secure and non-secure images.
#
function(mbed_post_build_musca_b1_merge_secure_bin secure_binary)
    find_package(Python3)

    set(post_build_command
        COMMAND ${Python3_EXECUTABLE} ${MBED_PATH}/tools/targets/ARM_MUSCA_B1.py
            --non-secure-bin ${CMAKE_BINARY_DIR}/${APP_TARGET}.bin
            --secure-bin ${secure_binary}
    )

    mbed_set_post_build_operation()
endfunction()

#
# Merge ARM MUSCA S1 secure and non-secure images.
#
function(mbed_post_build_musca_s1_merge_secure_bin secure_binary)
    find_package(Python3)

    set(post_build_command
        COMMAND ${Python3_EXECUTABLE} ${MBED_PATH}/tools/targets/ARM_MUSCA_S1.py
            --non-secure-bin ${CMAKE_BINARY_DIR}/${APP_TARGET}.bin
            --secure-bin ${secure_binary}
    )

    mbed_set_post_build_operation()
endfunction()
