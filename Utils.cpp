//
// Created by Matthew Burket on 10/19/18.
//

#include <string>
#include <vector>
#include <bitset>
#include "Utils.h"

/// Given a string convert each character to binary add that binary to the given vector
/// \param vector the vector to add the bits to
/// \param message the message to convert to binary
void Utils::string_to_bit_stream(std::vector<bool> &vector, std::string message) {
    for (std::size_t i = 0; i < message.size(); i++) {
        auto bitstring = std::bitset<8>(message.c_str()[i]);

        for (int j = 0; j < bitstring.size(); j++) {
            vector.push_back(bitstring[j]);
        }
    }
}

/// Converts a string of "0" and "1" to bool values add them to the given vector
/// \param vector vector the vector to add the bits to
/// \param bitstring the bitstring to convert
void Utils::bit_string_to_bit_stream(std::vector<bool> &vector, std::string bitstring) {
    for (std::size_t i = 0; i < bitstring.size(); i++) {
        if (bitstring[i] == '0') {
            vector.push_back(false);
        } else if {
            vector.push_back(true);
        }
        else {
            throw std::invalid_argument("The string can only contain 0 and 1");
        }
    }
}

