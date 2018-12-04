//
// Created by mburket on 12/1/18.
//

#include "alert.h"

void alert::create_alert(std::string filename) {
    auto *sound_data = new std::vector<double>;
    auto *bits = new std::vector<bool>();

    std::string header;
    EAS::create_header(this, header);

    Utils::bit_string_to_bit_stream((std::vector<bool> &) *bits, PREAMBLE);
    Utils::string_to_bit_stream((std::vector<bool> &) *bits, header);

    Audio::generate_silence((std::vector<double> &) *sound_data, SAMPLE_RATE);

    for (int i = 0; i < 3; i++) {
        Audio::generate_afsk((std::vector<double> &) *sound_data, (std::vector<bool> &) *bits);
        Audio::generate_silence((std::vector<double> &) *sound_data, SAMPLE_RATE);
    }

    bits->clear();

    EAS::create_wat(this, sound_data);

    Audio::generate_silence((std::vector<double> &) *sound_data, SAMPLE_RATE);

    create_eom(sound_data, bits);

    Audio::create_wav(sound_data, filename);

    delete bits;
    delete sound_data;
}

void alert::create_eom(const std::vector<double> *sound_data, const std::vector<bool> *bits) const {
    Utils::bit_string_to_bit_stream((std::vector<bool> &) *bits, PREAMBLE);
    Utils::string_to_bit_stream((std::vector<bool> &) *bits, EOM);

    for (int i = 0; i < 3; i++) {
        Audio::generate_afsk((std::vector<double> &) *sound_data, (std::vector<bool> &) *bits);
        Audio::generate_silence((std::vector<double> &) *sound_data, SAMPLE_RATE);
    }
}
