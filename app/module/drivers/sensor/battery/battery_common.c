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

uint8_t lithium_ion_mv_to_pct(int16_t batt_mv) {
    // Lookup table of slope formulas for calculating remaining battery capacity.
    // The original values used to calculate slopes come from:
    //
    //       https://blog.ampow.com/lipo-voltage-chart/
    //
    struct lookup_point {
        float millivolts;
        float percent;
    };

    static const struct lookup_point battery_lookup[] = {
        {.millivolts = 4200, .percent = 100}, {.millivolts = 3870, .percent = 60},
        {.millivolts = 3690, .percent = 10},  {.millivolts = 3610, .percent = 5},
        {.millivolts = 3270, .percent = 0},
    };

    if (batt_mv > 4200) {
        return 100;
    }

    for (int i = 1; i < ARRAY_SIZE(battery_lookup); i++) {
        struct lookup_point one = battery_lookup[i - 1];
        struct lookup_point two = battery_lookup[i];
        if (batt_mv >= two.millivolts) {
            float slope = (one.percent - two.percent) / (one.millivolts - two.millivolts);
            float offset = one.percent - slope * one.millivolts;
            float batt_percent = (slope * batt_mv) + offset;
            return (uint8_t)batt_percent;
        }
    }

    return 0;
}
