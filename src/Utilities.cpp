// KatanaOpenAssetIO
// Copyright (c) 2024 The Foundry Visionmongers Ltd
// SPDX-License-Identifier: Apache-2.0
#include "Utilities.hpp"

#include <regex>

namespace Utilities
{

namespace
{
bool GetBooleanValue(const FnKat::Asset::StringMap& args, const std::string& key)
{
    const auto it = args.find(key);
    if (it == args.cend())
        return false;
    return it->second == "True";
}
}  // anonymous namespace

bool ShouldVersionUp(const FnKat::Asset::StringMap& args)
{
    return GetBooleanValue(args, "versionUp");
}

bool ShouldPublish(const FnKat::Asset::StringMap& args)
{
    return GetBooleanValue(args, "publish");
}
}  // namespace Utilities
