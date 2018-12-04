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


void EAS::create_header(const alert *alert, std::string &header) {
    header.append(HEADER);
    header.push_back('-');
    header.append(alert->origin);
    header.push_back('-');
    header.append(alert->event);
    for (auto locationsIter = alert->areas.begin(); locationsIter < alert->areas.end(); locationsIter++) {
        header.push_back('-');
        header.append(*locationsIter);

    }
    header.push_back('-');
    header.append(alert->length);
    header.push_back('-');
    header.append(Utils::zero_pad_int(alert->date,3));
    header.append(Utils::zero_pad_int(alert->hour, 2));
    header.append(Utils::zero_pad_int(alert->minute, 2));
    header.push_back('-');
    header.append(alert->participant);
    header.push_back('-');
   std::cout << header;
}

void EAS::create_wat(const alert *alert, const std::vector<double> *sound_data) {
    if (alert->wat == NRW_WAT) {
        Audio::generate_tone(NRW_WAT_FREQ, (std::vector<double> &) *sound_data, SAMPLE_RATE * 8);
    } else {
        Audio::generate_dual_tone(WAT_FREQ_1, WAT_FREQ_2, (std::vector<double> &) *sound_data, SAMPLE_RATE * 5);
    }
}
