# KatanaOpenAssetIO
# Copyright (c) 2024 The Foundry Visionmongers Ltd
# SPDX-License-Identifier: Apache-2.0

from abc import ABC, abstractmethod
from openassetio_mediacreation import specifications


class PublishStrategy(ABC):
    @abstractmethod
    def asset_trait_set(self):
        pass

    @abstractmethod
    def pre_publish_trait_data(self, args):
        pass

    @abstractmethod
    def post_publish_trait_data(self, args):
        pass


class MediaCreationPublishStrategy(PublishStrategy):
    def __init__(self, specification_class):
        self.specification_class = specification_class

    def asset_trait_set(self):
        return self.specification_class.kTraitSet

    def pre_publish_trait_data(self, args):
        # TODO: Populate with manager driven trait values
        specification = self.specification_class.create()
        return specification.traits_data()

    def post_publish_trait_data(self, args):
        # TODO: Populate with manager katana driven trait values
        specification = self.specification_class.create()
        return specification.traits_data()


# Utility declarations
WorkfileAssetPublisher = MediaCreationPublishStrategy(
    specifications.application.WorkfileSpecification
)

ImageAssetPublisher = MediaCreationPublishStrategy(
    specifications.twoDimensional.DeepBitmapImageResourceSpecification
)

SceneGeometryAssetPublisher = MediaCreationPublishStrategy(
    specifications.threeDimensional.SceneGeometryResourceSpecification
)

ShaderResourceAssetPublisher = MediaCreationPublishStrategy(
    specifications.threeDimensional.ShaderResourceSpecification
)

SceneLightingAssetPublisher = MediaCreationPublishStrategy(
    specifications.threeDimensional.SceneLightingResourceSpecification
)


class PublishStrategies:
    def __init__(self):
        self.m_strategies = {
            "kFnAssetTypeKatanaScene": WorkfileAssetPublisher,
            "kFnAssetTypeMacro": WorkfileAssetPublisher,
            "kFnAssetTypeLiveGroup": WorkfileAssetPublisher,
            "kFnAssetTypeImage": ImageAssetPublisher,
            "kFnAssetTypeLookFile": WorkfileAssetPublisher,
            "kFnAssetTypeLookFileMgrSettings": WorkfileAssetPublisher,
            "kFnAssetTypeAlembic": SceneGeometryAssetPublisher,
            "kFnAssetTypeCastingSheet": WorkfileAssetPublisher,
            "kFnAssetTypeAttributeFile": WorkfileAssetPublisher,
            "kFnAssetTypeFCurveFile": WorkfileAssetPublisher,
            "kFnAssetTypeGafferThreeRig": SceneLightingAssetPublisher,
            "kFnAssetTypeScenegraphBookmarks": WorkfileAssetPublisher,
            "kFnAssetTypeShader": ShaderResourceAssetPublisher,
        }

    def strategy_for_asset_type(self, asset_type):
        try:
            return self.m_strategies[asset_type]
        except KeyError:
            # TODO: Handle default asset publisher.
            raise RuntimeError(f"Publishing '{asset_type}' is currently unsupported.")
