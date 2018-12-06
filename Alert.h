/* This file is a part of EAS Encoder.
 *
 * Copyright (C) 2018 Matthew Burket
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 */

#ifndef SAMEENCODER_ALERT_H
#define SAMEENCODER_ALERT_H

#include <vector>
#include <string>

/**
 * This this represents an EAS Alert
 */
class Alert {
public:
    enum WATs {
        NORMAL_WAT, NRW_WAT
    };
    std::string origin;
    std::string event;
    std::string length;
    std::vector<std::string> areas;
    int date;
    int hour;
    int minute;
    std::string participant;
    WATs wat;
    void create_alert(std::string filename);
    std::string create_header_string();
    void create_wat(const std::vector<double> *sound_data);

private:
    void create_eom_tones(const std::vector<double> *sound_data) const;
    void create_header_tones(const std::vector<double> *sound_data, const std::string &header) const;
};


#endif //SAMEENCODER_ALERT_H
