#include "opaque_types.hpp"

#include <nanobind/stl/bind_vector.h>
#include <nw/objects/Item.hpp>

namespace nb = nanobind;

void bind_opaque_types(nb::module_& m)
{
    nb::bind_vector<std::vector<int64_t>>(m, "Int64Vector");
    nb::bind_vector<std::vector<int32_t>>(m, "Int32Vector");
    nb::bind_vector<std::vector<int16_t>>(m, "Int16Vector");
    nb::bind_vector<std::vector<int8_t>>(m, "Int8Vector");
    nb::bind_vector<std::vector<uint64_t>>(m, "UInt64Vector");
    nb::bind_vector<std::vector<uint32_t>>(m, "UInt32Vector");
    nb::bind_vector<std::vector<uint16_t>>(m, "UInt16Vector");
    nb::bind_vector<std::vector<uint8_t>>(m, "UInt8Vector");
    nb::bind_vector<std::vector<std::string>>(m, "StringVector");
    nb::bind_vector<std::vector<glm::vec3>>(m, "Vec3Vector");
    nb::bind_vector<std::vector<nw::model::Vertex>>(m, "VertexVector");
    nb::bind_vector<std::vector<nw::model::SkinVertex>>(m, "SkinVertexVector");
    nb::bind_vector<std::vector<nw::model::Node*>>(m, "NodePtrVector");
    nb::bind_vector<std::vector<nw::ClassEntry>>(m, "ClassEntryVector");
    nb::bind_vector<std::vector<nw::InventoryItem>>(m, "InventoryItemVector");
    nb::bind_vector<std::vector<nw::LevelUp>>(m, "LevelUpVector");
    nb::bind_vector<std::vector<nw::Resref>>(m, "ResrefVector");
    nb::bind_vector<std::vector<nw::AreaTile>>(m, "AreaTileVector");

    nb::bind_vector<std::vector<nw::Area*>>(m, "AreaVector");
    nb::bind_vector<std::vector<nw::Creature*>>(m, "CreatureVector");
    nb::bind_vector<std::vector<nw::Door*>>(m, "DoorVector");
    nb::bind_vector<std::vector<nw::Encounter*>>(m, "EncounterVector");
    nb::bind_vector<std::vector<nw::Item*>>(m, "ItemVector");
    nb::bind_vector<std::vector<nw::Placeable*>>(m, "PlaceableVector");
    nb::bind_vector<std::vector<nw::Sound*>>(m, "SoundVector");
    nb::bind_vector<std::vector<nw::Store*>>(m, "StoreVector");
    nb::bind_vector<std::vector<nw::Trigger*>>(m, "TriggerVector");
    nb::bind_vector<std::vector<nw::Waypoint*>>(m, "WaypointVector");
    nb::bind_vector<std::vector<nw::script::Symbol>>(m, "SymbolVector");
    nb::bind_vector<std::vector<nw::DialogPtr*>>(m, "DialogVector");
}
