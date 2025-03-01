#include <zephyr/kernel.h>
#include <zmk/event_manager.h>
#include <zmk/hid.h>
#include <zmk/keymap.h>
#include <zmk/layers.h>

// マウス移動時のイベントリスナー
static int mouse_movement_listener(const struct zmk_hid_mouse_move_event *ev) {
    // トラックボールが動いたらマウスレイヤーを有効化
    zmk_layer_activate(scroll_layer);
    
    // タイマーをリセットし、一定時間後にデフォルトレイヤーに戻る
    k_timer_start(&layer_reset_timer, K_SECONDS(3), K_NO_WAIT);

    return 0;
}

// HIDイベントを登録
ZMK_LISTENER(mouse_layer_listener, mouse_movement_listener);
ZMK_SUBSCRIPTION(mouse_layer_listener, zmk_hid_mouse_move_event);

// 3秒後にレイヤーをリセットするための関数
void reset_layer(struct k_timer *timer_id) {
    zmk_layer_deactivate(scroll_layer);
}

// タイマーの宣言
K_TIMER_DEFINE(layer_reset_timer, reset_layer, NULL);
