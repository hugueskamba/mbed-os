# Copyright (c) 2020 ARM Limited. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

if("NU_PFM_M2351_NPSA_NS" IN_LIST MBED_TARGET_LABELS)
    if ("NU_PREBUILD_SECURE" IN_LIST MBED_TARGET_LABELS)
        target_link_libraries(mbed-core
            INTERFACE
                ${CMAKE_CURRENT_SOURCE_DIR}/TARGET_NU_PFM_M2351_NPSA_NS/TARGET_NU_PREBUILD_SECURE/cmse_lib.o
        )
    endif()
elseif("NU_PFM_M2351_NS" IN_LIST MBED_TARGET_LABELS)
    if ("NU_PREBUILD_SECURE" IN_LIST MBED_TARGET_LABELS)
        target_link_libraries(mbed-core
            INTERFACE
                ${CMAKE_CURRENT_SOURCE_DIR}/TARGET_NU_PFM_M2351_NS/TARGET_NU_PREBUILD_SECURE/cmse_lib.o
        )
    endif()
elseif("TFM" IN_LIST MBED_TARGET_LABELS)
    target_sources(mbed-core INTERFACE TARGET_TFM/tfm_ns_lock_rtx.c)
endif()

add_subdirectory(device)

target_sources(mbed-core
    INTERFACE
        wait_ns.c
)
