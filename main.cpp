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
#include <math.h>
#include <vector>
#include <algorithm>

#include "Utils.h"
#include "eas.h"
#include "audio.h"
#include "Alert.cpp"
#include "UI.h"

#define TRUE 1

void getAreas(std::vector<std::string> *locations);
int getDate();
int getStartHour();
int getStartMinute();
std::string getParticipant();
Alert::WATs getWat();
std::string getOrigin();
std::string getEvent();
std::string getLength();

std::string getFileName();

int main() {
    auto *a = new Alert();

    a->origin = getOrigin();

    a->event = getEvent();

    // Length
    a->length = getLength();

    // Areas
    std::vector<std::string> areas;
    getAreas(&areas);
    a->areas = areas;

    // Get Date Info
    a->date = getDate();
    a->hour = getStartHour();
    a->minute = getStartMinute();
    a->participant = getParticipant();
    a->wat = getWat();

    std::string filename = getFileName();

    a->create_alert(filename);
    delete a;
    exit(EXIT_SUCCESS);

}

/// get the filename for the alert
/// \return
std::string getFileName() {
    std::cout << "Enter file name, should end with .wav: ";
    std::string filename;
    std::cin >> filename;
    return filename;
}

/// Get the length of the alert
/// \return
std::string getLength() {
    // Could be programmatically produced
    std::vector<std::string> lengths = {"0015", "0030", "0045", "0100", "0115", "0130", "0145", "0200", "2030", "0300",
                                        "0330", "0400", "0430", "0500", "0530", "0600", "6030", "0700", "0730", "0800"};
    std::string length = UI::getChoice(&lengths);
    return length;
}

/// Get the event code for the alert
/// \return
std::string getEvent() {
    std::vector<std::string> nationalEvents = {"EAN", "NIC", "NPT", "RMT", "RWT"};

    std::vector<std::string> stateEvents = { "ADR", "AVW", "AVA", "BZW", "BLU", "CAE", "CDW", "CEM", "CFW", "CFA", "DSW", "EQW", "EVI",
                                   "EWW", "FRW", "FFW", "FFA", "FFS", "FLW", "FLA", "FLS", "HMW", "HWW", "HWA", "HUW", "HUA",
                                   "HLS", "LEW", "LAE", "NMN", "TOE", "NUW", "DMO", "RHW", "SVR", "SVA", "SVS", "SPW", "SMW",
                                   "SPS", "SSA", "SSW", "TOR", "TOA", "TRW", "TRA", "TSW", "TSA", "VOW", "WSW", "WSA"
                                 };
    std::vector<std::string> events;
    events.insert(events.end(), nationalEvents.begin(), nationalEvents.end());
    events.insert(events.end(), stateEvents.begin(), stateEvents.end());
    std::string event = UI::getChoice(&events, 6);
    return event;
}

/// Get the origin of the alert
/// \return
std::string getOrigin() {
    std::vector<std::string> originators = {"EAS", "CIV", "WXR", "PEP"};

    std::string origin  = UI::getChoice(&originators);
    return origin;
}

/// Get the WAT the user wants for the alert
/// \return
Alert::WATs getWat() {
    std::cout << "Select the Attention Tone" << std::endl;
    std::vector<std::string> wats = { "NRW", "Normal" };
    std::string choice = UI::getChoice(&wats);
    if (choice == wats[0]) {
        return Alert::NRW_WAT;
    } else {
        return Alert::NORMAL_WAT;
    }

}

/// Get the participaint for the alert
/// Last part of the header
/// \return
std::string getParticipant() {
    std::cout << "Participant: ";
    std::string part;
    while (TRUE) {
        std::cin >> part;
        if (part.length() != 8) {
            std::cout << "Participant must 8 characters long";
        }
        return part;
    }
}

/// Get the date for the alert
/// \return
int getDate() {
    std::cout << "Enter Start Date: ";
    return UI::getIntFromUser(0, 366);
}


/// Get the start hour of the alert
/// \return
int getStartHour() {
    std::cout << "Enter Start Hour: ";
    return UI::getIntFromUser(0, 23);
}

/// Get the start minute of the alert with
/// \return
int getStartMinute() {
    std::cout << "Enter the Start Minute: ";
    return UI::getIntFromUser(0, 59);
}

/// Get the areas for the alert from the user
/// \param locations
void getAreas(std::vector<std::string> *locations) {
    std::cout << "Type \"DONE\" when done entering locations" << std::endl;
    for (int i = 0; i < 31; i++) {
        std::string location;
        std::cout << "Enter location: ";
        std::cin >> location;
        if (location == "DONE") {
            std:: cout << "Done Entering locations." << std::endl;
            break;
        } else {
            locations->push_back(Utils::zero_pad_int(location, 6));
        }
    }
}
