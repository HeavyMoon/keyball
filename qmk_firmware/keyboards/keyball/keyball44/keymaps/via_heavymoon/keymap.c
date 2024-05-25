/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

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

#include QMK_KEYBOARD_H

#include "quantum.h"

#ifdef LAYER_LED_ENABLE
#   include "layer_led.c"
#endif

enum my_keyball_keycodes {
    LAY_TOG = KEYBALL_SAFE_RANGE,   // FUNCTIONS > USER > User 0
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default (VIA)
  [0] = LAYOUT_universal(
    KC_ESC   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                        KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_BSPC  ,
    KC_LCTL  , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                        KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , KC_ENT   ,
    KC_LSFT  , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                                        KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , MO(1)    ,
                          KC_LGUI  , KC_LALT  , LT(KC_SPC,1), MO(3) , MO(2)   ,                   MO(4)    , MO(2)    ,            _______  , _______  , KC_PSCR
  ),

  [1] = LAYOUT_universal(
    KC_TAB   , KC_1     , KC_2     , KC_3     , KC_4     , KC_5     ,                                         KC_6     , KC_7    , KC_8     , KC_9     , KC_0     , KC_DEL   ,
    KC_F2    , KC_MINS  , KC_EQL   , KC_BSLS  , KC_GRV   , KC_LBRC  ,                                         KC_MINS  , KC_BTN1 , KC_BTN2  , KC_UP    , KC_BTN3  , _______  ,
    _______  , KC_F4    , KC_F5    , KC_F11   , KC_QUOT  , KC_RBRC  ,                                         KC_PGUP  , KC_PGDN , KC_LEFT  , KC_DOWN  , KC_RGHT  , _______  ,
                          _______  , _______  , KC_HOME  , KC_END   , _______  ,                   _______  , KC_LSFT  ,           _______  , _______  , _______
  ),

  [2] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  , _______  ,                                         KC_NUM  , KC_P7    , KC_P8    , KC_P9    , KC_PAST  , KC_PSLS  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                         KC_PDOT , KC_P4    , KC_P5    , KC_P6    , KC_PPLS  , KC_PENT  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                         KC_P0   , KC_P1    , KC_P2    , KC_P3    , KC_PMNS  , _______  ,
                          _______  , _______  , _______  , _______  , _______  ,                  _______  , _______  ,            _______  , _______  , _______
  ),

  [3] = LAYOUT_universal(
    RGB_TOG  , LAY_TOG  , _______  , _______  , AML_TO   , KBC_SAVE ,                                        RGB_M_P  , RGB_M_B  , RGB_M_R  , RGB_M_SW , RGB_M_SN , RGB_M_K  ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , AML_I50  , SCRL_DVI ,                                        RGB_M_X  , RGB_M_G  , RGB_M_T  , RGB_M_TW , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , AML_D50  , SCRL_DVD ,                                        CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , _______  , _______  ,
                          QK_BOOT  , _______  , _______  , _______  , _______  ,                  _______  , _______  ,            _______  , _______  , QK_BOOT
  ),

  [4] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  , _______  ,                                        _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                        _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                        _______  , _______  , _______  , _______  , _______  , _______  ,
                          _______  , _______  , _______  , _______  , _______  ,                  _______  , _______  ,            _______  , _______  , _______
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);

    #ifdef LAYER_LED_ENABLE
    change_layer_led_color(state);
    #endif

    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif

// 切り替え処理
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        #ifdef LAYER_LED_ENABLE
        case LAY_TOG:
            toggle_layer_led(record->event.pressed);
            return true;
        #endif
        default:
            break;
    }
    return true;
}

