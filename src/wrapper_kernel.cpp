#include "casters.hpp"
#include "opaque_types.hpp"

#include <nw/kernel/EffectSystem.hpp>
#include <nw/kernel/Kernel.hpp>
#include <nw/kernel/Objects.hpp>
#include <nw/kernel/Rules.hpp>
#include <nw/kernel/TwoDACache.hpp>
#include <nw/objects/Area.hpp>
#include <nw/objects/Creature.hpp>
#include <nw/objects/Door.hpp>
#include <nw/objects/Encounter.hpp>
#include <nw/objects/Module.hpp>
#include <nw/objects/Placeable.hpp>
#include <nw/objects/Store.hpp>
#include <nw/objects/Trigger.hpp>
#include <nw/objects/Waypoint.hpp>
#include <nw/resources/ResourceManager.hpp>

#include <nanobind/nanobind.h>
#include <nanobind/stl/filesystem.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/string_view.h>

#include <filesystem>

namespace nb = nanobind;
namespace fs = std::filesystem;

void init_kernel_config(nb::module_& kernel)
{
    nb::class_<nw::ConfigOptions>(kernel, "ConfigOptions")
        .def(nb::init<>())
        .def_rw("include_install", &nw::ConfigOptions::include_install)
        .def_rw("include_user", &nw::ConfigOptions::include_user);

    nb::class_<nw::kernel::Config>(kernel, "Config")
        .def("initialize", [](const nw::ConfigOptions& options) {
            nw::kernel::config().initialize(options);
        })
        .def("install_path", &nw::kernel::Config::install_path)
        .def("options", &nw::kernel::Config::options)
        .def("user_path", &nw::kernel::Config::user_path)
        .def("set_paths", &nw::kernel::Config::set_paths)
        .def("set_version", &nw::kernel::Config::set_version)
        .def("version", &nw::kernel::Config::version);

    kernel.def(
        "config", []() {
            return &nw::kernel::config();
        },
        nb::rv_policy::reference);
}

void init_kernel_effects(nb::module_& kernel)
{
    nb::class_<nw::kernel::EffectSystemStats>(kernel, "EffectSystemStats")
        .def_ro("free_list_size", &nw::kernel::EffectSystemStats::free_list_size)
        .def_ro("pool_size", &nw::kernel::EffectSystemStats::pool_size);

    nb::class_<nw::kernel::EffectSystem>(kernel, "EffectSystem")
        // Unexposed:
        // - Effect* generate(const ItemProperty& property, EquipIndex index, BaseItem baseitem) const;
        // - virtual void initialize() override;
        // - virtual void clear() override;
        .def("add_effect", nb::overload_cast<nw::EffectType, nw::kernel::EffectFunc, nw::kernel::EffectFunc>(&nw::kernel::EffectSystem::add))
        .def("add_itemprop", nb::overload_cast<nw::ItemPropertyType, nw::kernel::ItemPropFunc>(&nw::kernel::EffectSystem::add))
        .def("apply", &nw::kernel::EffectSystem::apply)
        .def("create", &nw::kernel::EffectSystem::create, nb::rv_policy::reference)
        .def("destroy", &nw::kernel::EffectSystem::destroy)
        .def("ip_cost_table", &nw::kernel::EffectSystem::ip_cost_table)
        .def("ip_definition", &nw::kernel::EffectSystem::ip_definition)
        .def("ip_definitions", &nw::kernel::EffectSystem::ip_definitions)
        .def("ip_param_table", &nw::kernel::EffectSystem::ip_param_table)
        .def("itemprops", &nw::kernel::EffectSystem::itemprops)
        .def("remove", &nw::kernel::EffectSystem::remove)
        .def("stats", &nw::kernel::EffectSystem::stats);

    kernel.def(
        "effects", []() {
            return &nw::kernel::effects();
        },
        nb::rv_policy::reference);
}

template <typename T>
T* load_object_helper(nw::kernel::ObjectSystem& self, std::string_view resref)
{
    return self.load<T>(resref);
}

template <typename T>
T* load_object_helper_fs(nw::kernel::ObjectSystem& self, const fs::path& path, nw::SerializationProfile profile)
{
    return self.load_file<T>(path, profile);
}

void init_kernel_objects(nb::module_& kernel)
{
    nb::class_<nw::kernel::ObjectSystem>(kernel, "Objects")
        .def("area", &nw::kernel::ObjectSystem::make_area,
            nb::rv_policy::reference_internal)
        .def("creature", &load_object_helper<nw::Creature>,
            nb::rv_policy::reference_internal)
        .def("destroy", &nw::kernel::ObjectSystem::destroy)
        .def("door", &load_object_helper<nw::Door>,
            nb::rv_policy::reference_internal)
        .def("encounter", &load_object_helper<nw::Encounter>,
            nb::rv_policy::reference_internal)
        .def("get", &nw::kernel::ObjectSystem::get_object_base,
            nb::rv_policy::reference_internal)
        .def("get_by_tag", &nw::kernel::ObjectSystem::get_by_tag,
            nb::arg("tag"), nb::arg("nth") = 0,
            nb::rv_policy::reference_internal)
        .def("item", &load_object_helper<nw::Item>,
            nb::rv_policy::reference_internal)
        .def("placeable", &load_object_helper<nw::Placeable>,
            nb::rv_policy::reference_internal)
        .def("store", &load_object_helper<nw::Store>,
            nb::rv_policy::reference_internal)
        .def("trigger", &load_object_helper<nw::Trigger>,
            nb::rv_policy::reference_internal)
        .def("valid", &nw::kernel::ObjectSystem::valid)
        .def("waypoint", &load_object_helper<nw::Waypoint>,
            nb::rv_policy::reference_internal);

    kernel.def(
        "objects", []() {
            return &nw::kernel::objects();
        },
        nb::rv_policy::reference);
}

void init_kernel_resman(nb::module_& kernel)
{
    nb::class_<nw::ResourceManager>(kernel, "ResourceManager")
        .def("contains", [](const nw::ResourceManager& self, std::string_view res) {
            return self.contains(nw::Resource::from_filename(res));
        })
        .def("demand", [](const nw::ResourceManager& self, std::string_view res) {
            return self.demand(nw::Resource::from_filename(res));
        })
        .def("texture", &nw::ResourceManager::texture);

    kernel.def(
        "resman", []() {
            return &nw::kernel::resman();
        },
        nb::rv_policy::reference);
}

void init_kernel_rules(nb::module_& kernel)
{
    nb::class_<nw::kernel::Rules>(kernel, "Rules");
    kernel.def(
        "rules", []() {
            return &nw::kernel::rules();
        },
        nb::rv_policy::reference);
}

void init_kernel_strings(nb::module_& kernel)
{
    nb::class_<nw::kernel::Strings>(kernel, "Strings");
    kernel.def(
        "strings", []() {
            return &nw::kernel::strings();
        },
        nb::rv_policy::reference);
}

void init_kernel_twoda_cache(nb::module_& kernel)
{
    nb::class_<nw::kernel::TwoDACache>(kernel, "TwoDACache")
        .def("get", nb::overload_cast<std::string_view>(&nw::kernel::TwoDACache::get),
            nb::rv_policy::reference_internal)
        .def("get", nb::overload_cast<const nw::Resource&>(&nw::kernel::TwoDACache::get),
            nb::rv_policy::reference_internal);

    kernel.def(
        "twodas", []() {
            return &nw::kernel::twodas();
        },
        nb::rv_policy::reference);
}

void init_kernel(nb::module_& kernel)
{
    init_kernel_config(kernel);
    init_kernel_effects(kernel);
    init_kernel_objects(kernel);
    init_kernel_resman(kernel);
    init_kernel_rules(kernel);
    init_kernel_strings(kernel);
    init_kernel_twoda_cache(kernel);

    kernel.def("load_module", [](const std::string& path, bool instantiate = true) -> nw::Module* { return nw::kernel::load_module(path, instantiate); }, nb::arg("path"), nb::arg("instantiate") = true, nb::rv_policy::reference);
    kernel.def("unload_module", &nw::kernel::unload_module);

    kernel.def("start", []() {
              nw::kernel::config().initialize();
              nw::kernel::services().start();
          })
        .def("start", [](const nw::ConfigOptions& config) {
            nw::kernel::config().initialize(config);
            nw::kernel::services().start();
        });
}
