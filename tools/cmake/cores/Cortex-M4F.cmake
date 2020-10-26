# Copyright (c) 2020 ARM Limited. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

# Sets cpu core options
function(mbed_set_cpu_core_options target mbed_toolchain)
    target_compile_definitions(mbed-core
        PUBLIC
            __CORTEX_M4
            ARM_MATH_CM4
            __FPU_PRESENT=1
            __CMSIS_RTOS
            __MBED_CMSIS_RTOS_CM
    )

    if(${mbed_toolchain} STREQUAL "GCC_ARM")
        list(APPEND common_toolchain_options
            "-mthumb"
            "-mcpu=cortex-m4"
            "-mfpu=fpv4-sp-d16"
            "-mfloat-abi=softfp"
        )
        
        target_compile_options(mbed-core
            PUBLIC
                ${common_toolchain_options}
        )

        target_link_options(mbed-core
            PUBLIC
                ${common_toolchain_options}
        )
    elseif(${mbed_toolchain} STREQUAL "ARM")
        list(APPEND compile_options
            "-mcpu=cortex-m4"
            "-mfpu=fpv4-sp-d16"
            "-mfloat-abi=hard"
        )

        target_compile_options(mbed-core
            PUBLIC
                $<$<COMPILE_LANGUAGE:C>:${compile_options}>
                $<$<COMPILE_LANGUAGE:CXX>:${compile_options}>
                $<$<COMPILE_LANGUAGE:ASM>:-mcpu=Cortex-M4>
        )

        target_link_options(mbed-core
            PUBLIC
                "--cpu=Cortex-M4"
        )
    endif()
endfunction()
