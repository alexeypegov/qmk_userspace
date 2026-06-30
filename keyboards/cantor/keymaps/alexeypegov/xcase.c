/* Simple xcase implementation
* Replaces spaces with delimiters for snake_case, kebab-case, camelCase
*/

#include "xcase.h"


// private variables
static bool xcase_active = false;
static uint16_t xcase_delimiter = KC_UNDS;
static uint16_t last_keycode = KC_NO;

#define MAX_EXCLUSION_KEYCODES 16
static uint16_t exclusion_keycodes[MAX_EXCLUSION_KEYCODES];
static uint8_t exclusion_keycode_count = 0;


// public functions

bool is_xcase_active(void) {
    return xcase_active;
}

bool is_xcase_exclusion_keycode(uint16_t keycode) {
    for (uint8_t i = 0; i < exclusion_keycode_count; i++) {
        if (exclusion_keycodes[i] == keycode) {
            return true;
        }
    }

    if (IS_QK_MOMENTARY(keycode) ||
        IS_QK_DEF_LAYER(keycode) ||
        IS_QK_TOGGLE_LAYER(keycode) ||
        IS_QK_ONE_SHOT_LAYER(keycode) ||
        IS_QK_TO(keycode) ||
        IS_QK_LAYER_MOD(keycode) ||
        IS_QK_ONE_SHOT_MOD(keycode)
    ) {
        return true;
    }

    switch (keycode) {
#ifdef TRI_LAYER_ENABLE
        case QK_TRI_LAYER_LOWER ... QK_TRI_LAYER_UPPER:
#endif
#ifdef LAYER_LOCK_ENABLE
        case QK_LAYER_LOCK:
#endif
        case KC_A ... KC_Z:
        case KC_P1 ... KC_P0:
        case KC_INTERNATIONAL_1 ... KC_LANGUAGE_9:
        case KC_UNDERSCORE:
        case KC_MINUS:
        case KC_KP_MINUS:
        case KC_BACKSPACE:
        case KC_DELETE:
        case KC_LEFT:
        case KC_RIGHT:
        case KC_UP:
        case KC_DOWN:
        case KC_LEFT_SHIFT:
        case KC_RIGHT_SHIFT:
        case KC_LEFT_CTRL:
        case KC_RIGHT_CTRL:
        case KC_LEFT_GUI:
        case KC_RIGHT_GUI:
        case KC_RIGHT_ALT:
        case KC_LEFT_ALT:
        case KC_CAPS:
            return true;
        case KC_1 ... KC_0:
            if ((get_mods()|get_oneshot_mods()|get_weak_mods()) & MOD_MASK_SHIFT) {
                return false;
            } else {
                return true;
            }
        default:
            return false;
    }
}

void add_xcase_exclusion_keycode(uint16_t keycode) {
    if (exclusion_keycode_count >= MAX_EXCLUSION_KEYCODES) {
        return;
    }
    if (is_xcase_exclusion_keycode(keycode)) {
        return;
    }
    exclusion_keycodes[exclusion_keycode_count++] = keycode;
}

void remove_xcase_exclusion_keycode(uint16_t keycode) {
    for (uint8_t i = 0; i < exclusion_keycode_count; i++) {
        if (exclusion_keycodes[i] == keycode) {
            for (uint8_t j = i; j < exclusion_keycode_count - 1; j++) {
                exclusion_keycodes[j] = exclusion_keycodes[j + 1];
            }
            exclusion_keycode_count--;
            return;
        }
    }
}

void enable_xcase_with(uint16_t delimiter) {
    uint16_t mods = delimiter & ~0xFF;

    bool is_visual_mod = (mods == QK_LSFT) ||
                         (mods == QK_LALT) ||
                         (mods == QK_RALT) ||
                         (mods == (QK_LSFT | QK_LALT));

    if (!IS_QK_BASIC(delimiter) && !is_visual_mod) {
        return;
    }

    switch (delimiter) {
        case KC_LSFT:
        case KC_RSFT:
        case OS_LSFT:
        case OS_RSFT:
            xcase_delimiter = KC_LSFT;
            break;

#ifdef TRI_LAYER_ENABLE
        case QK_TRI_LAYER_LOWER ... QK_TRI_LAYER_UPPER:
#endif
#ifdef LAYER_LOCK_ENABLE
        case QK_LAYER_LOCK:
#endif
        case KC_NO:
        case KC_F1 ... KC_F12:
        case KC_F13 ... KC_LPAD:
        case KC_BACKSPACE:
        case KC_DEL:
        case KC_HOME:
        case KC_END:
        case KC_PGUP:
        case KC_PGDN:
        case KC_PSCR:
        case KC_SCRL:
        case KC_PAUS:
        case KC_INS:
        case KC_NUM:
        case KC_ESC:
        case KC_LCTL:
        case KC_RCTL:
        case KC_LCMD:
        case KC_RCMD:
        case KC_SPACE:
            return;

        default:
            xcase_delimiter = delimiter;
            break;
        }

    last_keycode = KC_NO;
    xcase_active = true;
    add_xcase_exclusion_keycode(delimiter);
}

void disable_xcase(void) {
    xcase_active = false;
    last_keycode = KC_NO;
    remove_xcase_exclusion_keycode(xcase_delimiter);
}

bool process_record_xcase(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case XCASE_SNAKE:
                enable_xcase_with(KC_UNDS);
                return false;
            case XCASE_KEBAB:
                enable_xcase_with(KC_MINS);
                return false;
            case XCASE_CAMEL:
                enable_xcase_with(KC_LSFT);
                return false;
            case XCASE_OFF:
                disable_xcase();
                return false;
        }
    }

    if (!xcase_active) {
        return true;
    }

    if (record->event.pressed) {
        uint16_t base_keycode = keycode;
        if (IS_QK_MOD_TAP(keycode)) {
            base_keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
        } else if (IS_QK_LAYER_TAP(keycode)) {
            base_keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
        }

        if (base_keycode == KC_SPC) {
            if (last_keycode == KC_SPC) {
                if (xcase_delimiter != KC_LSFT &&
                    xcase_delimiter != KC_CAPS)
                {
                    tap_code(KC_BSPC);
                }
                disable_xcase();
                return true;
            }

            if (xcase_delimiter == KC_LSFT) {
                add_oneshot_mods(MOD_BIT(xcase_delimiter));
            } else {
                tap_code16(xcase_delimiter);
            }
            last_keycode = KC_SPC;
            return false;
        }

        if (!is_xcase_exclusion_keycode(base_keycode)) {
            disable_xcase();
        } else {
            last_keycode = base_keycode;
        }
        return true;
    }
    return true;
}
