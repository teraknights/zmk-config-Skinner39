#include <zephyr/kernel.h>
#include <zmk/event_manager.h>
#include <zmk/hid.h>
#include <zmk/keymap.h>
#include <zmk/layers.h>

// トラックボールの動作を検知する関数
static int mouse_movement_listener(const struct zmk_hid_mouse_move_event *ev) {
    zmk_layer_activate(MOUSE_LAYER);
    
    // 3秒後にデフォルトレイヤーへ戻るタイマーをセット
    k_timer_start(&layer_reset_timer, K_SECONDS(3), K_NO_WAIT);

    return 0;
}

// タイマーが切れたらデフォルトレイヤーに戻る
void reset_layer(struct k_timer *timer_id) {
    zmk_layer_deactivate(MOUSE_LAYER);
}

// タイマーの宣言
K_TIMER_DEFINE(layer_reset_timer, reset_layer, NULL);

// HIDイベントを登録
ZMK_LISTENER(mouse_layer_listener, mouse_movement_listener);
ZMK_SUBSCRIPTION(mouse_layer_listener, zmk_hid_mouse_move_event);
