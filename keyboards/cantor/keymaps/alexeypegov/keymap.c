#include QMK_KEYBOARD_H

void keyboard_post_init_user(void) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_enable();
    rgb_matrix_set_speed(RGB_MATRIX_DEFAULT_SPD);
    //rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE);
    rgb_matrix_sethsv(HSV_PURPLE);
#endif
}

enum custom_keycodes {
    DEFAULT = SAFE_RANGE,
    LOWER,
    RAISE,
    FUNC,
    MOUSE,
};

enum combos {
  THREE_FOUR_DASH,
  DF_DASH,
  JK_ESC
};

const uint16_t PROGMEM three_four_combo[] = {KC_3, KC_4, COMBO_END};
const uint16_t PROGMEM df_combo[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};


combo_t key_combos[COMBO_COUNT] = {
  // Add commonly used dash to home row
  [DF_DASH]    = COMBO(df_combo, KC_MINS),
  [THREE_FOUR_DASH]    = COMBO(three_four_combo, KC_MINS),
  // For Vim, put Escape on the home row
  [JK_ESC]    = COMBO(jk_combo, KC_ESC),

};

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER  1
#define _RAISE  2
#define _FUNC   3
#define _MOUSE  4
#define _SHORTCUT  5
#define _RU 6

enum unicode_names {
    RU_JE, RU_JE_UP,
    RU_TSE, RU_TSE_UP,
    RU_U, RU_U_UP,
    RU_KA, RU_KA_UP,
    RU_IE, RU_IE_UP,
    RU_EN, RU_EN_UP,
    RU_GHE, RU_GHE_UP,
    RU_SHA, RU_SHA_UP,
    RU_SHCHA, RU_SHCHA_UP,
    RU_ZE, RU_ZE_UP,
    RU_HA, RU_HA_UP,
    RU_HARD, RU_HARD_UP,
    RU_EF, RU_EF_UP,
    RU_YERU, RU_YERU_UP,
    RU_VE, RU_VE_UP,
    RU_A, RU_A_UP,
    RU_PE, RU_PE_UP,
    RU_ER, RU_ER_UP,
    RU_O, RU_O_UP,
    RU_EL, RU_EL_UP,
    RU_DE, RU_DE_UP,
    RU_ZHE, RU_ZHE_UP,
    RU_E, RU_E_UP,
    RU_YA, RU_YA_UP,
    RU_CHE, RU_CHE_UP,
    RU_ES, RU_ES_UP,
    RU_EM, RU_EM_UP,
    RU_I, RU_I_UP,
    RU_TE, RU_TE_UP,
    RU_SOFT, RU_SOFT_UP,
    RU_BE, RU_BE_UP,
    RU_YU, RU_YU_UP,
    RU_COMM, RU_DOT,
    RU_QUOT, RU_DQUO,
};

const uint32_t PROGMEM unicode_map[] = {
    [RU_JE] = 0x0439, [RU_JE_UP] = 0x0419,
    [RU_TSE] = 0x0446, [RU_TSE_UP] = 0x0426,
    [RU_U] = 0x0443, [RU_U_UP] = 0x0423,
    [RU_KA] = 0x043A, [RU_KA_UP] = 0x041A,
    [RU_IE] = 0x0435, [RU_IE_UP] = 0x0415,
    [RU_EN] = 0x043D, [RU_EN_UP] = 0x041D,
    [RU_GHE] = 0x0433, [RU_GHE_UP] = 0x0413,
    [RU_SHA] = 0x0448, [RU_SHA_UP] = 0x0428,
    [RU_SHCHA] = 0x0449, [RU_SHCHA_UP] = 0x0429,
    [RU_ZE] = 0x0437, [RU_ZE_UP] = 0x0417,
    [RU_HA] = 0x0445, [RU_HA_UP] = 0x0425,
    [RU_HARD] = 0x044A, [RU_HARD_UP] = 0x042A,
    [RU_EF] = 0x0444, [RU_EF_UP] = 0x0424,
    [RU_YERU] = 0x044B, [RU_YERU_UP] = 0x042B,
    [RU_VE] = 0x0432, [RU_VE_UP] = 0x0412,
    [RU_A] = 0x0430, [RU_A_UP] = 0x0410,
    [RU_PE] = 0x043F, [RU_PE_UP] = 0x041F,
    [RU_ER] = 0x0440, [RU_ER_UP] = 0x0420,
    [RU_O] = 0x043E, [RU_O_UP] = 0x041E,
    [RU_EL] = 0x043B, [RU_EL_UP] = 0x041B,
    [RU_DE] = 0x0434, [RU_DE_UP] = 0x0414,
    [RU_ZHE] = 0x0436, [RU_ZHE_UP] = 0x0416,
    [RU_E] = 0x044D, [RU_E_UP] = 0x042D,
    [RU_YA] = 0x044F, [RU_YA_UP] = 0x042F,
    [RU_CHE] = 0x0447, [RU_CHE_UP] = 0x0427,
    [RU_ES] = 0x0441, [RU_ES_UP] = 0x0421,
    [RU_EM] = 0x043C, [RU_EM_UP] = 0x041C,
    [RU_I] = 0x0438, [RU_I_UP] = 0x0418,
    [RU_TE] = 0x0442, [RU_TE_UP] = 0x0422,
    [RU_SOFT] = 0x044C, [RU_SOFT_UP] = 0x042C,
    [RU_BE] = 0x0431, [RU_BE_UP] = 0x0411,
    [RU_YU] = 0x044E, [RU_YU_UP] = 0x042E,
    [RU_COMM] = 0x002C, [RU_DOT] = 0x002E,
    [RU_QUOT] = 0x0027, [RU_DQUO] = 0x0022,
};

// For _QWERTY layer
#define GUI_ENT  GUI_T(KC_ENT)
#define LOW_TAB  LT(_LOWER, KC_TAB)
#define MOU_GUI  LT(_MOUSE, KC_LGUI)
#define OSL_FUN  OSL(_FUNC)
#define OSM_AGR  OSM(MOD_RALT)
#define OSM_ALT  OSM(MOD_LALT)
#define OSM_CTL  OSM(MOD_LCTL)
#define OSM_SFT  OSM(MOD_LSFT)
#define RSE_BSP  LT(_RAISE, KC_BSPC)

// For _RAISE layer
#define CTL_ESC  LCTL_T(KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_DEL  ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
 OSM(MOD_LALT),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                     KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_QUOT ,OSM_AGR ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
 OSM(MOD_LSFT),   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                     KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,OSL_FUN ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         OSM_CTL, GUI_ENT, LOW_TAB,    RSE_BSP ,KC_SPC  ,OSM_SFT
                                      //`--------------------------'  `--------------------------'
  ),

[_LOWER] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_EXLM, KC_AT,  KC_HASH, KC_DLR,  KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______ ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_1,    KC_2,   KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______ ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX , KC_TILD,KC_GRV, KC_LBRC, KC_LCBR,                       KC_RCBR, KC_RBRC, KC_COMM,KC_DOT,  KC_SLSH, _______ ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS,  KC_TRNS, LOWER,    KC_TRNS, KC_TRNS, KC_COLON
                                      //`--------------------------'  `--------------------------'
  ),

[_RAISE] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_DEL , KC_INS, KC_UNDS, KC_PLUS, KC_PGUP,                      KC_BRID, KC_BRIU, KC_F13 , KC_BSLS, KC_PIPE,_______ ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_HOME, KC_END , KC_MINS, KC_EQL , KC_PGDN,                      KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_APP ,_______ ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_LT  , KC_GT  , KC_COPY, KC_PSTE, KC_SCLN,                      KC_MPLY, KC_MPRV, KC_MNXT, KC_VOLD, KC_VOLU,_______ ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          CTL_ESC, KC_TRNS, XXXXXXX,    RAISE  , KC_TRNS, KC_TRNS\
                                      //`--------------------------'  `--------------------------'
  ),

[_FUNC] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_F1  , KC_F2  , KC_F3   , KC_F4 ,  KC_F5 ,                     KC_F6   , KC_F7  , KC_F8  , KC_F9  , KC_F10 ,_______ ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_F11 , KC_F12 , XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,_______ ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,KC_CAPS,S(KC_DEL),C(KC_INS),S(KC_INS),XXXXXXX,                      RM_TOGG, XXXXXXX, XXXXXXX, XXXXXXX, C(G(KC_Q)),XXXXXXX ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, FUNC   , XXXXXXX
                                      //`--------------------------'  `--------------------------'
                                      //`--------------------------'  `--------------------------'
  ),

// There's no keybinding to activate the mouse layer yet!
[_MOUSE] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, MS_LEFT, MS_UP, MS_DOWN, MS_RGHT, _______,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, MS_BTN1, MS_BTN2, XXXXXXX, XXXXXXX, _______,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX,XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_APP,  XXXXXXX, XXXXXXX, XXXXXXX, _______,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS\
                                      //`--------------------------'  `--------------------------'
  ),

[_RU] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
 UP(RU_JE, RU_JE_UP), UP(RU_TSE, RU_TSE_UP), UP(RU_U, RU_U_UP), UP(RU_KA, RU_KA_UP), UP(RU_IE, RU_IE_UP), UP(RU_EN, RU_EN_UP), UP(RU_GHE, RU_GHE_UP), UP(RU_SHA, RU_SHA_UP), UP(RU_SHCHA, RU_SHCHA_UP), UP(RU_ZE, RU_ZE_UP), UP(RU_HA, RU_HA_UP), UP(RU_HARD, RU_HARD_UP),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      OSM_ALT, UP(RU_EF, RU_EF_UP), UP(RU_YERU, RU_YERU_UP), UP(RU_VE, RU_VE_UP), UP(RU_A, RU_A_UP), UP(RU_PE, RU_PE_UP), UP(RU_ER, RU_ER_UP), UP(RU_O, RU_O_UP), UP(RU_EL, RU_EL_UP), UP(RU_DE, RU_DE_UP), UP(RU_ZHE, RU_ZHE_UP), UP(RU_E, RU_E_UP),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      OSM_SFT, UP(RU_YA, RU_YA_UP), UP(RU_CHE, RU_CHE_UP), UP(RU_ES, RU_ES_UP), UP(RU_EM, RU_EM_UP), UP(RU_I, RU_I_UP), UP(RU_TE, RU_TE_UP), UP(RU_SOFT, RU_SOFT_UP), UP(RU_BE, RU_BE_UP), UP(RU_YU, RU_YU_UP), UP(RU_COMM, RU_DOT), UP(RU_QUOT, RU_DQUO),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          OSM_CTL, GUI_ENT, LOW_TAB,    RSE_BSP, KC_SPC, OSM_SFT
                                      //`--------------------------'  `--------------------------'
  ),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed && keycode == KC_SPC && (get_mods() & MOD_MASK_GUI)) {
        layer_invert(_RU);
        return false;
    }

    return true;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
      case LT(_RAISE, KC_BSPC):
            return TAPPING_TERM_THUMB;
      case LT(_LOWER, KC_TAB):
            return TAPPING_TERM_THUMB;
      case LT(_MOUSE, KC_LGUI):
            return TAPPING_TERM_THUMB;
      case LT(_SHORTCUT, OSM_SFT):
            return TAPPING_TERM_THUMB;
      default:
            return TAPPING_TERM;
    }
}

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
