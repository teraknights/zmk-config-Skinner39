#pragma once

void timer_expiry(struct k_timer *timer_id);
int trackball_moved(const struct zmk_sensor_event *ev);
