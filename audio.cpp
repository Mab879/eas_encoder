//
// Created by Matthew Burket on 10/18/18.
//
#include "eas.h"
#include <math.h>
#include <string>
#include "audio.h"

using namespace std;

/// Add the wave data to the given double vector
/// \param freq freqeunce of the tone in hertz
/// \param vector vector to add samples to
/// \param length length in number of samples
void Audio::generate_tone(double freq, std::vector<double> &vector, long length) {
    for (int i = 0; i < length; i++) {
        vector.push_back(sin((i * 2 * M_PI  * freq) / SAMPLE_RATE));
    }
}

void Audio::generate_dual_tone(double freq1, double freq2, std::vector<double> &vector, long length) {
    for (int i = 0; i < length; i++) {
        double value = sin((i * 2 * M_PI  * freq1) / SAMPLE_RATE) + sin((i * 2 * M_PI  * freq1) / SAMPLE_RATE);
        vector.push_back(value);
    }
}

/// From a bitsteam, add the PCM wave bits to to the given vector
/// \param vector the vector to add the sound to
/// \param message the message to encode
void Audio::generate_afsk(std::vector<double> &vector, __1::vector<bool> &message) {
    long length = static_cast<long>(round(SAMPLE_RATE * (1 / DATA_RATE)));

    for (short i : message) {
        if (i == 0) {
            generate_tone(MARK_FREQ, vector, length);
        } else {
            generate_tone(SPACE_FREQ, vector, length);
        }
    }
}