/* Copyright 2019 Danny Nguyen <danny@keeb.io>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#ifndef RGB_MATRIX_ENABLE
#    error RGB_MATRIX_ENABLE is required
#endif

#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif

enum Layers {
    LAYER_DEFAULT,
    LAYER_SETTINGS,
};

enum EncoderNames {
    ENCODER_LEFT,
    ENCODER_RIGHT,
    ENCODER_MIDDLE,
};

enum Macros {
    MACRO_UNNAMED = SAFE_RANGE,
};

enum Aliases {
    /* Windows shortcut */
    kMonitorPrev = LCTL(LWIN(KC_LEFT)),
    kMonitorNext = LCTL(LWIN(KC_RIGHT)),
    kTaskmgr     = LCTL(LSFT(KC_ESC)),
    /* shortcut in Microsoft PowerToys */
    kMuteCamera = LCTL(KC_F19),
    kMuteMic    = LCTL(KC_F20),
    /* Araxis Merge shortcut */
    kResolve = LCTL(KC_K)
};

/* clang-format off */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_DEFAULT] = LAYOUT(
        kTaskmgr,           KC_F13,         RGB_TOG,
        MO(LAYER_SETTINGS), kMuteCamera,    kMuteMic,
        kMonitorPrev,       kResolve,       kMonitorNext
    ),
    [LAYER_SETTINGS] = LAYOUT(
        QK_BOOT, KC_F16, _______,
        _______, KC_F17, _______,
        KC_MPRV, KC_F18, KC_MNXT
    ),
};
/* clang-format on */

bool encoder_update_user(uint8_t index, bool clockwise) {
    int const layer = get_highest_layer(layer_state);

    printf("index=%d, clockwise=%d\n", index, clockwise);

    switch (index) {
        /* Knob 1: Volume dn/up */
        case ENCODER_LEFT:
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
            break;

        /* Knob 2: RGB hue cycle */
        case ENCODER_MIDDLE:
            if (layer == LAYER_SETTINGS) {
                if (clockwise) {
                    rgb_matrix_increase_sat();
                } else {
                    rgb_matrix_decrease_sat();
                }
            } else {
                if (clockwise) {
                    rgb_matrix_increase_hue();
                } else {
                    rgb_matrix_decrease_hue();
                }
            }
            break;

        /* Knob 3: RGB brightness +/- */
        case ENCODER_RIGHT:
            if (clockwise) {
                rgb_matrix_increase_val();
            } else {
                rgb_matrix_decrease_val();
            }
            break;
    }

    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MACRO_UNNAMED:
            return false;
    }

    return true;
}

static HSV const LayerColors[2] = {
    {HSV_BLUE},
    {HSV_RED},
};

bool rgb_matrix_indicators_user(void) {
    HSV color;

    switch (get_highest_layer(layer_state)) {
        case LAYER_SETTINGS:
            color = LayerColors[LAYER_SETTINGS];
            break;
        default:
            color = LayerColors[LAYER_DEFAULT];
            break;
    }

    // match brightness of keyboard
    color.v = rgb_matrix_get_val();

    if (color.v < 200) {
        color.v = 200;
    }

    RGB rgb = hsv_to_rgb(color);
    rgb_matrix_set_color(9, rgb.r, rgb.g, rgb.b);
    rgb_matrix_set_color(10, rgb.r, rgb.g, rgb.b);

    // turn off encoder leds
    rgb_matrix_set_color(0, RGB_OFF);
    rgb_matrix_set_color(1, RGB_OFF);
    rgb_matrix_set_color(2, RGB_OFF);

    return false;
}

void keyboard_post_init_user(void) {
    rgb_matrix_enable_noeeprom();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
}

#ifdef VIRTSER_ENABLE
void virtser_recv(uint8_t c) {
    printf("virtser_recv(%c)\n", c);
}
#else
#    error VIRTSER_ENABLE not enabled
#endif
