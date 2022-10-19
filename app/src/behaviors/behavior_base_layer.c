/*
 * Copyright (c) 2022 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#define DT_DRV_COMPAT zmk_behavior_base_layer

#include <device.h>
#include <drivers/behavior.h>
#include <logging/log.h>

#include <zmk/keymap.h>
#include <zmk/behavior.h>
#include <zmk/events/endpoint_selection_changed.h>
#include <zmk/events/ble_active_profile_changed.h>
#include <zmk/profiles.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#if DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT)

uint8_t base_layer_by_profile[ZMK_PROFILE_COUNT] = {0};

static int behavior_to_init(const struct device *dev) { return 0; };

static int on_keymap_binding_pressed(struct zmk_behavior_binding *binding,
                                     struct zmk_behavior_binding_event event) {
    LOG_DBG("position %d layer %d", event.position, binding->param1);

    const zmk_profile_index_t profile_index = zmk_current_profile_index();
    const uint8_t layer = binding->param1;

    base_layer_by_profile[profile_index] = layer;
    zmk_keymap_layer_to(layer);
    LOG_INF("saved base layer %d for profile %d", layer, profile_index);

    return ZMK_BEHAVIOR_OPAQUE;
}

static int on_keymap_binding_released(struct zmk_behavior_binding *binding,
                                      struct zmk_behavior_binding_event event) {
    LOG_DBG("position %d layer %d", event.position, binding->param1);
    return ZMK_BEHAVIOR_OPAQUE;
}

static int base_layer_listener(const zmk_event_t *e) {
    if (e == NULL) {
        return ZMK_EV_EVENT_BUBBLE;
    }

    const zmk_profile_index_t profile_index = zmk_current_profile_index();
    const uint8_t layer = base_layer_by_profile[profile_index];

    zmk_keymap_layer_to(layer);
    LOG_INF("restored base layer %d for profile %d", layer, profile_index);

    return ZMK_EV_EVENT_BUBBLE;
}
static ZMK_LISTENER(base_layer_listener, base_layer_listener);

static ZMK_SUBSCRIPTION(base_layer_listener, zmk_endpoint_selection_changed);

#if IS_ENABLED(CONFIG_ZMK_BLE)
static ZMK_SUBSCRIPTION(base_layer_listener, zmk_ble_active_profile_changed);
#endif

static const struct behavior_driver_api behavior_base_layer_driver_api = {
    .binding_pressed = on_keymap_binding_pressed,
    .binding_released = on_keymap_binding_released,
};

DEVICE_DT_INST_DEFINE(0, behavior_to_init, NULL, NULL, NULL, APPLICATION,
                      CONFIG_KERNEL_INIT_PRIORITY_DEFAULT, &behavior_base_layer_driver_api);

#endif /* DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT) */
