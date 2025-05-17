#include "glm/wrap_vmath.h"
#include "opaque_types.hpp"

#define NB_DEBUG 1
#include <nanobind/nanobind.h>
#include <nanobind/stl/filesystem.h>

#include <nw/util/platform.hpp>

namespace nb = nanobind;

void init_i18n(nb::module_& nw);
void init_formats(nb::module_& nw);
void init_objects(nb::module_& nw);
void init_resources(nb::module_& nw);
void init_rules(nb::module_& nw);
void init_serialization(nb::module_& nw);
void init_util(nb::module_& nw);
void init_kernel(nb::module_& kernel);
void init_model(nb::module_& nw);
void init_script(nb::module_& nw);

void init_core_scriptapi(nb::module_& m);
void init_nwn1(nb::module_& m);

NB_MODULE(_core, nw)
{
    nw.doc() = "rollnw python wrapper";

    bind_opaque_types(nw);
    // Initialize submodules
    init_i18n(nw);
    init_formats(nw);
    init_objects(nw);
    init_resources(nw);
    init_rules(nw);
    init_serialization(nw);
    init_util(nw);
    wrap_vmath(nw);

    nb::module_ kernel = nw.def_submodule("kernel");
    init_kernel(kernel);
    nb::module_ script = nw.def_submodule("script");
    init_script(script);
    nb::module_ model = nw.def_submodule("model");
    init_model(model);

    // Profiles - NWN1
    nb::module_ nwn1 = nw.def_submodule("nwn1");
    init_core_scriptapi(nwn1);
    init_nwn1(nwn1);
}
