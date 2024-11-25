// KatanaOpenAssetIO
// Copyright (c) 2024 The Foundry Visionmongers Ltd
// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <FnAsset/plugin/FnAsset.h>

namespace Utilities
{

// Returns true if args contains the "versionUp" argument
// indicating that the user has requested a new version is created.
bool ShouldVersionUp(const FnKat::Asset::StringMap& args);

// Returns true if args contains the "publish" argument
// indicating that the user has requested this version set as the latest
// version.
bool ShouldPublish(const FnKat::Asset::StringMap& args);
}  // namespace Utilities
