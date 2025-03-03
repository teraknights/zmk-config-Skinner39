#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zmk/event_manager.h>
#include <zmk/behavior.h>
#include <zmk/keymap.h>
#include <zmk/events/keycode_state_changed.h>
#include <dt-bindings/zmk/keys.h>  // HID キーコード定義

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

static int key_press_listener(const zmk_event_t *eh) {

        printk("Key Released!(printk)" );
        LOG_INF("Key Released!(log_inf)");
    return 0;
}

ZMK_LISTENER(key_press_logger, key_press_listener);
ZMK_SUBSCRIPTION(key_press_logger, zmk_keycode_state_changed);
