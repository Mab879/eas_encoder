/* This file is a part of EAS Encoder.
 *
 * Copyright (C) 2018 Matthew Burket
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 */

#ifndef SAMEENCODER_AUDIO_H
#define SAMEENCODER_AUDIO_H
#include <vector>

/**
 * This class contains audio related helper functions.
 */
class Audio {
public:
    static void generate_tone(double freq, std::vector<double> &vector, long length);
    static void generate_afsk(std::vector<double> &vector, std::vector<bool> &message);
    static void generate_dual_tone(double freq1, double freq2, std::vector<double> &vector, long length);
    static void generate_silence(std::vector<double> &vector, long length);
    static void create_wav(std::vector<double> *sound_data, const std::string &fileName);
};
#endif //SAMEENCODER_AUDIO_H
