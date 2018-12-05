/* This file is a part of EAS Encoder.
 *
 * Copyright (C) 2018 Matthew Burket
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 */
#include <iostream>
#include "eas.h"
#include "Utils.h"
#include "audio.h"


void EAS::create_wat(const alert *alert, const std::vector<double> *sound_data) {
    if (alert->wat == NRW_WAT) {
        Audio::generate_tone(NRW_WAT_FREQ, (std::vector<double> &) *sound_data, SAMPLE_RATE * 8);
    } else {
        Audio::generate_dual_tone(WAT_FREQ_1, WAT_FREQ_2, (std::vector<double> &) *sound_data, SAMPLE_RATE * 5);
    }
}
