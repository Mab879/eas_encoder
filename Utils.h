//
// Created by Matthew Burket on 10/19/18.
//

#ifndef SAMEENCODER_UTILS_H
#define SAMEENCODER_UTILS_H

#include <vector>
#include <string>

class Utils {
public:
    static void string_to_bit_stream(std::vector<bool> &vector, std::string message);
    static void bit_string_to_bit_stream(std::vector<bool> &vector, std::string bitstring);
};
#endif //SAMEENCODER_UTILS_H
