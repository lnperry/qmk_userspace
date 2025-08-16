#include QMK_KEYBOARD_H

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

// --- Layer Names ---
enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_NAV,
    LAYER_SYS,
    LAYER_POINTER,
};

// --- Custom Keycodes for Macros ---
enum custom_keycodes {
    // Macros
    SPOTLIGHT = SAFE_RANGE,
    SCREENSHOT,
    WIN_LEFT,
    WIN_RIGHT,
    WIN_MAX,
};

// --- Layer Aliases ---
#define NAV MO(LAYER_NAV)
#define SYS MO(LAYER_SYS)
#define PT_Z LT(LAYER_POINTER, KC_Z)
#define PT_SLSH LT(LAYER_POINTER, KC_SLSH)

// --- Home Row Mod Definitions ---
#define A_CMD    LGUI_T(KC_A)
#define S_OPT    LALT_T(KC_S)
#define D_CTL    LCTL_T(KC_D)
#define F_SFT    LSFT_T(KC_F)
#define J_SFT    RSFT_T(KC_J)
#define K_CTL    RCTL_T(KC_K)
#define L_OPT    RALT_T(KC_L)
#define SCLN_CMD RGUI_T(KC_SCLN)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_BASE] = LAYOUT(
        // Left Hand (24 keys)
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
        LSFT_T(KC_ESC), A_CMD, S_OPT, D_CTL, F_SFT, KC_G,
        KC_LCTL, PT_Z,    KC_X,    KC_C,    KC_V,    KC_B,

        // Right Hand (24 keys)
        KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,
        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSLS,
        KC_H,    J_SFT,   K_CTL,   L_OPT, SCLN_CMD, KC_QUOT,
        KC_N,    KC_M, KC_COMM,  KC_DOT, PT_SLSH, KC_RALT,

        // All 8 Thumb Keys MUST be at the end
        KC_SPC, KC_LGUI, SYS,   NAV,   KC_ENT,
        KC_LALT, KC_DEL,  KC_BSPC
    ),

    [LAYER_NAV] = LAYOUT(
        // Left Hand
        _______, _______, _______, _______, _______, _______,
        _______, KC_BRID, KC_VOLU, KC_BRIU, _______, _______,
        _______, KC_MPRV, KC_VOLD, KC_MNXT, _______, _______,
        _______, _______, KC_MPLY, _______, _______, _______,

        // Right Hand
        _______, _______, _______, _______, _______, _______,
        KC_PGUP,   KC_HOME,   KC_UP,   KC_END, XXXXXXX, XXXXXXX,
        KC_PGDN,   KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX,
        _______, _______, _______, _______, _______, _______,

        // Thumbs (at the end)
        _______, _______, _______, _______, _______,
        _______, _______, _______
    ),

    [LAYER_SYS] = LAYOUT(
        // Left Hand
        QK_BOOT,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, SPOTLIGHT, WIN_LEFT, WIN_MAX, WIN_RIGHT, XXXXXXX,
        _______, SCREENSHOT, XXXXXXX, _______, _______, _______,

        // Right Hand
          KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_F12,
        XXXXXXX, XXXXXXX, KC_MCTL, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,

        // Thumbs (at the end)
        _______, _______, _______, _______, _______,
        _______, _______, _______
    ),

    [LAYER_POINTER] = LAYOUT(
        // Left Hand
        KC_BTN1,  KC_BTN2,  KC_BTN3, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, DPI_MOD, S_D_MOD,
        XXXXXXX,  KC_LGUI,  KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,
        XXXXXXX,  _______,  DRGSCRL, SNIPING, XXXXXXX, XXXXXXX,

        // Right Hand
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,  EE_CLR,
        S_D_MOD, DPI_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, XXXXXXX,
        XXXXXXX, XXXXXXX, SNIPING, DRGSCRL, _______, XXXXXXX,

        // Thumbs (at the end)
        KC_BTN1,  KC_BTN2,  KC_BTN3, KC_BTN3,  KC_BTN2,
        XXXXXXX,  KC_BTN2,  KC_BTN1
    ),
};

// --- Macro Handling ---
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case SPOTLIGHT:
                SEND_STRING(SS_LGUI(" ")); // Command + Space
                return false;
            case SCREENSHOT:
                SEND_STRING(SS_LGUI(SS_LSFT("5"))); // Command + Shift + 5
                return false;
            case WIN_LEFT:
                // Correctly sends Command + Option + Left Arrow
                register_code(KC_LGUI);
                register_code(KC_LALT);
                tap_code(KC_LEFT);
                unregister_code(KC_LALT);
                unregister_code(KC_LGUI);
                return false;
            case WIN_RIGHT:
                // Correctly sends Command + Option + Right Arrow
                register_code(KC_LGUI);
                register_code(KC_LALT);
                tap_code(KC_RGHT);
                unregister_code(KC_LALT);
                unregister_code(KC_LGUI);
                return false;
            case WIN_MAX:
                // Correctly sends Command + Option + Enter
                register_code(KC_LGUI);
                register_code(KC_LALT);
                tap_code(KC_ENT);
                unregister_code(KC_LALT);
                unregister_code(KC_LGUI);
                return false;
        }
    }
    return true;
}

// --- RGB Layer Colors ---
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case LAYER_BASE:
            rgb_matrix_sethsv_noeeprom(HSV_WHITE);
            break;
        case LAYER_NAV:
            rgb_matrix_sethsv_noeeprom(HSV_BLUE);
            break;
        case LAYER_SYS:
            rgb_matrix_sethsv_noeeprom(HSV_MAGENTA);
            break;
        case LAYER_POINTER:
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
            break;
        default:
            break;
    }
    return state;
}

void keyboard_post_init_user(void) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(HSV_WHITE);
}
