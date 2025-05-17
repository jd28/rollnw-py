/***************************************************************************
 * Copyright (c) 2019, Martin Renou                                         *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/
// Converted to nanobind

#ifndef NANOBIND_JSON_HPP
#define NANOBIND_JSON_HPP

#include <nw/log.hpp>

#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nlohmann/json.hpp>

#include <cstdint>
#include <stdexcept>
#include <string>

namespace nb = nanobind;
namespace nl = nlohmann;

namespace nb_json {

// Convert nlohmann::json to nb::dict
inline nb::dict json_to_dict(const nl::json& j)
{
    if (!j.is_object()) {
        throw std::runtime_error("json_to_dict: JSON value is not an object");
    }

    nb::dict dict;
    for (auto& [key, value] : j.items()) {
        if (value.is_null()) {
            dict[nb::str(key.c_str())] = nb::none();
        } else if (value.is_boolean()) {
            dict[nb::str(key.c_str())] = nb::bool_(value.get<bool>());
        } else if (value.is_number_integer()) {
            dict[nb::str(key.c_str())] = nb::int_(value.get<nl::json::number_integer_t>());
        } else if (value.is_number_unsigned()) {
            dict[nb::str(key.c_str())] = nb::int_(value.get<nl::json::number_unsigned_t>());
        } else if (value.is_number_float()) {
            dict[nb::str(key.c_str())] = nb::float_(value.get<double>());
        } else if (value.is_string()) {
            dict[nb::str(key.c_str())] = nb::str(value.get<std::string>().c_str());
        } else if (value.is_object()) {
            dict[nb::str(key.c_str())] = json_to_dict(value);
        } else if (value.is_array()) {
            nb::list list;
            for (const auto& item : value) {
                if (item.is_object()) {
                    list.append(json_to_dict(item));
                } else if (item.is_null()) {
                    list.append(nb::none());
                } else if (item.is_boolean()) {
                    list.append(nb::bool_(item.get<bool>()));
                } else if (item.is_number_integer()) {
                    list.append(nb::int_(item.get<nl::json::number_integer_t>()));
                } else if (item.is_number_unsigned()) {
                    list.append(nb::int_(item.get<nl::json::number_unsigned_t>()));
                } else if (item.is_number_float()) {
                    list.append(nb::float_(item.get<double>()));
                } else if (item.is_string()) {
                    list.append(nb::str(item.get<std::string>().c_str()));
                } else {
                    throw std::runtime_error("json_to_dict: Unsupported JSON array value type");
                }
            }
            dict[nb::str(key.c_str())] = list;
        } else {
            throw std::runtime_error("json_to_dict: Unsupported JSON value type");
        }
    }
    return dict;
}

// Convert nb::dict to nlohmann::json
inline nl::json dict_to_json(const nb::dict& dict)
{
    nl::json j = nl::json::object();

    for (const auto [key, value] : dict) {
        if (!nb::isinstance<nb::str>(key)) { continue; }
        std::string key_str{nb::str(key).c_str()};

        if (value.is_none()) {
            j[key_str] = nullptr;
        } else if (nb::isinstance<nb::bool_>(value)) {
            j[key_str] = nb::cast<bool>(value);
        } else if (nb::isinstance<nb::int_>(value)) {
            try {
                j[key_str] = nb::cast<int64_t>(value);
            } catch (...) {
                // For very large integers that don't fit in int64_t
                try {
                    j[key_str] = nb::cast<uint64_t>(value);
                } catch (...) {
                    throw std::runtime_error("dict_to_json: Integer too large for JSON");
                }
            }
        } else if (nb::isinstance<nb::float_>(value)) {
            j[key_str] = nb::cast<double>(value);
        } else if (nb::isinstance<nb::str>(value)) {
            j[key_str] = nb::str(value).c_str();
        } else if (nb::isinstance<nb::dict>(value)) {
            j[key_str] = dict_to_json(nb::cast<nb::dict>(value));
        } else if (nb::isinstance<nb::list>(value) || nb::isinstance<nb::tuple>(value)) {
            nl::json array = nl::json::array();
            for (const nb::handle item : value) {
                if (item.is_none()) {
                    array.push_back(nullptr);
                } else if (nb::isinstance<nb::bool_>(item)) {
                    array.push_back(nb::cast<bool>(item));
                } else if (nb::isinstance<nb::int_>(item)) {
                    try {
                        array.push_back(nb::cast<int64_t>(item));
                    } catch (...) {
                        try {
                            array.push_back(nb::cast<uint64_t>(item));
                        } catch (...) {
                            throw std::runtime_error("dict_to_json: Integer in array too large for JSON");
                        }
                    }
                } else if (nb::isinstance<nb::float_>(item)) {
                    array.push_back(nb::cast<double>(item));
                } else if (nb::isinstance<nb::str>(item)) {
                    array.push_back(nb::str(item).c_str());
                } else if (nb::isinstance<nb::dict>(item)) {
                    array.push_back(dict_to_json(nb::cast<nb::dict>(item)));
                } else {
                    throw std::runtime_error("dict_to_json: Unsupported Python array item type");
                }
            }
            j[key_str] = array;
        } else {
            throw std::runtime_error("dict_to_json: Unsupported Python value type");
        }
    }
    return j;
}

} // namespace nb_json

// Type caster for nlohmann::json to enable automatic conversions in function arguments
namespace nanobind {
namespace detail {
template <>
struct type_caster<nl::json> {
public:
    NB_TYPE_CASTER(nl::json, const_name("json"))

    bool from_python(handle src, uint8_t, cleanup_list*)
    {
        if (!nb::isinstance<nb::dict>(src)) {
            return false;
        }

        try {
            value = nb_json::dict_to_json(nb::cast<nb::dict>(src));
            return true;
        } catch (...) {
            return false;
        }
    }

    static handle from_cpp(nl::json src, rv_policy, cleanup_list*)
    {
        if (!src.is_object()) {
            return nb::none().release();
        }

        try {
            nb::dict obj = nb_json::json_to_dict(src);
            return obj.release();
        } catch (...) {
            return nb::none().release();
        }
    }
};
}
}

#endif // NANOBIND_JSON_HPP
