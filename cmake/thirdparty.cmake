# KatanaOpenAssetIO
# Copyright (c) 2024 The Foundry Visionmongers Ltd
# SPDX-License-Identifier: Apache-2.0

# Katana APIs
find_package(Katana CONFIG REQUIRED)

set_target_properties(
        foundry.katana.FnConfig
        foundry.katana.FnAsset
        foundry.katana.FnAssetPlugin
        foundry.katana.FnAttribute
        foundry.katana.FnLogging
        foundry.katana.pystring
        PROPERTIES
        SYSTEM TRUE
)

# Python
find_package(Python REQUIRED COMPONENTS Development)

# OpenAssetIO
find_package(OpenAssetIO CONFIG REQUIRED)

# OpenAssetIO MediaCreation library
find_package(OpenAssetIO-MediaCreation CONFIG REQUIRED)
