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
#include "alert.cpp"
#include "UI.h"

#define TRUE 1

using namespace std;

void getAreas(vector<string> *locations);
int getDate();
int getStartHour();
int getStartMinute();
std::string getParticipant();
WATs getWat();
string getOrigin();
string getEvent();
string getLength();

int main() {
    auto *a = new alert();

    a->origin = getOrigin();

    a->event = getEvent();

    // Lengths, could be programmatically produced
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

    a->create_alert("eas_alert_1.wav");
    delete a;
    exit(EXIT_SUCCESS);

}

string getLength() {
    vector<string> lengths = {"0015", "0030", "0045", "0100", "0115", "0130", "0145", "0200", "0215", "2030"};
    string length = UI::getChoice(&lengths);
    return length;
}

string getEvent() {
    vector<string> nationalEvents = {"EAN", "NIC", "NPT", "RMT", "RWT"};

    vector<string> stateEvents = { "ADR", "AVW", "AVA", "BZW", "BLU", "CAE", "CDW", "CEM", "CFW", "CFA", "DSW", "EQW", "EVI",
                             "EWW", "FRW", "FFW", "FFA", "FFS", "FLW", "FLA", "FLS", "HMW", "HWW", "HWA", "HUW", "HUA",
                             "HLS", "LEW", "LAE", "NMN", "TOE", "NUW", "DMO", "RHW", "SVR", "SVA", "SVS", "SPW", "SMW",
                             "SPS", "SSA", "SSW", "TOR", "TOA", "TRW", "TRA", "TSW", "TSA", "VOW", "WSW", "WSA"};
    vector<string> events;
    events.insert(events.end(), nationalEvents.begin(), nationalEvents.end());
    events.insert(events.end(), stateEvents.begin(), stateEvents.end());
    string event = UI::getChoice(&events, 6);
    return event;
}

string getOrigin() {
    vector<string> originators = {"EAS", "CIV", "WXR", "PEP"};

    string origin  = UI::getChoice(&originators);
    return origin;
}

WATs getWat() {
    vector<string> wats = { "NRW", "Normal" };
    string choice = UI::getChoice(&wats);
    if (choice == wats[0]) {
        return NRW_WAT;
    } else {
        return NORMAL_WAT;
    }

}

std::string getParticipant() {
    cout << "Participant: ";
    std::string part;
    while (TRUE) {
        cin >> part;
        if (part.length() != 8) {
            cout << "Participant must 8 characters long";
        }
        return part;
    }
}

int getDate() {
   cout << "Enter Start Date: ";
   return UI::getIntFromUser();
}

int getStartHour() {
    cout << "Enter Start Hour: ";
    return UI::getIntFromUser();
}


int getStartMinute() {
    cout << "Enter the Start Minute: ";
    return UI::getIntFromUser();
}

void getAreas(vector<string> *locations) {
    for (int i = 0; i < 31; i++) {
        string location;
        cout << "Enter location: ";
        cin >> location;
        if (location == "DONE") {
            cout << "Done Entering locations." << endl;
            break;
        } else {
            locations->push_back(Utils::zero_pad_int(location, 6));
        }
    }
}