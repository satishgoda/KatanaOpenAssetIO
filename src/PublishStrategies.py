from abc import ABC, abstractmethod
from typing import Dict, Any


class PublishStrategy(ABC):
    """
    Abstract base class for defining a publish strategy.
    """

    @abstractmethod
    def asset_trait_set(self) -> set:
        """
        Returns the TraitSet related to publishing this type of asset.
        """
        pass

    @abstractmethod
    def pre_publish_trait_data(self, args: Dict[str, Any]) -> Dict[str, Any]:
        """
        Pre-publish trait data processing.
        """
        pass

    @abstractmethod
    def post_publish_trait_data(self, args: Dict[str, Any]) -> Dict[str, Any]:
        """
        Post-publish trait data processing.
        """
        pass


class PublishStrategies:
    """
    Container for managing multiple publish strategies.
    """

    def __init__(self):
        self._strategies: Dict[str, PublishStrategy] = {}

    def strategy_for_asset_type(self, asset_type: str) -> PublishStrategy:
        """
        Retrieves the publish strategy for a given asset type.
        """
        if asset_type not in self._strategies:
            raise ValueError(f"No strategy found for asset type: {asset_type}")
        return self._strategies[asset_type]

    def add_strategy(self, asset_type: str, strategy: PublishStrategy):
        """
        Adds a strategy for a specific asset type.
        """
        self._strategies[asset_type] = strategy
