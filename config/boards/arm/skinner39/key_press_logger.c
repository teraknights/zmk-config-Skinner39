#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zmk/event_manager.h>
#include <zmk/behavior.h>
#include <zmk/keymap.h>
#include <zmk/events/keycode_state_changed.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

static int key_press_listener(const struct zmk_keycode_state_changed *ev) {
    if (ev->keycode == HID_USAGE_KEY_A) {  // `Q` キーをチェック
        if (ev->state) {  // キーが押されたとき（0 = 離したとき, 1 = 押したとき）
            printk("Q Key Pressed!\n");
            LOG_INF("Q Key Pressed!");
        } else {
            printk("Q Key Released!\n");
            LOG_INF("Q Key Released!");
        }
    }
    return 0;
}

ZMK_LISTENER(key_press_logger, key_press_listener);
ZMK_SUBSCRIPTION(key_press_logger, zmk_keycode_state_changed);
