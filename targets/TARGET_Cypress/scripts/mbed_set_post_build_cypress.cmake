# Copyright (c) 2021 ARM Limited. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

include(${MBED_PATH}/tools/cmake/mbed_set_post_build.cmake)

#
# Merge Cortex-M4 HEX and a Cortex-M0 HEX.
#
function(mbed_post_build_psoc6_merge_hex)
    find_package(Python3)

    set (extra_macro_args ${ARGN})

    list(LENGTH cortex_m0_hex num_extra_args)

    if(${num_extra_args} GREATER 0)
        list(GET extra_macro_args 0 cortex_m0_hex)
        set(post_build_command
            COMMAND ${Python3_EXECUTABLE} ${MBED_PATH}/tools/targets/PSOC6.py
                merge
                --elf $<TARGET_FILE:${APP_TARGET}>
                --m4hex ${CMAKE_BINARY_DIR}/${APP_TARGET}.hex
                --m0hex ${cortex_m0_hex}
        )
    else()
        set(post_build_command
            COMMAND ${Python3_EXECUTABLE} ${MBED_PATH}/tools/targets/PSOC6.py
                merge
                --elf $<TARGET_FILE:${APP_TARGET}>
                --hexf0 ${CMAKE_BINARY_DIR}/${APP_TARGET}.hex
        )
    endif()

    mbed_set_post_build_operation()
endfunction()


#
# Sign a Cortex-M4 HEX with Cortex-M0 HEX.
#
function(mbed_post_build_psoc6_sign_image
    m0hex_filename
    mbed_target_name
    policy_file_name
    boot_scheme
    cm0_img_id
    cm4_img_id
    cortex_m0_hex
)
    find_package(Python3)

    set(post_build_command
        COMMAND ${Python3_EXECUTABLE} ${MBED_PATH}/tools/targets/PSOC6.py
            sign
            --build-dir ${CMAKE_BINARY_DIR}
            --m0hex-filename ${m0hex_filename}
            --target-name ${mbed_target_name}
            --policy-file-name ${policy_file_name}
            --boot-scheme ${boot_scheme}
            --cm0-img-id ${cm0_img_id}
            --cm4-img-id ${cm4_img_id}
            --elf $<TARGET_FILE:${APP_TARGET}>
            --m4hex ${CMAKE_BINARY_DIR}/${APP_TARGET}.hex
            --m0hex ${cortex_m0_hex}
    )

    mbed_set_post_build_operation()
endfunction()
