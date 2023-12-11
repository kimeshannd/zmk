/*
 * Copyright (c) 2021 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#include <errno.h>
#include <zephyr/drivers/sensor.h>

#include "battery_common.h"

int battery_channel_get(const struct battery_value *value, enum sensor_channel chan,
                        struct sensor_value *val_out) {
    switch (chan) {
    case SENSOR_CHAN_GAUGE_VOLTAGE:
        val_out->val1 = value->millivolts / 1000;
        val_out->val2 = (value->millivolts % 1000) * 1000U;
        break;

    case SENSOR_CHAN_GAUGE_STATE_OF_CHARGE:
        val_out->val1 = value->state_of_charge;
        val_out->val2 = 0;
        break;

    default:
        return -ENOTSUP;
    }

    return 0;
}

typedef struct {
    int16_t millivolts;
    float slope;
    float offset;
} batt_est_formula;

uint8_t lithium_ion_mv_to_pct(int16_t bat_mv) {
    // Lookup table of slope formulas for calculating remaining battery capacity.
    // The original values used to calculate slopes come from:
    //
    //       https://blog.ampow.com/lipo-voltage-chart/

    const batt_est_formula lipo_formula_lookup[9] = {
        {.millivolts = 4200, .slope = 0, .offset = 100},
        {.millivolts = 4150, .slope = 0.1, .offset = -320},
        {.millivolts = 4110, .slope = 0.125, .offset = -423.75},
        {.millivolts = 4020, .slope = 0.111, .offset = -366.22},
        {.millivolts = 3870, .slope = 0.133, .offset = -454.68},
        {.millivolts = 3690, .slope = 0.278, .offset = -1015.84},
        {.millivolts = 3610, .slope = 0.063, .offset = -222.47},
        {.millivolts = 3270, .slope = 0.015, .offset = -48.09},
    };

    for (int i = 0; i < 9; i++) {
        batt_est_formula current_formula = lipo_formula_lookup[i];
        if (bat_mv >= current_formula.millivolts) {
            float capacity = bat_mv * current_formula.slope + current_formula.offset;
            return (uint8_t)capacity;
        }
    }

    return 0;
}