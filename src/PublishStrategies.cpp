// KatanaOpenAssetIO
// Copyright (c) 2024 The Foundry Visionmongers Ltd
// SPDX-License-Identifier: Apache-2.0
#include "PublishStrategies.hpp"

#include <FnAsset/plugin/FnAsset.h>
#include <FnAsset/suite/FnAssetSuite.h>
#include <FnLogging/FnLogging.h>
#include <openassetio_mediacreation/openassetio_mediacreation.hpp>
#include <openassetio_mediacreation/specifications/specifications.hpp>

namespace
{
template <typename T>
struct MediaCreationPublishStrategy : PublishStrategy
{
    [[nodiscard]] const openassetio::trait::TraitSet& assetTraitSet() const override
    {
        return T::kTraitSet;
    }

    [[nodiscard]] openassetio::trait::TraitsDataPtr prePublishTraitData(
        const FnKat::Asset::StringMap& args) const override
    {
        // TODO(DH): Populate with manager driven trait values
        (void)args;
        const auto specification = T::create();
        return specification.traitsData();
    }

    [[nodiscard]] openassetio::trait::TraitsDataPtr postPublishTraitData(
        const FnKat::Asset::StringMap& args) const override
    {
        // TODO(DH): Populate with manager katana driven trait values
        (void)args;
        const auto specification = T::create();
        return specification.traitsData();
    }
};

// Utility declarations
using WorkfileAssetPublisher = MediaCreationPublishStrategy<
    openassetio_mediacreation::specifications::application::WorkfileSpecification>;

using ImageAssetPublisher =
    MediaCreationPublishStrategy<openassetio_mediacreation::specifications::twoDimensional::
                                     DeepBitmapImageResourceSpecification>;

using SceneGeometryAssetPublisher =
    MediaCreationPublishStrategy<openassetio_mediacreation::specifications::threeDimensional::
                                     SceneGeometryResourceSpecification>;

using ShaderResourceAssetPublisher = MediaCreationPublishStrategy<
    openassetio_mediacreation::specifications::threeDimensional::ShaderResourceSpecification>;

using SceneLightingAssetPublisher =
    MediaCreationPublishStrategy<openassetio_mediacreation::specifications::threeDimensional::
                                     SceneLightingResourceSpecification>;

}  // anonymous namespace

PublishStrategies::PublishStrategies()
{
    m_strategies[kFnAssetTypeKatanaScene] = std::make_unique<WorkfileAssetPublisher>();
    // TODO(DH): This would be better as something like ApplicationExtensionAssetPublisher...
    m_strategies[kFnAssetTypeMacro] = std::make_unique<WorkfileAssetPublisher>();
    m_strategies[kFnAssetTypeLiveGroup] = std::make_unique<WorkfileAssetPublisher>();
    m_strategies[kFnAssetTypeImage] = std::make_unique<ImageAssetPublisher>();
    m_strategies[kFnAssetTypeLookFile] = std::make_unique<WorkfileAssetPublisher>();
    m_strategies[kFnAssetTypeLookFileMgrSettings] = std::make_unique<WorkfileAssetPublisher>();
    m_strategies[kFnAssetTypeAlembic] = std::make_unique<SceneGeometryAssetPublisher>();
    m_strategies[kFnAssetTypeCastingSheet] = std::make_unique<WorkfileAssetPublisher>();
    m_strategies[kFnAssetTypeAttributeFile] = std::make_unique<WorkfileAssetPublisher>();
    m_strategies[kFnAssetTypeFCurveFile] = std::make_unique<WorkfileAssetPublisher>();
    m_strategies[kFnAssetTypeGafferThreeRig] = std::make_unique<SceneLightingAssetPublisher>();
    m_strategies[kFnAssetTypeScenegraphBookmarks] = std::make_unique<WorkfileAssetPublisher>();
    m_strategies[kFnAssetTypeShader] = std::make_unique<ShaderResourceAssetPublisher>();
}

const PublishStrategy& PublishStrategies::strategyForAssetType(const std::string& assetType) const
{
    try
    {
        return *m_strategies.at(assetType);
    }
    catch (const std::out_of_range&)
    {
        // TODO(DH): Handle default asset publisher.
        throw std::runtime_error("Publishing '" + assetType + "' is currently unsupported.");
    }
}