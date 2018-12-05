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
#include "UI.h"

#define TRUE 1

/// Have the user choose a choice
/// One per online
/// \param vector the vector of string for the user to pick from
/// \return the string they chose
std::string UI::getChoice(std::vector<std::string> *vector) {
    return getChoice(vector, 1);
}

/// Have the user choose a choice
/// \param vector the vector of string for the user to pick from
/// \param perLine the number of choices per line
/// \return the string they chose
std::string UI::getChoice(std::vector<std::string> *vector, int perLine) {
    int count = 1;
    for (auto &it : *vector) {
        std::cout << "[" << count << "] " << it << " ";
        if (count % perLine == 0) {
            std::cout << std::endl;
        }
        count++;
    }

    std::cout << std::endl;
    unsigned long choice = getIntFromUser(1, vector->size());
    return vector->at(choice-1);
}

/// Get an integer from the user
/// \return the integer the user entered
unsigned long UI::getIntFromUser() {
    while (true) {
        std::string strNumber;
        std::cin >> strNumber;
        unsigned long  i;
        try {
            i = stoul(strNumber);
        } catch  (std::invalid_argument) {
            continue;
        }
        return i;
    }
}

/// Get a integer from the user in a range
/// \param low the lowest acceptable integer
/// \param high the highest acceptable integer
/// \return an integer from the user in the given range
unsigned long UI::getIntFromUser(unsigned long low, unsigned long high) {
    while (true) {
        unsigned long userInt = getIntFromUser();
        if (userInt < low) {
            std::cout << "You must enter a integer greater than or equal to " << low << std::endl;
        } else if (userInt > high) {
            std::cout << "You must enter a integer less than or equal to " << high << std::endl;
        } else {
            return userInt;
        }
    }
}
