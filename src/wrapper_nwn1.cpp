#include "casters.hpp"
#include "opaque_types.hpp"
#include "json/nanobind_json.hpp"

#include <nw/objects/Creature.hpp>
#include <nw/objects/Item.hpp>

#include <nw/profiles/nwn1/scriptapi.hpp>

#include <nanobind/nanobind.h>
#include <nlohmann/json.hpp>

#include <filesystem>

namespace nb = nanobind;

void init_nwn1(nb::module_& m)
{

    // ============================================================================
    // == Object ==================================================================
    // ============================================================================

    // == Object: Effects =========================================================
    // ============================================================================

    // == Object: Hit Points ======================================================
    // ============================================================================

    m.def("get_current_hitpoints", &nwn1::get_current_hitpoints);
    m.def("get_max_hitpoints", &nwn1::get_max_hitpoints);

    // == Object: Saves ============================================================
    // =============================================================================
    m.def("saving_throw", &nwn1::saving_throw);
    m.def("resolve_saving_throw", &nwn1::resolve_saving_throw);

    // == Abilities ===============================================================
    // ============================================================================
    m.def("get_ability_score", &nwn1::get_ability_score,
        nb::arg("obj"), nb::arg("ability"), nb::arg("base") = false);
    m.def("get_ability_modifier", &nwn1::get_ability_modifier,
        nb::arg("obj"), nb::arg("ability"), nb::arg("base") = false);
    m.def("get_dex_modifier", &nwn1::get_dex_modifier);

    // == Armor Class =============================================================
    // ============================================================================
    m.def("calculate_ac_versus", &nwn1::calculate_ac_versus,
        nb::arg("obj"), nb::arg("versus") = nullptr, nb::arg("is_touch_attack") = false);
    m.def("calculate_item_ac", &nwn1::calculate_item_ac);

    // == Creature: Casting =======================================================
    // ============================================================================

    m.def("add_known_spell", &nwn1::add_known_spell);
    m.def("add_memorized_spell", &nwn1::add_memorized_spell);
    m.def("compute_total_spell_slots", &nwn1::compute_total_spell_slots);
    m.def("compute_total_spells_knowable", &nwn1::compute_total_spells_knowable);
    m.def("get_available_spell_slots", &nwn1::get_available_spell_slots);
    m.def("get_available_spell_uses", &nwn1::get_available_spell_uses);
    m.def("get_caster_level", &nwn1::get_caster_level);
    m.def("get_spell_dc", &nwn1::get_spell_dc);
    m.def("recompute_all_availabe_spell_slots", &nwn1::recompute_all_availabe_spell_slots);
    m.def("remove_known_spell", &nwn1::remove_known_spell);

    // == Creature: Classes =======================================================
    // ============================================================================

    m.def("can_use_monk_abilities", &nwn1::can_use_monk_abilities);

    // == Creature: Combat ========================================================
    // ============================================================================

    m.def("base_attack_bonus", &nwn1::base_attack_bonus);
    m.def("calculate_challenge_rating", &nwn1::calculate_challenge_rating);
    m.def("equip_index_to_attack_type", &nwn1::equip_index_to_attack_type);
    m.def("get_weapon_by_attack_type", &nwn1::get_weapon_by_attack_type);
    m.def("is_flanked", &nwn1::is_flanked);

    m.def("resolve_attack", &nwn1::resolve_attack);
    m.def("resolve_attack_bonus", &nwn1::resolve_attack_bonus,
        nb::arg("obj"), nb::arg("type"), nb::arg("versus") = nullptr);
    m.def("resolve_attack_damage", &nwn1::resolve_attack_damage);
    m.def("resolve_attack_roll", &nwn1::resolve_attack);
    m.def("resolve_attack_type", &nwn1::resolve_attack_type);
    m.def("resolve_concealment", &nwn1::resolve_concealment);
    m.def("resolve_critical_multiplier", &nwn1::resolve_critical_multiplier);
    m.def("resolve_critical_threat", &nwn1::resolve_critical_threat);
    m.def("resolve_damage_modifiers", &nwn1::resolve_damage_modifiers);
    m.def("resolve_damage_immunity", &nwn1::resolve_damage_immunity);
    m.def("resolve_damage_reduction", &nwn1::resolve_damage_reduction);
    m.def("resolve_damage_resistance", &nwn1::resolve_damage_resistance);
    m.def("resolve_dual_wield_penalty", &nwn1::resolve_dual_wield_penalty);
    m.def("resolve_iteration_penalty", &nwn1::resolve_iteration_penalty);
    m.def("resolve_number_of_attacks", &nwn1::resolve_number_of_attacks, nb::arg("obj"));
    m.def("resolve_target_state", &nwn1::resolve_target_state);
    m.def("resolve_unarmed_damage", &nwn1::resolve_unarmed_damage);
    m.def("resolve_weapon_damage", &nwn1::resolve_weapon_damage);
    m.def("resolve_weapon_damage_flags", &nwn1::resolve_weapon_damage_flags);
    m.def("resolve_weapon_power", &nwn1::resolve_weapon_power);
    m.def("weapon_is_finessable", &nwn1::weapon_is_finessable);
    m.def("weapon_iteration", &nwn1::weapon_iteration);

    // == Creature: Equips ========================================================
    // ============================================================================
    m.def("can_equip_item", &nwn1::can_equip_item);
    m.def("equip_item", &nwn1::equip_item);
    m.def("get_equipped_item", &nwn1::get_equipped_item, nb::rv_policy::reference);
    m.def("unequip_item", &nwn1::unequip_item);

    // == Creature: Skills ========================================================
    // ============================================================================
    m.def("get_skill_rank", &nwn1::get_skill_rank);
    m.def("resolve_skill_check", &nwn1::resolve_skill_check);

    // == Creature: Special Abilities =============================================
    // ============================================================================
    m.def("add_special_ability", &nwn1::add_special_ability, nb::arg("obj"), nb::arg("ability"), nb::arg("level") = 0);
    m.def("clear_special_ability", &nwn1::clear_special_ability, nb::arg("obj"), nb::arg("ability"));
    m.def("get_has_special_ability", &nwn1::get_has_special_ability, nb::arg("obj"), nb::arg("ability"));
    m.def("get_special_ability_level", &nwn1::get_special_ability_level, nb::arg("obj"), nb::arg("ability"));
    m.def("get_special_ability_uses", &nwn1::get_special_ability_uses, nb::arg("obj"), nb::arg("ability"));
    m.def("set_special_ability_level", &nwn1::set_special_ability_level, nb::arg("obj"), nb::arg("ability"), nb::arg("level"));
    m.def("set_special_ability_uses", &nwn1::set_special_ability_uses, nb::arg("obj"), nb::arg("ability"), nb::arg("uses"), nb::arg("level") = 0);
    m.def("remove_special_ability", &nwn1::remove_special_ability, nb::arg("obj"), nb::arg("ability"));

    // == Items ===================================================================
    // ============================================================================
    m.def("is_ranged_weapon", &nwn1::is_ranged_weapon);
    m.def("is_shield", &nwn1::is_shield);
    m.def("calculate_item_value", &nwn1::calculate_item_value);

    // == Effects =================================================================
    // ============================================================================

    // == Effect Creation =========================================================
    // ============================================================================
    m.def("effect_ability_modifier", &nwn1::effect_ability_modifier,
        nb::arg("ability"), nb::arg("modifier"),
        R"(Creates an ability modifier effect.)");

    m.def("effect_armor_class_modifier", &nwn1::effect_armor_class_modifier,
        nb::arg("type"), nb::arg("modifier"),
        R"(Creates an armor class modifier effect.)");

    m.def("effect_attack_modifier", &nwn1::effect_attack_modifier,
        nb::arg("attack"), nb::arg("modifier"),
        R"(Creates an attack modifier effect.)");

    m.def("effect_bonus_spell_slot", &nwn1::effect_bonus_spell_slot,
        nb::arg("class_"), nb::arg("spell_level"),
        R"(Creates a bonus spell slot effect.)");

    m.def("effect_concealment", &nwn1::effect_concealment,
        nb::arg("value"), nb::arg("type") = nwn1::miss_chance_type_normal,
        R"(Creates a concealment effect.)");

    m.def("effect_damage_bonus", &nwn1::effect_damage_bonus,
        nb::arg("type"), nb::arg("dice"), nb::arg("cat") = nw::DamageCategory::none,
        R"(Creates a damage bonus effect.)");

    m.def("effect_damage_immunity", &nwn1::effect_damage_immunity,
        nb::arg("type"), nb::arg("value"),
        R"(Creates a damage immunity effect. Negative values create a vulnerability.)");

    m.def("effect_damage_penalty", &nwn1::effect_damage_penalty,
        nb::arg("type"), nb::arg("dice"),
        R"(Creates a damage penalty effect.)");

    m.def("effect_damage_reduction", &nwn1::effect_damage_reduction,
        nb::arg("value"), nb::arg("power"), nb::arg("max") = 0,
        R"(Creates a damage reduction effect.)");

    m.def("effect_damage_resistance", &nwn1::effect_damage_resistance,
        nb::arg("type"), nb::arg("value"), nb::arg("max") = 0,
        R"(Creates a damage resistance effect.)");

    m.def("effect_haste", &nwn1::effect_haste,
        R"(Creates a haste effect.)");

    m.def("effect_hitpoints_temporary", &nwn1::effect_hitpoints_temporary,
        nb::arg("amount"),
        R"(Creates temporary hitpoints effect.)");

    m.def("effect_miss_chance", &nwn1::effect_miss_chance,
        nb::arg("value"), nb::arg("type") = nwn1::miss_chance_type_normal,
        R"(Creates a miss chance effect.)");

    m.def("effect_save_modifier", &nwn1::effect_save_modifier,
        nb::arg("save"), nb::arg("modifier"), nb::arg("vs") = -1,
        R"(Creates a save modifier effect.)");

    m.def("effect_skill_modifier", &nwn1::effect_skill_modifier,
        nb::arg("skill"), nb::arg("modifier"),
        R"(Creates a skill modifier effect.)");

    // == Item Property Creation ==================================================
    // ============================================================================
    m.def("itemprop_ability_modifier", &nwn1::itemprop_ability_modifier);
    m.def("itemprop_armor_class_modifier", &nwn1::itemprop_armor_class_modifier);
    m.def("itemprop_attack_modifier", &nwn1::itemprop_attack_modifier);
    m.def("itemprop_bonus_spell_slot", &nwn1::itemprop_bonus_spell_slot);
    m.def("itemprop_damage_bonus", &nwn1::itemprop_damage_bonus);
    m.def("itemprop_enhancement_modifier", &nwn1::itemprop_enhancement_modifier);
    m.def("itemprop_haste", &nwn1::itemprop_haste);
    m.def("itemprop_keen", &nwn1::itemprop_keen);
    m.def("itemprop_save_modifier", &nwn1::itemprop_save_modifier);
    m.def("itemprop_save_vs_modifier", &nwn1::itemprop_save_vs_modifier);
    m.def("itemprop_skill_modifier", &nwn1::itemprop_skill_modifier);
}
