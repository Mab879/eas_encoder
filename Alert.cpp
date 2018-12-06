/* This file is a part of EAS Encoder.
 *
 * Copyright (C) 2018 Matthew Burket
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 */

#include "Alert.h"
#include "eas.h"
#include "audio.h"
#include "Utils.h"

/// Given a file name will create an WAV of EAS tone from this alert
/// \param filename filename to save the WAV as
void Alert::create_alert(std::string filename) {
    auto *sound_data = new std::vector<double>;
    std::string header = create_header_string();
    create_header_tones(sound_data, header);
    create_wat(sound_data);
    Audio::generate_silence((std::vector<double> &) *sound_data, SAMPLE_RATE);
    create_eom_tones(sound_data);
    Audio::create_wav(sound_data, filename);
    delete sound_data;
}

/// Creates EAS header string
/// \return header of this alert
std::string Alert::create_header_string() {
    std::string header;
    header.append(HEADER);
    header.push_back('-');
    header.append(this->origin);
    header.push_back('-');
    header.append(this->event);
    for (auto locationsIter = this->areas.begin(); locationsIter < this->areas.end(); locationsIter++) {
        header.push_back('-');
        header.append(*locationsIter);

    }
    header.push_back('-');
    header.append(this->length);
    header.push_back('-');
    header.append(Utils::zero_pad_int(this->date,3));
    header.append(Utils::zero_pad_int(this->hour, 2));
    header.append(Utils::zero_pad_int(this->minute, 2));
    header.push_back('-');
    header.append(this->participant);
    header.push_back('-');
    return header;
}

/// Create the header
/// \param sound_data the
/// \param bits
/// \param header
void Alert::create_header_tones(const std::vector<double> *sound_data, const std::string &header) const {
    auto *bits = new std::vector<bool>();
    Utils::bit_string_to_bit_stream((std::vector<bool> &) *bits, PREAMBLE);
    Utils::string_to_bit_stream((std::vector<bool> &) *bits, header);

    Audio::generate_silence((std::vector<double> &) *sound_data, SAMPLE_RATE);

    for (int i = 0; i < 3; i++) {
        Audio::generate_afsk((std::vector<double> &) *sound_data, (std::vector<bool> &) *bits);
        Audio::generate_silence((std::vector<double> &) *sound_data, SAMPLE_RATE);
    }
}

/// Creates the end of message tones
/// \param sound_data
/// \param bits
void Alert::create_eom_tones(const std::vector<double> *sound_data) const {
    auto *bits = new std::vector<bool>();
    Utils::bit_string_to_bit_stream((std::vector<bool> &) *bits, PREAMBLE);
    Utils::string_to_bit_stream((std::vector<bool> &) *bits, EOM);

    for (int i = 0; i < 3; i++) {
        Audio::generate_afsk((std::vector<double> &) *sound_data, (std::vector<bool> &) *bits);
        Audio::generate_silence((std::vector<double> &) *sound_data, SAMPLE_RATE);
    }
}

/// Create the attention based on the
/// \param sound_data
void Alert::create_wat(const std::vector<double> *sound_data) {
    if (this->wat == NRW_WAT) {
        Audio::generate_tone(NRW_WAT_FREQ, (std::vector<double> &) *sound_data, SAMPLE_RATE * 8);
    } else {
        Audio::generate_dual_tone(WAT_FREQ_1, WAT_FREQ_2, (std::vector<double> &) *sound_data, SAMPLE_RATE * 5);
    }
}
