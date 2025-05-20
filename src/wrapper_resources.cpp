#include "casters.hpp"

#include <nw/resources/Container.hpp>
#include <nw/resources/Erf.hpp>
#include <nw/resources/ResourceManager.hpp>
#include <nw/resources/StaticDirectory.hpp>
#include <nw/resources/StaticKey.hpp>
#include <nw/resources/StaticZip.hpp>
#include <nw/resources/assets.hpp>
#include <nw/util/string.hpp>

#include <fmt/format.h>
#include <nanobind/nanobind.h>
#include <nanobind/operators.h>
#include <nanobind/stl/filesystem.h>
#include <nanobind/stl/string.h>

#include <string>

namespace nb = nanobind;

void init_resources_data(nb::module_& nw)
{
    nb::class_<nw::ResourceData>(nw, "ResourceData")
        .def_rw("name", &nw::ResourceData::name)
        .def_rw("bytes", &nw::ResourceData::bytes);
}

void init_resources_container(nb::module_& nw)
{
    nb::class_<nw::Container>(nw, "Container")
        .def("name", &nw::Container::name)
        .def("path", &nw::Container::path)
        .def("size", &nw::Container::size)
        .def("valid", &nw::Container::valid);
}

void init_resources_erf(nb::module_& nw)
{
    nb::class_<nw::Erf>(nw, "Erf")
        .def(nb::init<>())
        .def(nb::init<std::filesystem::path>())
        //.def("add", static_cast<bool (nw::Erf::*)(nw::Resource res, const nw::ByteArray&)>(&nw::Erf::add))
        .def("add", static_cast<bool (nw::Erf::*)(const std::filesystem::path&)>(&nw::Erf::add))
        .def("erase", &nw::Erf::erase)
        .def("merge", static_cast<bool (nw::Erf::*)(const nw::Erf&)>(&nw::Erf::merge))
        .def("reload", &nw::Erf::reload)
        .def("save", &nw::Erf::save)
        .def("save_as", &nw::Erf::save_as)

        .def_rw("description", &nw::Erf::description)

        .def("demand", [](const nw::Erf& self, std::string_view name) {
            return self.demand(nw::Resource::from_filename(name));
        })
        .def("name", &nw::Erf::name)
        .def("path", &nw::Erf::path)
        .def("size", &nw::Erf::size)
        .def("valid", &nw::Erf::valid);
}

void init_resource_manager(nb::module_& kernel)
{
    nb::class_<nw::ResourceManager>(kernel, "ResourceManager")
        .def("demand", [](const nw::ResourceManager& self, std::string_view name) {
            return self.demand(nw::Resource::from_filename(name));
        })
        .def("demand_server_vault", &nw::ResourceManager::demand_server_vault)
        .def("texture", &nw::ResourceManager::texture);
}

void init_resources(nb::module_& nw)
{
    nb::enum_<nw::ResourceType::type>(nw, "ResourceType", nb::is_arithmetic())
        .value("invalid", nw::ResourceType::invalid)
        .value("container", nw::ResourceType::container)
        .value("gff_archive", nw::ResourceType::gff_archive)
        .value("movie", nw::ResourceType::movie)
        .value("player", nw::ResourceType::player)
        .value("sound", nw::ResourceType::sound)
        .value("texture", nw::ResourceType::texture)
        .value("json", nw::ResourceType::json)
        .value("bmp", nw::ResourceType::bmp)
        .value("mve", nw::ResourceType::mve)
        .value("tga", nw::ResourceType::tga)
        .value("wav", nw::ResourceType::wav)
        .value("plt", nw::ResourceType::plt)
        .value("ini", nw::ResourceType::ini)
        .value("bmu", nw::ResourceType::bmu)
        .value("mpg", nw::ResourceType::mpg)
        .value("txt", nw::ResourceType::txt)
        .value("plh", nw::ResourceType::plh)
        .value("tex", nw::ResourceType::tex)
        .value("mdl", nw::ResourceType::mdl)
        .value("thg", nw::ResourceType::thg)
        .value("fnt", nw::ResourceType::fnt)
        .value("lua", nw::ResourceType::lua)
        .value("slt", nw::ResourceType::slt)
        .value("nss", nw::ResourceType::nss)
        .value("ncs", nw::ResourceType::ncs)
        .value("mod", nw::ResourceType::mod)
        .value("are", nw::ResourceType::are)
        .value("set", nw::ResourceType::set)
        .value("ifo", nw::ResourceType::ifo)
        .value("bic", nw::ResourceType::bic)
        .value("wok", nw::ResourceType::wok)
        .value("twoda", nw::ResourceType::twoda)
        .value("tlk", nw::ResourceType::tlk)
        .value("txi", nw::ResourceType::txi)
        .value("git", nw::ResourceType::git)
        .value("bti", nw::ResourceType::bti)
        .value("uti", nw::ResourceType::uti)
        .value("btc", nw::ResourceType::btc)
        .value("utc", nw::ResourceType::utc)
        .value("dlg", nw::ResourceType::dlg)
        .value("itp", nw::ResourceType::itp)
        .value("btt", nw::ResourceType::btt)
        .value("utt", nw::ResourceType::utt)
        .value("dds", nw::ResourceType::dds)
        .value("bts", nw::ResourceType::bts)
        .value("uts", nw::ResourceType::uts)
        .value("ltr", nw::ResourceType::ltr)
        .value("gff", nw::ResourceType::gff)
        .value("fac", nw::ResourceType::fac)
        .value("bte", nw::ResourceType::bte)
        .value("ute", nw::ResourceType::ute)
        .value("btd", nw::ResourceType::btd)
        .value("utd", nw::ResourceType::utd)
        .value("btp", nw::ResourceType::btp)
        .value("utp", nw::ResourceType::utp)
        .value("dft", nw::ResourceType::dft)
        .value("gic", nw::ResourceType::gic)
        .value("gui", nw::ResourceType::gui)
        .value("css", nw::ResourceType::css)
        .value("ccs", nw::ResourceType::ccs)
        .value("btm", nw::ResourceType::btm)
        .value("utm", nw::ResourceType::utm)
        .value("dwk", nw::ResourceType::dwk)
        .value("pwk", nw::ResourceType::pwk)
        .value("btg", nw::ResourceType::btg)
        .value("utg", nw::ResourceType::utg)
        .value("jrl", nw::ResourceType::jrl)
        .value("sav", nw::ResourceType::sav)
        .value("utw", nw::ResourceType::utw)
        .value("fourpc", nw::ResourceType::fourpc)
        .value("ssf", nw::ResourceType::ssf)
        .value("hak", nw::ResourceType::hak)
        .value("nwm", nw::ResourceType::nwm)
        .value("bik", nw::ResourceType::bik)
        .value("ndb", nw::ResourceType::ndb)
        .value("ptm", nw::ResourceType::ptm)
        .value("ptt", nw::ResourceType::ptt)
        .value("bak", nw::ResourceType::bak)
        .value("dat", nw::ResourceType::dat)
        .value("shd", nw::ResourceType::shd)
        .value("xbc", nw::ResourceType::xbc)
        .value("wbm", nw::ResourceType::wbm)
        .value("mtr", nw::ResourceType::mtr)
        .value("ktx", nw::ResourceType::ktx)
        .value("ttf", nw::ResourceType::ttf)
        .value("sql", nw::ResourceType::sql)
        .value("tml", nw::ResourceType::tml)
        .value("sq3", nw::ResourceType::sq3)
        .value("lod", nw::ResourceType::lod)
        .value("gif", nw::ResourceType::gif)
        .value("png", nw::ResourceType::png)
        .value("jpg", nw::ResourceType::jpg)
        .value("caf", nw::ResourceType::caf)
        .value("ids", nw::ResourceType::ids)
        .value("erf", nw::ResourceType::erf)
        .value("bif", nw::ResourceType::bif)
        .value("key", nw::ResourceType::key)
        .export_values();

    nw.def("restype_from_extension", &nw::ResourceType::from_extension, nb::arg("ext"));
    nw.def("restype_to_string", &nw::ResourceType::to_string, nb::arg("value"));

    init_resources_data(nw);
    init_resources_container(nw);
    init_resources_erf(nw);
}
