// KatanaOpenAssetIO
// Copyright (c) 2024 The Foundry Visionmongers Ltd
// SPDX-License-Identifier: Apache-2.0
#pragma once
#include <openassetio/hostApi/HostInterface.hpp>

/**
The KatanaHostInterface class provides a mock implementation of a host interface for the
openassetio library.
*/
class KatanaHostInterface : public openassetio::hostApi::HostInterface
{
public:
    /**
    Default constructor for the KatanaHostInterface class.
    */
    KatanaHostInterface() = default;

    /**
    Default destructor for the KatanaHostInterface class.
    */
    ~KatanaHostInterface() override = default;

    /**
    Returns an identifier string for this mock host interface.
    */
    [[nodiscard]] openassetio::Identifier identifier() const override
    {
        return "com.foundry.katana";
    }

    /**
    Returns a human-readable name for this mock host interface.
    */
    [[nodiscard]] openassetio::Str displayName() const override { return "Katana"; }

    /**
    Returns an empty dictionary of information about this mock host interface.
    */
    openassetio::InfoDictionary info() override { return {}; }
};