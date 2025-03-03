#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zmk/event_manager.h>
#include <zmk/behavior.h>
#include <zmk/keymap.h>
#include <zmk/events/keycode_state_changed.h>
#include <dt-bindings/zmk/keys.h>  // HID キーコード定義

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

static int key_press_listener(const zmk_event_t *eh) {
    const struct zmk_keycode_state_changed *ev = as_zmk_keycode_state_changed(eh);
    if (!ev) {
        return -ENOTSUP;  // イベントの型が違う場合は無視
    }

    if (ev->state) {  // 1 = キーが押されたとき
        printk("Key Pressed! Keycode: 0x%02X\n", ev->keycode);
        LOG_INF("Key Pressed! Keycode: 0x%02X", ev->keycode);
    } else {  // 0 = キーを離したとき
        printk("Key Released! Keycode: 0x%02X\n", ev->keycode);
        LOG_INF("Key Released! Keycode: 0x%02X", ev->keycode);
    }
    return 0;
}

ZMK_LISTENER(key_press_logger, key_press_listener);
ZMK_SUBSCRIPTION(key_press_logger, zmk_keycode_state_changed);
