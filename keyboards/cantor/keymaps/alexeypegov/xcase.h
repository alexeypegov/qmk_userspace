#pragma once

#include "quantum.h"

#ifndef OS_LSFT
#    define OS_LSFT OSM(MOD_LSFT)
#endif
#ifndef OS_RSFT
#    define OS_RSFT OSM(MOD_RSFT)
#endif

enum xcase_keycodes {
    XCASE_SNAKE = SAFE_RANGE,
    XCASE_KEBAB,
    XCASE_CAMEL,
    XCASE_OFF,
    XCASE_SAFE_RANGE
};

#define XC_SNK XCASE_SNAKE
#define XC_KBB XCASE_KEBAB
#define XC_CML XCASE_CAMEL
#define XC_OFF XCASE_OFF

void enable_xcase_with(uint16_t delimiter);
void disable_xcase(void);
bool is_xcase_active(void);
void add_xcase_exclusion_keycode(uint16_t keycode);
void remove_xcase_exclusion_keycode(uint16_t keycode);
bool is_xcase_exclusion_keycode(uint16_t keycode);
bool process_record_xcase(uint16_t keycode, keyrecord_t *record);
