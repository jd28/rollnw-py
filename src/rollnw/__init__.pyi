import enum
from enum import IntFlag
from typing import ByteString, ClassVar, DefaultDict

class IVector4:
    x: int
    y: int
    z: int
    w: int

class Vector2:
    x: float
    y: float

class Vector3:
    x: float
    y: float
    z: float

class Vector4:
    x: float
    y: float
    z: float
    W: float

class LanguageID(enum.IntEnum):
    invalid = -1
    english = 0
    french = 1
    german = 2
    italian = 3
    spanish = 4
    polish = 5
    korean = 128
    chinese_traditional = 129
    chinese_simplified = 130
    japanese = 131

class Language:
    @staticmethod
    def encoding(language: LanguageID) -> str: ...
    @staticmethod
    def from_string(string: str) -> LanguageID: ...
    @staticmethod
    def has_feminine(language: LanguageID) -> bool: ...
    @staticmethod
    def to_base_id(id: int) -> tuple[LanguageID, bool]: ...
    @staticmethod
    def to_runtime_id(language: LanguageID, feminine: bool = False) -> int: ...
    @staticmethod
    def to_string(language: LanguageID, long_name: bool = False) -> str: ...

class LocString:
    def __init__(self, strref: int = -1) -> None: ...
    def __getitem__(self, language: LanguageID) -> str: ...
    def add(self, language: LanguageID, string: str, feminine: bool = False): ...
    def contains(self, language: LanguageID, feminine: bool = False): ...
    def get(self, language: LanguageID, feminine: bool = False): ...
    def remove(self, language: LanguageID, feminine: bool = False): ...
    def set_strref(self, strref: int): ...
    def size(self) -> int: ...
    def strref(self) -> int: ...
    def to_dict(self) -> DefaultDict: ...
    @staticmethod
    def from_dict(data: dict): ...

class Tlk:
    def __init__(self, init: str | LanguageID) -> None: ...
    def __getitem__(self, strref: int) -> str: ...
    def __setitem__(self, strref: int, string: str): ...
    def __len__(self) -> int: ...
    def get(self, strref: int) -> str: ...
    def language_id(self) -> None: ...
    def modified(self) -> None: ...
    def save(self) -> None: ...
    def save_as(self, path: str): ...
    def set(self, strref: int, string: str): ...
    def size(self) -> None: ...
    def valid(self) -> None: ...

class GameVersion(enum.Enum):
    v1_69 = ...
    vEE = ...
    nwn2 = ...

class CreatureColors(enum.Enum):
    hair = ...
    skin = ...
    tatoo1 = ...
    tatoo2 = ...

class CreatureAppearance:
    body_parts: BodyParts
    colors: list[int]
    id: int
    phenotype: int
    portrait_id: int
    tail: int
    wings: int

class BodyParts:
    belt: int
    bicep_left: int
    bicep_right: int
    foot_left: int
    foot_right: int
    forearm_left: int
    forearm_right: int
    hand_left: int
    hand_right: int
    head: int
    neck: int
    pelvis: int
    shin_left: int
    shin_right: int
    shoulder_left: int
    shoulder_right: int
    thigh_left: int
    thigh_right: int

class CombatInfo:
    ac_natural_bonus: int
    ac_armor_base: int
    ac_shield_base: int
    combat_mode: int
    target_state: int
    size_ab_modifier: int
    size_ac_modifier: int

class Common:
    resref: str
    tag: str
    name: LocString
    locals: LocalData
    location: Location
    comment: str
    palette_id: int

class CreatureScripts:
    on_attacked: str
    on_blocked: str
    on_conversation: str
    on_damaged: str
    on_death: str
    on_disturbed: str
    on_endround: str
    on_heartbeat: str
    on_perceived: str
    on_rested: str
    on_spawn: str
    on_spell_cast_at: str
    on_user_defined: str

class CreatureStats:
    def add_feat(self, feat: int) -> bool: ...
    def get_ability_score(self, id: int): ...
    def get_skill_rank(self, id: int): ...
    def has_feat(self, feat: int) -> bool: ...
    def remove_feat(self, feat: int): ...
    def set_ability_score(self, id: int, value: int) -> bool: ...
    def set_skill_rank(self, id: int, value: int) -> bool: ...

class DoorScripts:
    on_click: str
    on_closed: str
    on_damaged: str
    on_death: str
    on_disarm: str
    on_heartbeat: str
    on_lock: str
    on_melee_attacked: str
    on_open_failure: str
    on_open: str
    on_spell_cast_at: str
    on_trap_triggered: str
    on_unlock: str
    on_user_defined: str

class EquipSlot(enum.Flag):
    head = ...
    chest = ...
    boots = ...
    arms = ...
    righthand = ...
    lefthand = ...
    cloak = ...
    leftring = ...
    rightring = ...
    neck = ...
    belt = ...
    arrows = ...
    bullets = ...
    bolts = ...
    creature_left = ...
    creature_right = ...
    creature_bite = ...
    creature_skin = ...

class EquipIndex(enum.IntEnum):
    head = 0
    chest = 1
    boots = 2
    arms = 3
    righthand = 4
    lefthand = 5
    cloak = 6
    leftring = 7
    rightring = 8
    neck = 9
    belt = 10
    arrows = 11
    bullets = 12
    bolts = 13
    creature_left = 14
    creature_right = 15
    creature_bite = 16
    creature_skin = 17
    invalid = 4294967295

class Equips:
    equips: list[str | Item]
    def instantiate(self) -> None: ...

class InventoryItem:
    infinite: bool
    x: int
    y: int
    item: str | Item

class Inventory:
    items: list[InventoryItem]
    owner: ObjectBase
    def __len__(self) -> int: ...
    def instantiate(self) -> None: ...
    def add_item(self, item: Item) -> bool: ...
    def add_page(self) -> bool: ...
    def can_add_item(self, item: Item) -> bool: ...
    def debug(self) -> str: ...
    def items(self) -> list['Item']: ...
    def remove_item(self, item: Item) -> bool: ...
    def size(self) -> int: ...

class ClassEntry:
    id: int
    level: int
    spells: SpellBook

class LevelUp:
    class_: int
    ability: int
    epic: bool
    feats: list[int]
    hitpoints: int
    known_spells: list[tuple[int, int]]
    skillpoints: int
    skills: list[tuple[int, int]]

class LevelHistory:
    entries: list[LevelUp]

class LevelStats:
    entries: list[ClassEntry]
    def level(self) -> int: ...
    def level_by_class(self, class_: int) -> int: ...

class Location:
    area: int
    orientation: Vector3
    position: Vector3

class LocalData:
    def clear(self, varname: str, type: int): ...
    def clear_all(self, type: int): ...
    def delete_float(self, varname: str): ...
    def delete_int(self, varname: str): ...
    def delete_object(self, varname: str): ...
    def delete_string(self, varname: str): ...
    def delete_location(self, varname: str): ...
    def get_float(self, varname: str): ...
    def get_int(self, varname: str) -> int: ...
    def get_object(self, varname: str): ...
    def get_string(self, varname: str) -> str: ...
    def get_location(self, varname: str): ...
    def set_float(self, varname: str, value: float): ...
    def set_int(self, varname: str, value: int): ...
    def set_object(self, varname: str, value: ObjectHandle): ...
    def set_string(self, varname: str, value: str): ...
    def set_location(self, varname: str, value: Location): ...
    def size(self) -> None: ...

class Lock:
    key_name: str
    key_required: bool
    lockable: bool
    locked: bool
    lock_dc: int
    unlock_dc: int
    remove_key: bool

class Saves:
    fort: int
    reflex: int
    will: int

class SpellFlags(enum.Flag):
    none = 0
    readied = 1
    spontaneous = 2
    unlimited = 4

class SpellEntry:
    spell: int
    meta: int
    flags: SpellFlags

class SpellBook:
    def add_known_spell(self, level: int, entry: SpellEntry): ...
    def add_memorized_spell(self, level: int, entry: SpellEntry): ...
    def clear_memorized_spell(self, level: int, spell: int) -> None: ...
    def get_known_spell_count(self, level: int): ...
    def get_memorized_spell_count(self, level: int): ...
    def get_known_spell(self, level: int, index: int): ...
    def get_memorized_spell(self, level: int, index: int): ...
    def remove_known_spell(self, level: int, entry: SpellEntry): ...

class SpecialAbility:
    spell: int
    level: int
    flags: SpellFlags

class Trap:
    detect_dc: int
    detectable: bool
    disarm_dc: int
    disarmable: bool
    is_trapped: bool
    one_shot: bool
    type: int

class DialogNodeType(enum.IntEnum):
    entry = 0
    reply = 1

class DialogAnimation(enum.IntEnum):
    default = 0
    taunt = 28
    greeting = 29
    listen = 30
    worship = 33
    salute = 34
    bow = 35
    steal = 37
    talk_normal = 38
    talk_pleading = 39
    talk_forceful = 40
    talk_laugh = 41
    victory_1 = 44
    victory_2 = 45
    victory_3 = 46
    look_far = 48
    drink = 70
    read = 71
    none = 88

class DialogPtr:
    parent: Dialog
    type: DialogNodeType
    node: DialogNode
    script_appears: str
    is_start: bool
    is_link: bool
    comment: str
    def add_ptr(self, ptr: DialogPtr, is_link: bool = False) -> DialogPtr: ...
    def add_string(self, value: str, lang: LanguageID = ..., feminine: bool = False) -> DialogPtr: ...
    def add(self) -> DialogPtr: ...
    def copy(self) -> DialogPtr: ...
    def get_condition_param(self, key: str) -> str | None: ...
    def remove_condition_param(self, key: str): ...
    def remove_ptr(self, ptr: DialogPtr): ...
    def set_condition_param(self, key: str, value: str): ...

class DialogNode:
    parent: Dialog
    type: DialogNodeType
    comment: str
    quest: str
    speaker: str
    quest_entry: int
    script_action: str
    sound: str
    text: LocString
    animation: DialogAnimation
    delay: int
    pointers: list[DialogPtr]
    def copy(self) -> DialogNode: ...
    def get_action_param(self, key: str) -> str | None: ...
    def remove_action_param(self, key: str): ...
    def set_action_param(self, key: str, value: str): ...

class Dialog:
    json_archive_version: ClassVar[int]
    restype: ClassVar['ObjectType']
    script_abort: str
    script_end: str
    delay_entry: int
    delay_reply: int
    word_count: int
    prevent_zoom: bool
    def __init__(self) -> None: ...
    def __len__(self) -> int: ...
    def __getitem__(self, index: int) -> DialogPtr: ...
    def add(self) -> DialogPtr: ...
    def add_ptr(self, ptr: DialogPtr, is_link: bool = False) -> DialogPtr: ...
    def add_string(self, value: str, lang: LanguageID = ..., feminine: bool = False) -> DialogPtr: ...
    def delete_ptr(self, ptr: DialogPtr): ...
    def remove_ptr(self, ptr: DialogPtr): ...
    def save(self, path: str): ...
    def valid(self) -> bool: ...
    @staticmethod
    def from_file(path: str) -> Dialog: ...

class Image:
    def __init__(self, filename: str) -> None: ...
    def channels(self) -> int: ...
    def data(self) -> bytes: ...
    def height(self) -> int: ...
    def valid(self) -> bool: ...
    def width(self) -> int: ...
    def write_to(self) -> None: ...

class Ini:
    def __init__(self, filename: str) -> None: ...
    def get_int(self, key: str) -> int | None: ...
    def get_float(self, key: str) -> float | None: ...
    def get_str(self, key: str) -> str | None: ...
    def valid(self) -> None: ...

class PaletteNodeType(enum.IntEnum):
    branch = ...
    category = ...
    blueprint = ...

class PaletteTreeNode:
    def clear(self) -> None: ...
    type: PaletteNodeType
    id: int
    display: int
    name: str
    strref: int
    resref: str
    cr: float
    faction: str
    children: list['PaletteTreeNode']

class Palette:
    resource_type: ResourceType
    children: list[PaletteTreeNode]
    tileset: str
    def is_skeleton(self) -> bool: ...
    def save(self, path: str, format: str = 'json') -> None: ...
    def to_dict(self) -> dict: ...
    def valid(self) -> bool: ...
    @staticmethod
    def from_dict(value: dict): ...
    @staticmethod
    def from_file(path: str): ...

class PltLayer(enum.IntEnum):
    plt_layer_skin = 0
    plt_layer_hair = 1
    plt_layer_metal1 = 2
    plt_layer_metal2 = 3
    plt_layer_cloth1 = 4
    plt_layer_cloth2 = 5
    plt_layer_leather1 = 6
    plt_layer_leather2 = 7
    plt_layer_tattoo1 = 8
    plt_layer_tattoo2 = 9

class PltPixel: ...

class PltColors:
    colors: list[int]

class Plt:
    def height(self) -> None: ...
    def pixels(self) -> None: ...
    def valid(self) -> None: ...
    def width(self) -> None: ...

def decode_plt_color(plt: Plt, colors: PltColors, x: int, y: int) -> int: ...

class TwoDA:
    def __init__(self) -> None: ...
    def __init__(self, filename: str) -> None: ...
    def add_column(self, name: str) -> bool: ...
    def column_names(self) -> list[str]: ...
    def get(self, row: int, column: int | str): ...
    def get_raw(self, row: int, column: int) -> str: ...
    def set(self, row: int, column: int | str, value: int | float | str): ...
    @staticmethod
    def from_string(string: str) -> TwoDA: ...

class StaticTwoDA:
    def __init__(self, filename: str) -> None: ...
    def get(self, row: int, column: int | str): ...
    @staticmethod
    def from_string(string: str) -> StaticTwoDA: ...

class ObjectBase:
    def handle(self) -> None: ...

class ObjectType(enum.Enum):
    invalid = ...
    gui = ...
    tile = ...
    module = ...
    area = ...
    creature = ...
    item = ...
    trigger = ...
    projectile = ...
    placeable = ...
    door = ...
    areaofeffect = ...
    waypoint = ...
    encounter = ...
    store = ...
    portal = ...
    sound = ...

class ObjectHandle:
    type: ObjectType

class AreaFlags(enum.Flag):
    none = 0
    interior = 1
    underground = 2
    natural = 4

class Area:
    json_archive_version: ClassVar[int]
    object_type: ClassVar[int]
    comments: str
    creator_id: int
    creatures: list[Creature]
    doors: list[Door]
    encounters: list[Encounter]
    flags: AreaFlags
    height: int
    id: int
    items: list[Item]
    listen_check_mod: int
    loadscreen: int
    name: LocString
    no_rest: int
    placeables: list[Placeable]
    pvp: int
    scripts: AreaScripts
    shadow_opacity: int
    skybox: int
    sounds: list[Sound]
    spot_check_mod: int
    stores: list[Store]
    tiles: list[AreaTile]
    tileset_resref: str
    triggers: list[Trigger]
    version: int
    waypoints: list[Waypoint]
    weather: AreaWeather
    width: int

class AreaScripts:
    on_enter: str
    on_exit: str
    on_heartbeat: str
    on_user_defined: str

class AreaWeather:
    chance_lightning: int
    chance_rain: int
    chance_snow: int
    color_moon_ambient: int
    color_moon_diffuse: int
    color_moon_fog: int
    color_sun_ambient: int
    color_sun_diffuse: int
    color_sun_fog: int
    fog_clip_distance: int
    wind_power: int
    day_night_cycle: int
    is_night: int
    lighting_scheme: int
    fog_moon_amount: int
    moon_shadows: int
    fog_sun_amount: int
    sun_shadows: int

class Creature(ObjectBase):
    json_archive_version: ClassVar[int]
    object_type: ClassVar[int]
    appearance: CreatureAppearance
    bodybag: int
    chunk_death: int
    common: Common
    conversation: str
    cr: float
    cr_adjust: int
    decay_time: int
    deity: str
    description: LocString
    disarmable: int
    faction_id: int
    gender: int
    good_evil: int
    hp: int
    hp_current: int
    hp_max: int
    immortal: int
    interruptable: int
    lawful_chaotic: int
    levels: LevelStats
    lootable: int
    name_first: LocString
    name_last: LocString
    pc: int
    perception_range: float
    plot: int
    race: int
    scripts: CreatureScripts
    soundset: str
    starting_package: int
    stats: CreatureStats
    subrace: str
    walkrate: int
    @property
    def equipment(self) -> Equips: ...
    @property
    def history(self) -> LevelHistory: ...
    @property
    def inventory(self) -> Inventory: ...
    def save(self, path: str, format: str = 'json') -> None: ...
    @staticmethod
    def from_dict(value: dict): ...
    @staticmethod
    def from_file(path: str): ...

class DoorAnimationState(enum.Enum):
    closed = ...
    opened1 = ...
    opened2 = ...

class Door:
    json_archive_version: ClassVar[int]
    object_type: ClassVar[int]
    animation_state: DoorAnimationState
    appearance: int
    conversation: str
    description: LocString
    faction: int
    generic_type: int
    hardness: int
    hp: int
    hp_current: int
    interruptable: int
    linked_to: str
    linked_to_flags: int
    loadscreen: int
    lock: Lock
    plot: int
    portrait_id: int
    saves: Saves
    scripts: DoorScripts
    trap: Trap
    def save(self, path: str, format: str = 'json') -> None: ...
    @staticmethod
    def from_dict(value: dict): ...
    @staticmethod
    def from_file(path: str): ...

class EncounterScripts:
    on_entered: str
    on_exhausted: str
    on_exit: str
    on_heartbeat: str
    on_user_defined: str

class SpawnCreature:
    appearance: int
    cr: int
    resref: str
    single_spawn: bool

class SpawnPoint:
    orientation: Vector3
    position: Vector3

class Encounter:
    active: bool
    creatures: list[SpawnCreature]
    creatures_max: int
    creatures_recommended: int
    difficulty: int
    difficulty_index: int
    faction: int
    geometry: list[Vector3]
    player_only: bool
    reset: bool
    reset_time: int
    respawns: int
    scripts: EncounterScripts
    spawn_option: int
    spawn_points: list[SpawnPoint]
    def save(self, path: str, format: str = 'json') -> None: ...
    @staticmethod
    def from_dict(value: dict): ...
    @staticmethod
    def from_file(path: str): ...

class ItemModelType(enum.Enum):
    simple = ...
    layered = ...
    composite = ...
    armor = ...

class ItemColors(enum.Enum):
    cloth1 = ...
    cloth2 = ...
    leather1 = ...
    leather2 = ...
    metal1 = ...
    metal2 = ...

class ItemModelParts(enum.Enum):
    model1 = ...
    model2 = ...
    model3 = ...
    armor_belt = ...
    armor_lbicep = ...
    armor_lfarm = ...
    armor_lfoot = ...
    armor_lhand = ...
    armor_lshin = ...
    armor_lshoul = ...
    armor_lthigh = ...
    armor_neck = ...
    armor_pelvis = ...
    armor_rbicep = ...
    armor_rfarm = ...
    armor_rfoot = ...
    armor_rhand = ...
    armor_robe = ...
    armor_rshin = ...
    armor_rshoul = ...
    armor_rthigh = ...
    armor_torso = ...

class ItemProperty:
    type: int
    subtype: int
    cost_table: int
    cost_value: int
    param_table: int
    param_value: int

class Item:
    additional_cost: int
    baseitem: int
    charges: int
    cost: int
    cursed: bool
    description: LocString
    description_id: LocString
    identified: bool
    inventory: Inventory
    model_colors: list[int]
    model_parts: list[int]
    model_type: ItemModelType
    plot: bool
    properties: list[ItemProperty]
    stacksize: int
    stolen: bool
    def model_to_plt_colors(self) -> PltColors: ...
    def get_icon_by_part(self, part: ItemModelParts = ..., female: bool = False) -> Image: ...
    def save(self, path: str, format: str = 'json') -> None: ...
    @staticmethod
    def from_dict(value: dict): ...
    @staticmethod
    def from_file(path: str): ...

class Module:
    creator: int
    dawn_hour: int
    description: LocString
    dusk_hour: int
    entry_area: str
    entry_orientation: Vector3
    entry_position: Vector3
    expansion_pack: int
    haks: list[str]
    id: ByteString
    is_save_game: bool
    locals: LocalData
    min_game_version: int
    minutes_per_hour: int
    name: LocString
    scripts: ModuleScripts
    start_day: int
    start_hour: int
    start_month: int
    start_movie: str
    start_year: int
    tag: str
    tlk: str
    version: int
    xpscale: int
    def __iter__(self): ...
    def __len__(self) -> int: ...
    def area_count(self) -> int: ...
    def get_area(self, index: int) -> Area | None: ...
    @property
    def uuid(self) -> str: ...

class ModuleScripts:
    on_client_enter: str
    on_client_leave: str
    on_cutsnabort: str
    on_heartbeat: str
    on_item_acquire: str
    on_item_activate: str
    on_item_unaquire: str
    on_load: str
    on_player_chat: str
    on_player_death: str
    on_player_dying: str
    on_player_equip: str
    on_player_level_up: str
    on_player_rest: str
    on_player_uneqiup: str
    on_spawnbtndn: str
    on_start: str
    on_user_defined: str

class PlaceableAnimationState(enum.Enum):
    none = ...
    open = ...
    closed = ...
    destroyed = ...
    activated = ...
    deactivated = ...

class PlaceableScripts:
    on_click: str
    on_closed: str
    on_damaged: str
    on_death: str
    on_disarm: str
    on_heartbeat: str
    on_inventory_disturbed: str
    on_lock: str
    on_melee_attacked: str
    on_open: str
    on_spell_cast_at: str
    on_trap_triggered: str
    on_unlock: str
    on_used: str
    on_user_defined: str

class Placeable(ObjectBase):
    json_archive_version: ClassVar[int]
    object_type: ClassVar[int]
    animation_state: PlaceableAnimationState
    appearance: int
    bodybag: int
    common: Common
    conversation: str
    description: LocString
    faction: int
    hardness: int
    has_inventory: bool
    hp: int
    hp_current: int
    interruptable: bool
    inventory: Inventory
    lock: Lock
    plot: bool
    portrait_id: int
    saves: Saves
    scripts: PlaceableScripts
    static: bool
    trap: Trap
    useable: bool
    def save(self, path: str, format: str = 'json') -> None: ...
    @staticmethod
    def from_dict(value: dict): ...
    @staticmethod
    def from_file(path: str): ...

class Player(Creature):
    def save(self, path: str, format: str = 'json') -> None: ...

class Sound(ObjectBase):
    json_archive_version: ClassVar[int]
    object_type: ClassVar[int]
    active: bool
    common: Common
    continuous: bool
    distance_max: float
    distance_min: float
    elevation: float
    generated_type: int
    hours: int
    interval: int
    interval_variation: int
    looping: bool
    pitch_variation: float
    positional: bool
    priority: int
    random: bool
    random_position: bool
    random_x: float
    random_y: float
    sounds: list[str]
    times: int
    volume: int
    volume_variation: int
    def save(self, path: str, format: str = 'json') -> None: ...
    @staticmethod
    def from_dict(value: dict): ...
    @staticmethod
    def from_file(path: str): ...

class StoreScripts:
    on_closed: str
    on_opened: str

class Store(ObjectBase):
    json_archive_version: ClassVar[int]
    object_type: ClassVar[int]
    armor: Inventory
    blackmarket: bool
    blackmarket_markdown: int
    gold: int
    identify_price: int
    markdown: int
    markup: int
    max_price: int
    miscellaneous: Inventory
    potions: Inventory
    rings: Inventory
    scripts: StoreScripts
    weapons: Inventory
    def save(self, path: str, format: str = 'json') -> None: ...
    @staticmethod
    def from_dict(value: dict) -> Store: ...
    @staticmethod
    def from_file(path: str) -> Store: ...

class AreaTile:
    id: int
    height: int
    orientation: int
    animloop1: int
    animloop2: int
    animloop3: int
    mainlight1: int
    mainlight2: int
    srclight1: int
    srclight2: int

class TriggerScripts:
    on_click: str
    on_disarm: str
    on_enter: str
    on_exit: str
    on_heartbeat: str
    on_trap_triggered: str
    on_user_defined: str

class Trigger(ObjectBase):
    cursor: int
    faction: int
    geometry: list[Vector3]
    highlight_height: float
    linked_to: str
    linked_to_flags: int
    loadscreen: int
    portrait: int
    scripts: TriggerScripts
    trap: Trap
    type: int
    def save(self, path: str, format: str = 'json') -> None: ...
    @staticmethod
    def from_dict(value: dict) -> Trigger: ...
    @staticmethod
    def from_file(path: str) -> Trigger: ...

class Waypoint(ObjectBase):
    appearance: int
    description: LocString
    has_map_note: bool
    linked_to: str
    map_note: LocString
    map_note_enabled: bool
    def save(self, path: str, format: str = 'json') -> None: ...
    @staticmethod
    def from_dict(value: dict): ...
    @staticmethod
    def from_file(path: str): ...

class ResourceData: ...

class Erf:
    def __init__(self, path: str) -> None: ...
    def add(self, path) -> None: ...
    def extract_by_glob(self, glob: str, output: str) -> int: ...
    def extract(self, pattern, output) -> int: ...
    def erase(self, resource) -> None: ...
    def merge(self, container: Erf): ...
    def reload(self) -> None: ...
    def save(self) -> None: ...
    def save_as(self, path) -> None: ...
    def working_directory(self) -> str: ...

class AttackData:
    attacker: Creature
    target: ObjectBase
    type: int
    result: AttackResult
    target_state: int
    target_is_creature: bool
    is_ranged_attack: bool
    nth_attack: int
    attack_roll: int
    attack_bonus: int
    armor_class: int
    iteration_penalty: int
    multiplier: int
    threat_range: int
    concealment: int

class AttackResult(enum.IntEnum):
    hit_by_auto_success = ...
    hit_by_critical = ...
    hit_by_roll = ...
    miss_by_auto_fail = ...
    miss_by_concealment = ...
    miss_by_miss_chance = ...
    miss_by_roll = ...

class DamageCategory(IntFlag):
    none = 0
    penalty = ...
    critical = ...
    unblockable = ...

class DiceRoll:
    dice: int
    sides: int
    bonus: int

class EffectCategory(enum.IntEnum):
    magical = ...
    extraordinary = ...
    supernatural = ...
    item = ...
    innate = ...

class EffectID:
    version: int
    index: int

class EffectHandle:
    type: int
    subtype: int
    creator: ObjectHandle
    spell_id: int
    category: EffectCategory
    effect: Effect

class Effect:
    def clear(self) -> None: ...
    def get_float(self, index: int) -> float: ...
    def get_int(self, index: int) -> int: ...
    def get_string(self, index: int) -> str: ...
    def handle(self) -> EffectHandle: ...
    def id(self) -> EffectID: ...
    def set_float(self, index: int, value: float) -> None: ...
    def set_int(self, index: int, value: int) -> None: ...
    def set_string(self, index: int, value: str) -> None: ...
    def set_versus(self, vs) -> None: ...
    def versus(self) -> None: ...
