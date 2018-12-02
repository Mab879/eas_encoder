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
#include <sndfile.h>
#include <vector>
#include <ncurses.h>
#include <boost/concept_check.hpp>

#include "Utils.h"
#include "eas.h"
#include "audio.h"
#include "alert.cpp"

using namespace std;

template<typename T>
struct vecvec : public std::vector< std::vector<T> > {};

string getChoice(vector<string> *vector);
string getChoice(vector<string> *vector, int perLine);
void getAreas(vector<string> *locations);
int getIntFromUser();
int getDate();
int getStartHour();
int getStartMinute();
std::string getParticipant();

int main() {
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

    // Lengths
    vector<string> lengths = {"00:15", "00:30", "00:45", "01:00", "01:15", "01:30", "01:45", "02:00"};
    string length = getChoice(&lengths);

    // Areas
    std::vector<std::string> areas;
    getAreas(&areas);

    a->areas = areas;
    // Get Date Info
    a->date = getDate();
    a->hour = getStartHour();
    a->minute = getStartMinute();
    std::string part = getParticipant();
    delete a;
    exit(EXIT_SUCCESS);

}

std::string getParticipant() {
    cout << "Get Participant: ";
    std::string part;
    while (TRUE) {
        cin >> part;
        if (part.length() != 8) {
            cout << "Participant must 8 charaters long";
        }
        return part;
    }
    return part;
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
            cout << "Done Entering locations.";
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
    for (auto it = vector->begin(); it != vector->end(); it++) {
        cout << "[" << count << "] " << *it << " ";
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

void genSample(alert) {
    auto *sound_data = new std::vector<double>;
    auto *bits = new std::vector<bool>();

    Utils::bit_string_to_bit_stream((vector<bool> &) *bits, PREAMBLE);
    Utils::string_to_bit_stream((vector<bool> &) *bits, HEADER);
    Utils::string_to_bit_stream((vector<bool> &) *bits, "-WXR");
    Utils::string_to_bit_stream((vector<bool> &) *bits, "-TOR");
    Utils::string_to_bit_stream((vector<bool> &) *bits, "-019169");
    Utils::string_to_bit_stream((vector<bool> &) *bits, "-019153");
    Utils::string_to_bit_stream((vector<bool> &) *bits, "+0045");
    Utils::string_to_bit_stream((vector<bool> &) *bits, "-2941320");
    Utils::string_to_bit_stream((vector<bool> &) *bits, "-KDSM/NWS-");

    Audio::generate_tone(0, (vector<double> &) *sound_data, SAMPLE_RATE);

    Audio::generate_afsk((vector<double> &) *sound_data, (vector<bool> &) *bits);
    Audio::generate_tone(0, (vector<double> &) *sound_data, SAMPLE_RATE);

    Audio::generate_afsk((vector<double> &) *sound_data, (vector<bool> &) *bits);
    Audio::generate_tone(0, (vector<double> &) *sound_data, SAMPLE_RATE);

    Audio::generate_afsk((vector<double> &) *sound_data, (vector<bool> &) *bits);
    Audio::generate_tone(0, (vector<double> &) *sound_data, SAMPLE_RATE);

    bits->clear();

    //Audio::generate_tone(NRW_WAT_FREQ, (vector<double> &) *sound_data, SAMPLE_RATE * 8);
    //Audio::generate_dual_tone(WAT_FREQ_1, WAT_FREQ_2, (vector<double> &) *sound_data, SAMPLE_RATE * 5);
    Audio::generate_tone(0, (vector<double> &) *sound_data, SAMPLE_RATE);

    Utils::bit_string_to_bit_stream((vector<bool> &) *bits, PREAMBLE);
    Utils::string_to_bit_stream((vector<bool> &) *bits, EOM);

    Audio::generate_afsk((vector<double> &) *sound_data, (vector<bool> &) *bits);
    Audio::generate_tone(0, (vector<double> &) *sound_data, SAMPLE_RATE);

    Audio::generate_afsk((vector<double> &) *sound_data, (vector<bool> &) *bits);
    Audio::generate_tone(0, (vector<double> &) *sound_data, SAMPLE_RATE);

    Audio::generate_afsk((vector<double> &) *sound_data, (vector<bool> &) *bits);
    Audio::generate_tone(0, (vector<double> &) *sound_data, SAMPLE_RATE);

    struct SF_INFO info {};

    info.channels = 1;
    info.format = SF_FORMAT_WAV | SF_FORMAT_PCM_32;
    info.samplerate = SAMPLE_RATE;
    info.sections = 1;
    info.seekable = 1;

    const char *fileName = "eas_ean.wav";

    SNDFILE *sf = sf_open(fileName, SFM_WRITE, &info);
    fprintf(stderr, "%s\n", sf_error_number(sf_error(sf)));
    if (sf_write_double(sf, sound_data->data(), sound_data->size()) != sound_data->size()) {
        fprintf(stderr, "%s\n", sf_error_number(sf_error(sf)));
    }
    sf_write_sync(sf);
    sf_close(sf);

    delete bits;
    delete sound_data;
}

