from . import GameVersion, Module, Item, Container, StaticTwoDA, Resource
from . import ObjectBase, ObjectHandle, Area, Creature, Door, Encounter, Placeable, Store, Trigger, Waypoint
from . import Effect, ResourceType, Image, ResourceData

from typing import Optional, Tuple, List

# Classes #####################################################################
###############################################################################


class ConfigOptions:
    """Configuration options
    """
    #: If true, load base game data.
    include_install: bool = True
    #: If true, load NWSync data.
    include_nwsync: bool = True
    #: If true, load user data.
    include_user: bool = True


class Config:
    """Configuration service
    """

    def initialize(self, options: ConfigOptions):
        """Initialize config system"""
        pass

    def install_path(self) -> str:
        """Gets game install path"""
        return ""

    def options(self) -> ConfigOptions:
        """Gets config options
        """
        pass

    def user_path(self) -> str:
        """Gets game install path"""
        return ""

    def set_paths(self, install: str, user: str):
        """Sets game paths

        Note: Must be called before ``initialize``
        """

    def set_version(self, version: GameVersion):
        """Sets game paths

        Note: Must be called before ``initialize``
        """


class EffectSystemStats:
    """Effect system stat data
    """
    free_list_size: int
    pool_size: int


class EffectSystem:
    def add_effect(self, type, apply, remove):
        """Adds an effect type to the registry"""
        pass

    def add_itemprop(self, type, generator):
        """Adds an item property type to the registry"""
        pass

    def apply(self, obj: ObjectBase, effect: Effect) -> bool:
        """Applies an effect to an object"""
        pass

    def create(self, type) -> Effect:
        """Creates an effect"""
        pass

    def destroy(self, effect: Effect) -> None:
        """Destroys an effect"""

    def ip_cost_table(self, table: int) -> StaticTwoDA | None:
        """Gets an item property cost table"""
        pass

    def ip_definition(self, type):
        """Gets an item property definition"""
        pass

    def ip_param_table(self, table: int) -> StaticTwoDA | None:
        """Gets an item property param table"""
        pass

    def itemprops(self) -> StaticTwoDA:
        """Gets an item property baseitem table"""
        pass

    def remove(self, obj: ObjectBase, effect: Effect) -> bool:
        """Removes an effect to an object"""
        pass

    def stats(self) -> EffectSystemStats:
        """Gets stats regarding the effect system"""
        pass


class Objects:
    """The object system creates, serializes, and deserializes entities
    """

    def area(self, resref: str) -> Area:
        pass

    def creature(self, resref: str) -> Creature:
        pass

    def destroy(self, obj: ObjectHandle) -> None:
        """Destroys an object and removes it from object system"""
        pass

    def door(self, resref: str) -> Door:
        pass

    def encounter(self, resref: str) -> Encounter:
        pass

    def get(self, handle: ObjectHandle):
        """Gets an object by its handle"""
        pass

    def get_by_tag(self, tag: str, nth: int = 0) -> Optional[ObjectBase]:
        """Gets an object with specific tag
        """

    def item(self, resref: str) -> Item:
        pass

    def placeable(self, resref: str) -> Placeable:
        pass

    def store(self, resref: str) -> Store:
        pass

    def trigger(self, resref: str) -> Trigger:
        pass

    def valid(self, handle: ObjectHandle) -> bool:
        """Checks if an object handle is still valid"""
        pass

    def waypoint(self, resref: str) -> Waypoint:
        pass


class Resources(Container):
    """Resources service
    """

    def __init__(self, parent: "Resources"):
        """Constructs resoruce manager with a given parent."""

    def demand_any(self, resref: str,
                   restypes: List[ResourceType]) -> ResourceData:
        """Gets the first found resource in container priority order for an arbitrary list
        of types.
        """

    def demand_in_order(self, resref: str,
                        restypes: List[ResourceType]) -> ResourceData:
        """Attempts to locate first matching resource by resource type priority.
        """

    def demand_server_vault(self, cdkey: str, resref: str) -> ResourceData:
        """Demands a player character file.
        """

    def texture(self, resref: str) -> Optional[Image]:
        """Loads a texture from the resource manager

        This is a wrapper around ``demand_in_order`` only dds and tga are considered.
        """

    pass


class Rules:
    """Rules service
    """
    pass


class Strings:
    """Strings service
    """
    pass


class TwoDACache:
    """2da cache
    """

    def get(self, name: str | Resource) -> StaticTwoDA | None:
        """Gets a cached twoda"""
        pass

# Functions ###################################################################
###############################################################################


def config():
    """Gets config service"""
    pass


def load_module(path: str, instantiate: bool = True) -> Module:
    """Loads a module

    Args:
        path (str): path to module, can be a directory (with module.ifo), a mod file, or a zip file
        instantiate (bool): If instantiate is ``False``, no areas are loaded and service init at
            ``module_post_instantiation`` is not called.
    """
    pass


def effects() -> EffectSystem:
    """Gets effects service"""
    pass


def objects() -> Objects:
    """Gets objects service"""
    pass


def resman() -> Resources:
    """Gets resman service"""
    pass


def rules() -> Rules:
    """Gets rules service"""
    pass


def start(options: Optional[ConfigOptions]):
    """Starts kernel services

    Args:
        config (rollnw.ConfigOptions | None): Optionally pass in configuration.  Default behavior
            is to search for whatever NWN(:EE) install that it can find
    """
    pass


def strings() -> Strings:
    """Gets strings service"""
    pass


def twodas() -> TwoDACache:
    """Gets TwoDA Cache service"""
    pass


def unload_module() -> None:
    """Unloads the currently loaded module
    """
    pass
