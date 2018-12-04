/* This file is a part of EAS Encoder.
 *
 * Copyright (C) 2018 Matthew Burket
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 */

#ifndef SAMEENCODER_UTILS_H
#define SAMEENCODER_UTILS_H

#include <vector>
#include <string>

class Utils {
public:
    static void string_to_bit_stream(std::vector<bool> &vector, std::string message);
    static void bit_string_to_bit_stream(std::vector<bool> &vector, std::string bitstring);
    static std::string zero_pad_int(int num, int totalLength);
};
#endif //SAMEENCODER_UTILS_H
