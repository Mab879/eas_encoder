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

#define TRUE 1

using namespace std;

string getChoice(vector<string> *vector);
string getChoice(vector<string> *vector, int perLine);
void getAreas(vector<string> *locations);
int getIntFromUser();
int getDate();
int getStartHour();
int getStartMinute();
std::string getParticipant();
void genSample(alert *alert);
WATs getWat();

int main() {
    auto *bits = new std::vector<bool>();
   Utils::string_to_bit_stream((vector<bool> &) *bits, "a");
   for (auto i = bits->begin(); i < bits->end(); i++) {
       cout << *i;
   }
   cout << endl;


    auto *a = new alert();

    vector<string> originators = {"EAS", "CIV", "WXR", "PIP"};

    string origin  = getChoice(&originators);

    vector<string> nationalEvents = {"EAN", "NIC", "NPT", "RMT", "RWT"};

    vector<string> stateEvents = { "ADR", "AVW", "AVA", "BZW", "BLU", "CAE", "CDW", "CEM", "CFW", "CFA", "DSW", "EQW", "EVI",
                             "EWW", "FRW", "FFW", "FFA", "FFS", "FLW", "FLA", "FLS", "HMW", "HWW", "HWA", "HUW", "HUA",
                             "HLS", "LEW", "LAE", "NMN", "TOE", "NUW", "DMO", "RHW", "SVR", "SVA", "SVS", "SPW", "SMW",
                             "SPS", "SSA", "SSW", "TOR", "TOA", "TRW", "TRA", "TSW", "TSA", "VOW", "WSW", "WSA"};
    vector<string> events;
    events.insert(events.end(), nationalEvents.begin(), nationalEvents.end());
    events.insert(events.end(), stateEvents.begin(), stateEvents.end());
    string event = getChoice(&events, 6);

    // Lengths, could be programmatically produced
    vector<string> lengths = {"0015", "0030", "0045", "0100", "0115", "0130", "0145", "0200", "0215", "2030"};
    string length = getChoice(&lengths);

    // Areas
    std::vector<std::string> areas;
    getAreas(&areas);

    a->length = length;
    a->origin = origin;
    a->event = event;
    a->areas = areas;
    // Get Date Info
    a->date = getDate();
    a->hour = getStartHour();
    a->minute = getStartMinute();
    a->participant = getParticipant();
    a->wat = getWat();
    genSample(a);
    delete a;
    exit(EXIT_SUCCESS);

}

WATs getWat() {
    vector<string> wats = { "NRW", "Normal"};
    string choice = getChoice(&wats);
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
   return getIntFromUser();
}

int getStartHour() {
    cout << "Enter Start Hour: ";
    return getIntFromUser();
}


int getStartMinute() {
    cout << "Enter the Start Minute: ";
    return getIntFromUser();
}

void getAreas(vector<string> *locations) {
    for (int i = 0; i < 13; i++) {
        string location;
        cout << "Enter location: ";
        cin >> location;
        if (location == "DONE") {
            cout << "Done Entering locations." << endl;
            break;
        } else {
            locations->push_back(location);
        }
    }
}

string getChoice(vector<string> *vector) {
        return getChoice(vector, 1);
}


int getIntFromUser() {
    while (TRUE) {
        string strNumber;
        cin >> strNumber;
        int i;
        try {
            i = stoi(strNumber);
        } catch  (std::invalid_argument) {
            continue;
        }
        return i;
    }
}

string getChoice(vector<string> *vector, int perLine) {
    int count = 1;
    for (auto &it : *vector) {
        cout << "[" << count << "] " << it << " ";
        if (count % perLine == 0) {
            cout << endl;
        }
        count++;
    }

    bool inputValid = false;
    unsigned long choice;
    cout << endl;
    do {
        printf("Enter choice: ");
        cin >> choice;
        if (choice < 0) {
            printf("Invalid choice, must be greater than 0.");
        } else if (choice > vector->size()) {
            printf("Invalid choice, must be less or equal to %zu.", vector->size());
        } else {
            inputValid = true;
        }
    } while (!inputValid);
    return vector->at(choice-1);
}

void genSample(alert *alert) {
    auto *sound_data = new std::vector<double>;
    auto *bits = new std::vector<bool>();

    std::string header;
    EAS::create_header(alert, header);

    Utils::bit_string_to_bit_stream((vector<bool> &) *bits, PREAMBLE);
    Utils::string_to_bit_stream((vector<bool> &) *bits, header);

    Audio::generate_silence((vector<double> &) *sound_data, SAMPLE_RATE);

    for (int i = 0; i < 3; i++) {
        Audio::generate_afsk((vector<double> &) *sound_data, (vector<bool> &) *bits);
        Audio::generate_silence((vector<double> &) *sound_data, SAMPLE_RATE);
    }

    bits->clear();

    EAS::create_wat(alert, sound_data);

    Audio::generate_silence((vector<double> &) *sound_data, SAMPLE_RATE);

    Utils::bit_string_to_bit_stream((vector<bool> &) *bits, PREAMBLE);
    Utils::string_to_bit_stream((vector<bool> &) *bits, EOM);

    for (int i = 0; i < 3; i++) {
        Audio::generate_afsk((vector<double> &) *sound_data, (vector<bool> &) *bits);
        Audio::generate_silence((vector<double> &) *sound_data, SAMPLE_RATE);
    }

    Audio::create_wav(sound_data, "eas_tone.wav");

    delete bits;
    delete sound_data;
}
