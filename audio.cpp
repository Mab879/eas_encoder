/* This file is a part of EAS Encoder.
 *
 * Copyright (C) 2018 Matthew Burket
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 */

#include <math.h>
#include <string>
#include <sndfile.h>
#include <iostream>

#include "eas.h"
#include "audio.h"

using namespace std;

/// Add the wave data to the given double vector
/// \param freq frequency of the tone in hertz
/// \param vector vector to add samples to
/// \param length length in number of samples
void Audio::generate_tone(double freq, std::vector<double> &vector, long length) {
    for (int i = 0; i < length; i++) {
        vector.push_back(sin((i * 2 * M_PI  * freq) / SAMPLE_RATE));
    }
}

/// Create a dual tone
/// \param freq1 the first frequency
/// \param freq2 the second frequency
/// \param vector the vector to copy the sound bytes to
/// \param length how long to play the dual tone
void Audio::generate_dual_tone(double freq1, double freq2, std::vector<double> &vector, long length) {
    for (int i = 0; i < length; i++) {
        double value = 0.5 * sin((i * 2 * M_PI  * freq1) / SAMPLE_RATE) + 0.5 * sin((i * 2 * M_PI  * freq2) / SAMPLE_RATE);
        vector.push_back(value);
    }
}

/// From a bitsteam, add the PCM wave bits to to the given vector
/// \param vector the vector to add the sound to
/// \param message the message to encode
void Audio::generate_afsk(std::vector<double> &vector, std::vector<bool> &message) {
    long length = static_cast<long>(round(SAMPLE_RATE * (1 / DATA_RATE)));

    for (bool i : message) {
        if (i) {
            generate_tone(MARK_FREQ, vector, length);
        } else {
            generate_tone(SPACE_FREQ, vector, length);
        }
    }
}


void Audio::generate_silence(std::vector<double> &vector, long length) {
    generate_tone(0, vector, length);
}

void Audio::create_wav(vector<double> *sound_data, const std::string &fileName) {
    struct SF_INFO info {};

    info.channels = 1;
    info.format = SF_FORMAT_WAV | SF_FORMAT_PCM_32;
    info.samplerate = SAMPLE_RATE;
    info.sections = 1;
    info.seekable = 1;

    SNDFILE *sf = sf_open(fileName.c_str(), SFM_WRITE, &info);
    if (sf_write_double(sf, sound_data->data(), sound_data->size()) != sound_data->size()) {
        fprintf(stderr, "%s\n", sf_error_number(sf_error(sf)));
    } else {
        std::cout << "Wrote EAS alert to";
    }
    sf_write_sync(sf);
    sf_close(sf);
}