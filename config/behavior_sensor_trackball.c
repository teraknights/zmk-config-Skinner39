#include <zephyr/kernel.h>
#include <zmk/keymap.h>
#include <zmk/layer.h>
#include <zmk/event_manager.h>
#include <zmk/events/sensor_event.h>
#include "behavior_sensor_trackball.h"

#define SCROLL_LAYER 1
#define DEFAULT_LAYER 0
#define TIMEOUT_MS 2000

static struct k_timer layer_timer;

static int trackball_moved(const struct zmk_sensor_event *ev) {
    if (zmk_layer_active_get() != SCROLL_LAYER) {
        zmk_layer_activate(SCROLL_LAYER);
    }
    k_timer_start(&layer_timer, K_MSEC(TIMEOUT_MS), K_NO_WAIT);
    return 0;
}

void timer_expiry(struct k_timer *timer_id) {
    zmk_layer_deactivate(SCROLL_LAYER);
}

ZMK_LISTENER(trackball_listener, trackball_moved);
ZMK_SUBSCRIPTION(trackball_listener, zmk_sensor_event);

K_TIMER_DEFINE(layer_timer, timer_expiry, NULL);
