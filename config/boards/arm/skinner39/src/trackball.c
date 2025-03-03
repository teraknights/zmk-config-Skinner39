#include <zephyr.h>
#include <device.h>
#include <drivers/sensor.h>
#include <logging/log.h>
#include <zmk/event_manager.h>
#include <zmk/events/layer_state_changed.h>

LOG_MODULE_REGISTER(trackball);

#define SCROLL_LAYER 1
#define DEFAULT_LAYER 0
#define TRACKBALL_NODE DT_ALIAS(trackball)

static const struct device *trackball_dev;
static struct k_work_delayable layer_reset_work;

static void reset_layer(struct k_work *work) {
    zmk_event_manager_raise(zmk_layer_state_changed_from_encoded(DEFAULT_LAYER));
}

static void trackball_handler(const struct device *dev, struct sensor_trigger *trigger) {
    struct sensor_value value;
    sensor_channel_get(dev, SENSOR_CHAN_POS_DX, &value);
    if (value.val1 != 0) {
        zmk_event_manager_raise(zmk_layer_state_changed_from_encoded(SCROLL_LAYER));
        k_work_reschedule(&layer_reset_work, K_SECONDS(2));
    }
}

void main(void) {
    trackball_dev = device_get_binding(DT_LABEL(TRACKBALL_NODE));
    if (!trackball_dev) {
        LOG_ERR("Trackball device not found");
        return;
    }

    struct sensor_trigger trig = {
        .type = SENSOR_TRIG_DATA_READY,
        .chan = SENSOR_CHAN_POS_DX,
    };

    sensor_trigger_set(trackball_dev, &trig, trackball_handler);
    k_work_init_delayable(&layer_reset_work, reset_layer);
}
