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
#include <math.h>
#include <sndfile.h>
#include <vector>

#include "Utils.h"
#include "eas.h"
#include "audio.h"

using namespace std;

int main() {
    auto *sound_data = new std::vector<double>;
    auto *bits = new std::vector<bool>();

    Utils::bit_string_to_bit_stream((vector<bool> &) *bits, PREAMBLE);
    Utils::string_to_bit_stream((vector<bool> &) *bits, HEADER);
    Utils::string_to_bit_stream((vector<bool> &) *bits, "-WXR");
    Utils::string_to_bit_stream((vector<bool> &) *bits, "-TOR");
    Utils::string_to_bit_stream((vector<bool> &) *bits, "-019169");
    Utils::string_to_bit_stream((vector<bool> &) *bits, "-019153");
    Utils::string_to_bit_stream((vector<bool> &) *bits, "+0045");
    Utils::string_to_bit_stream((vector<bool> &) *bits, "-2941320");
    Utils::string_to_bit_stream((vector<bool> &) *bits, "-KDSM/NWS-");

    Audio::generate_tone(0, (vector<double> &) *sound_data, SAMPLE_RATE);

    for (int i = 0; i < 3; i++) {
        Audio::generate_afsk((vector<double> &) *sound_data, (vector<bool> &) *bits);
        Audio::generate_tone(0, (vector<double> &) *sound_data, SAMPLE_RATE);
    }

    bits->clear();

    Audio::generate_tone(NRW_WAT_FREQ, (vector<double> &) *sound_data, SAMPLE_RATE * 8);
    //Audio::generate_dual_tone(WAT_FREQ_1, WAT_FREQ_2, (vector<double> &) *sound_data, SAMPLE_RATE * 5);
    Audio::generate_tone(0, (vector<double> &) *sound_data, SAMPLE_RATE);

    Utils::bit_string_to_bit_stream((vector<bool> &) *bits, PREAMBLE);
    Utils::string_to_bit_stream((vector<bool> &) *bits, EOM);

    for (int i = 0; i < 3; i++) {
        Audio::generate_afsk((vector<double> &) *sound_data, (vector<bool> &) *bits);
        Audio::generate_tone(0, (vector<double> &) *sound_data, SAMPLE_RATE);
    }


    struct SF_INFO info{};

    info.channels = 1;
    info.format = SF_FORMAT_WAV | SF_FORMAT_PCM_32;
    info.samplerate = SAMPLE_RATE;
    info.sections = 1;
    info.seekable = 1;

    const char *fileName = "eas_ean.wav";

    SNDFILE *sf = sf_open(fileName, SFM_WRITE, &info);
    fprintf(stderr, "%s\n", sf_error_number(sf_error(sf)));
    if (sf_write_double(sf, sound_data->data(), sound_data->size()) != sound_data->size()) {
        fprintf(stderr, "%s\n", sf_error_number(sf_error(sf)));
    }
    sf_write_sync(sf);
    sf_close(sf);

    delete bits;
    delete sound_data;
}

