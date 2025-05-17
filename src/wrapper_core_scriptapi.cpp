#include "casters.hpp"

#include "nw/objects/Creature.hpp"
#include "nw/objects/Item.hpp"
#include "nw/objects/ObjectBase.hpp"
#include "nw/rules/Effect.hpp"
#include "nw/rules/items.hpp"
#include "nw/scriptapi.hpp"

#include <nanobind/nanobind.h>

namespace nb = nanobind;

void init_core_scriptapi(nb::module_& m)
{
    m.def("create_object", &nw::create_object);
    m.def("destroy_object", &nw::destroy_object);

    m.def("apply_effect", &nw::apply_effect, nb::arg("obj"), nb::arg("effect"));
    m.def("has_effect_applied", &nw::has_effect_applied, nb::arg("obj"), nb::arg("type"), nb::arg("subtype") = -1);
    m.def("remove_effect", &nw::remove_effect, nb::arg("obj"), nb::arg("effect"), nb::arg("destroy") = true);
    m.def("remove_effects_by", &nw::remove_effects_by, nb::arg("obj"), nb::arg("creator"));

    m.def("count_feats_in_range", &nw::count_feats_in_range, nb::arg("obj"), nb::arg("start"), nb::arg("end"));
    m.def("get_all_available_feats", &nw::get_all_available_feats, nb::arg("obj"));
    m.def("has_feat_successor", &nw::has_feat_successor, nb::arg("obj"), nb::arg("feat"));
    m.def("highest_feat_in_range", &nw::highest_feat_in_range, nb::arg("obj"), nb::arg("start"), nb::arg("end"));
    m.def("knows_feat", &nw::knows_feat, nb::arg("obj"), nb::arg("feat"));

    m.def("item_has_property", &nw::item_has_property, nb::arg("item"), nb::arg("type"), nb::arg("subtype") = -1);
    m.def("itemprop_to_string", &nw::itemprop_to_string, nb::arg("ip"));
}
