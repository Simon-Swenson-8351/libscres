#ifndef SC_DAT_UNIT_H
#define SC_DAT_UNIT_H

#include "scres_err.h"
#include "dyn_ary.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <inttypes.h>

const size_t DAT_UNIT_ENTRY_COUNT = 228;
const size_t DAT_UNIT_TBL_EXP = 8;
const size_t DAT_UNIT_UNIT_START = 0;
const size_t DAT_UNIT_UNIT_END = 106;
const size_t DAT_UNIT_STRUCTURE_START = 106;
const size_t DAT_UNIT_STRUCTURE_END = 202;
const size_t DAT_UNIT_OTHER_START = 202;
const size_t DAT_UNIT_OTHER_END = DAT_UNIT_ENTRY_COUNT;

typedef enum dat_unit_type {
    DAT_UNIT_TYPE_MAN,
    DAT_UNIT_TYPE_STRUCTURE,
    DAT_UNIT_TYPE_OTHER,
} dat_unit_type_t;

typedef enum dat_unit_size {
    DAT_UNIT_SIZE_INDEPENDENT,
    DAT_UNIT_SIZE_SMALL,
    DAT_UNIT_SIZE_MEDIUM,
    DAT_UNIT_SIZE_LARGE
} dat_unit_size_t;

typedef enum dat_unit_elev {
    DAT_UNIT_ELEV_BELOW_GND_0,
    DAT_UNIT_ELEV_BELOW_GND_1,
    DAT_UNIT_ELEV_GND_0,
    DAT_UNIT_ELEV_GND_1,
    DAT_UNIT_ELEV_GND_2,
    DAT_UNIT_ELEV_GND_3,
    DAT_UNIT_ELEV_GND_4,
    DAT_UNIT_ELEV_GND_5,
    DAT_UNIT_ELEV_GND_6,
    DAT_UNIT_ELEV_GND_7,
    DAT_UNIT_ELEV_GND_8,
    DAT_UNIT_ELEV_GND_9,
    DAT_UNIT_ELEV_AIR_0,
    DAT_UNIT_ELEV_AIR_1,
    DAT_UNIT_ELEV_AIR_2,
    DAT_UNIT_ELEV_AIR_3,
    DAT_UNIT_ELEV_AIR_4,
    DAT_UNIT_ELEV_AIR_5,
    DAT_UNIT_ELEV_AIR_6,
    DAT_UNIT_ELEV_AIR_7,
} dat_unit_elev_t;

typedef struct dat_unit_weapon {
    uint8_t weapon_id;
    uint8_t max_hits;
} dat_unit_weapon_t;

typedef struct dat_unit {
    uint8_t flingy_id;
    uint16_t sub_unit_ids[2];
    uint32_t construction_image_id;
    uint8_t direction;
    uint8_t shields_flag;
    uint16_t max_shields;
    uint32_t max_hp;
    uint8_t elevation;
    uint8_t old_movement; // ???
    uint8_t sub_label_stat_txt_id;
    struct {
        uint8_t comp_ai_idle;
        uint8_t human_ai_idle;
        uint8_t return_to_idle;
        uint8_t attack_unit;
        uint8_t attack_move;
    } order_ids;
    struct {
        dat_unit_weapon_t ground;
        dat_unit_weapon_t air;
    } weapons;
    union {
        uint8_t bytes;
        struct {
            uint8_t ignore_strategic_suicide :1;
            uint8_t ignore_guard             :1;
            uint8_t unused_04                :1;
            uint8_t unused_08                :1;
            uint8_t unused_10                :1;
            uint8_t unused_20                :1;
            uint8_t unused_40                :1;
            uint8_t unused_80                :1;
        } bits;
    } ai_flags;
    union {
        uint32_t bytes;
        struct {
            uint32_t building            :1;
            uint32_t addon               :1;
            uint32_t flier               :1;
            uint32_t worker              :1;
            uint32_t sub_unit            :1;
            uint32_t flying_building     :1;
            uint32_t hero                :1;
            uint32_t regenerates_hp      :1;
            uint32_t animated_idle       :1;
            uint32_t cloakable           :1;
            uint32_t two_units_per_egg   :1;
            uint32_t single_entity       :1;
            uint32_t resource_dropoff    :1;
            uint32_t resource_container  :1;
            uint32_t robotic             :1;
            uint32_t detector            :1;
            uint32_t organic             :1;
            uint32_t requires_creep      :1;
            uint32_t unused_00040000     :1;
            uint32_t requires_psi        :1;
            uint32_t burrowable          :1;
            uint32_t spellcaster         :1;
            uint32_t permanent_cloak     :1;
            uint32_t pickup_item         :1;
            uint32_t ignore_supply_check :1;
            uint32_t use_medium_overlays :1;
            uint32_t use_large_overlays  :1;
            uint32_t battle_reactions    :1;
            uint32_t full_auto_attack    :1;
            uint32_t invincible          :1;
            uint32_t mechanical          :1;
            uint32_t produces_units      :1;
        } bits;
    } ability_flags;
    uint8_t acquisition_range;
    uint8_t sight_range;
    uint8_t armor_upgrade_id;
    uint8_t armor;
    uint8_t right_click_action;
    struct {
        uint16_t what_start;
        uint16_t what_end;
    } sfx_ids;
    struct {
        uint8_t enum_val;
        uint16_t left[4];
        uint16_t up;
        uint16_t right;
        uint16_t down;
    } unit_size;
    uint16_t portrait_id;
    struct {
        uint16_t minerals;
        uint16_t vespene;
        uint16_t time;
        uint16_t requirements;
    } construction;
    struct {
        uint16_t width[2];
        uint16_t height;
        union {
            uint8_t bytes;
            struct {
                uint8_t zerg        :1;
                uint8_t terran      :1;
                uint8_t protoss     :1;
                uint8_t man         :1;
                uint8_t building    :1;
                uint8_t factory     :1;
                uint8_t independent :1;
                uint8_t neutral     :1;
            } bits;
        } group_flags;
        union {
            uint16_t bytes;
            struct {
                uint16_t non_neutral           :1;
                uint16_t unit_listing          :1;
                uint16_t mission_briefing      :1;
                uint16_t player_settings       :1;
                uint16_t all_races             :1;
                uint16_t set_doodad_state      :1;
                uint16_t non_location_triggers :1;
                uint16_t unit_settings         :1;
                uint16_t location_triggers     :1;
                uint16_t brood_war             :1;
                uint16_t unused_0400           :1;
                uint16_t unused_0800           :1;
                uint16_t unused_1000           :1;
                uint16_t unused_2000           :1;
                uint16_t unused_4000           :1;
                uint16_t unused_8000           :1;
            } bits;
        } avail_flags;
    } star_edit;
    struct {
        uint8_t provided;
        uint8_t required;
    } supply;
    struct {
        uint8_t slots_required;
        uint8_t slots_provided;
    } transport;
    struct {
        uint16_t build;
        uint16_t destroy;
    } score;
    uint16_t unit_map_str;
    uint8_t brood_war_flag;

    dat_unit_type_t type;
    union {
        struct {
            struct {
                uint16_t ready;
                uint16_t pissed_start;
                uint16_t pissed_end;
                uint16_t yes_start;
                uint16_t yes_end;
            } sfx_ids;
        } man_data;
        struct {
            uint16_t infestation_unit_id;
            uint16_t addon_horizontal_pos[2];
            uint16_t addon_vertical_pos;
        } structure_data;
    } typed_data;

} dat_unit_t;

typedef dat_unit_t dat_unit_ary_t[DAT_UNIT_ENTRY_COUNT];

#ifdef __cplusplus
}
#endif

#endif // #ifndef SC_DAT_UNIT_H