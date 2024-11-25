# KatanaOpenAssetIO
# Copyright (c) 2024 The Foundry Visionmongers Ltd
# SPDX-License-Identifier: Apache-2.0

function(katanaopenassetio_platform_target_properties target_name)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        if (KATANAOPENASSETIO_ENABLE_EXTRA_WARNINGS)
            # Compiler warnings
            target_compile_options(
                ${target_name}
                PRIVATE
                -Wall -Wextra -Wpedantic -Wl,--no-undefined
            )
        endif ()

        # Security hardening
        if (KATANAOPENASSETIO_ENABLE_SECURITY_HARDENING)
            target_compile_options(${target_name} PRIVATE -fstack-protector-all)
            if (NOT CMAKE_BUILD_TYPE STREQUAL Debug)
                # _FORTIFY_SOURCE is only available with optimisations enabled.
                target_compile_definitions(${target_name} PRIVATE _FORTIFY_SOURCE=2)
            endif ()
            target_compile_definitions(${target_name} PRIVATE _GLIBCXX_ASSERTIONS)
        endif ()
    endif ()
endfunction()
