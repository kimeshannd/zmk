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

#if IS_ENABLED(CONFIG_SETTINGS)
#include <settings/settings.h>
#endif

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#if DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT)

struct base_layer_state {
    uint8_t base_layer_by_profile[ZMK_PROFILE_COUNT];
};

static struct base_layer_state state = {.base_layer_by_profile = {0}};

#if IS_ENABLED(CONFIG_SETTINGS)
static int base_layer_settings_set(const char *name, size_t len, settings_read_cb read_cb,
                                   void *cb_arg) {
    const char *next;
    if (settings_name_steq(name, "state", &next) && !next) {
        if (len != sizeof(state)) {
            return -EINVAL;
        }
        int rc = read_cb(cb_arg, &state, sizeof(state));
        return MIN(rc, 0);
    }
    return -ENOENT;
}

static void base_layer_save_work_handler(struct k_work *work) {
    settings_save_one("base_layer/state", &state, sizeof(state));
}

static struct k_work_delayable base_layer_save_work;
struct settings_handler base_layer_settings_handler = {.name = "base_layer",
                                                       .h_set = base_layer_settings_set};
#endif

static int behavior_base_layer_init(const struct device *dev) {
#if IS_ENABLED(CONFIG_SETTINGS)
    settings_subsys_init();

    int err = settings_register(&base_layer_settings_handler);
    if (err) {
        LOG_ERR("Failed to register the base_layer settings handler (err %d)", err);
        return err;
    }

    k_work_init_delayable(&base_layer_save_work, base_layer_save_work_handler);

    settings_load_subtree("base_layer");
#endif

    return 0;
};

static int on_keymap_binding_pressed(struct zmk_behavior_binding *binding,
                                     struct zmk_behavior_binding_event event) {
    LOG_DBG("position %d layer %d", event.position, binding->param1);

    const zmk_profile_index_t profile_index = zmk_current_profile_index();
    const uint8_t layer = binding->param1;

    state.base_layer_by_profile[profile_index] = layer;
    zmk_keymap_layer_to(layer);
    LOG_INF("saved base layer %d for profile %d", layer, profile_index);

#if IS_ENABLED(CONFIG_SETTINGS)
    k_work_reschedule(&base_layer_save_work, K_MSEC(CONFIG_ZMK_SETTINGS_SAVE_DEBOUNCE));
#endif /* IS_ENABLED(CONFIG_SETTINGS) */

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
    const uint8_t layer = state.base_layer_by_profile[profile_index];

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

DEVICE_DT_INST_DEFINE(0, behavior_base_layer_init, NULL, NULL, NULL, APPLICATION,
                      CONFIG_KERNEL_INIT_PRIORITY_DEFAULT, &behavior_base_layer_driver_api);

#endif /* DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT) */
