// Layer LED Indicator by matucon
// Ref. https://mazcon.hatenablog.com/entry/2023/11/10/080000#LED%E3%82%A8%E3%83%95%E3%82%A7%E3%82%AF%E3%83%88%E7%84%A1%E5%8A%B9%E5%8C%96

#ifdef LAYER_LED_ENABLE

#include QMK_KEYBOARD_H

static const uint8_t my_layer_colors[] = {135, 85, 0, 213}; // 縹，緑，赤，紫

static uint8_t my_latest_val = 0;
static uint8_t my_latest_hue = 0;
static bool    layer_led     = true;

// レイヤーごとにLED色変更
void change_layer_led_color(layer_state_t state) {
    if (!layer_led) {
        return;
    }

    uint8_t layer_no = get_highest_layer(state);
    if (layer_no == 0) {
        my_latest_val = rgblight_get_val();
        rgblight_sethsv(rgblight_get_hue(), rgblight_get_sat(), 0);
    } else {
            rgblight_sethsv(my_layer_colors[layer_no -1], rgblight_get_sat(), my_latest_val);
    }
}

// 機能の有効・無効を切り替え
void toggle_layer_led(bool pressed) {
    if (!pressed) {
        return;
    }

    layer_led = !layer_led;
    if (layer_led) {
        my_latest_hue = rgblight_get_hue();
    } else {
        rgblight_sethsv(my_latest_hue, rgblight_get_sat(), rgblight_get_val());
    }
}

#endif
