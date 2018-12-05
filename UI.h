/* This file is a part of EAS Encoder.
 *
 * Copyright (C) 2018 Matthew Burket
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 */

#ifndef SAMEENCODER_UI_H
#define SAMEENCODER_UI_H

#include <string>
#include <vector>

/**
 * This class has various UI helper methods
 */
class UI {
public:
    static std::string getChoice(std::vector<std::string> *vector);
    static std::string getChoice(std::vector<std::string> *vector, int perLine);
    static unsigned long getIntFromUser();
    static unsigned long getIntFromUser(unsigned long low, unsigned long high);
};


#endif //SAMEENCODER_UI_H
