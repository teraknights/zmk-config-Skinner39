#include <zephyr/kernel.h>
#include <zmk/event_manager.h>
#include <zmk/hid.h>
#include <zmk/keymap.h>
#include <zmk/layers.h>
#include <zephyr/logging/log.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

// マウスレイヤーの定義（自由に変更可能）
#define MOUSE_LAYER 5

// トラックボールの動きを検知するリスナー
static int mouse_movement_listener(const struct zmk_hid_mouse_move_event *ev) {
    printk("Mouse movement detected! X: %d, Y: %d\n", ev->dx, ev->dy);
    LOG_INF("Mouse movement detected! X: %d, Y: %d", ev->dx, ev->dy);
    
    zmk_layer_activate(MOUSE_LAYER);
    
    // 3秒後に元のレイヤーに戻る
    k_timer_start(&layer_reset_timer, K_SECONDS(3), K_NO_WAIT);

    return 0;
}

// 3秒後にレイヤーをリセットする関数
void reset_layer(struct k_timer *timer_id) {
    LOG_INF("Resetting to default layer");
    zmk_layer_deactivate(MOUSE_LAYER);
}

// タイマーの宣言
K_TIMER_DEFINE(layer_reset_timer, reset_layer, NULL);

// HID イベントのリスナーを登録
ZMK_LISTENER(custom_mouse_listener, mouse_movement_listener);
ZMK_SUBSCRIPTION(custom_mouse_listener, zmk_hid_mouse_move_event);
