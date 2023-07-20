/*
Copyright 2020 The Mad Noodle (Jesse Leventhal)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 4

/* NCC-1701-KB PCB default pin-out */
#define MATRIX_ROW_PINS { F7, F1, D6, D7 }
#define MATRIX_COL_PINS { F0, F5, F4, F6 }

/* RGB BackLight */
#define WS2812_DI_PIN B7
#define RGBLED_NUM 6
#define RGBLIGHT_SLEEP

/*RGB Defaults*/
#ifdef RGBLIGHT_MODE_RAINBOW_SWIRL
#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RAINBOW_SWIRL
#endif
#define RGBLIGHT_DEFAULT_SPD 3

/*Encoders */
#define ENCODERS_PAD_A { B6 }
#define ENCODERS_PAD_B { B5 }

#define OLED_DISPLAY_128X32
#define OLED_FONT_H "drivers/oled/glcdfont.c"

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL
