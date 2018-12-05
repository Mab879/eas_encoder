//
// Created by mburket on 12/1/18.
//

#ifndef SAMEENCODER_ALERT_H
#define SAMEENCODER_ALERT_H

#include <vector>
#include <string>

enum WATs {
    NORMAL_WAT, NRW_WAT
};

class alert {
public:
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

private:
    void create_eom_tones(const std::vector<double> *sound_data) const;
    void create_header_tones(const std::vector<double> *sound_data, const std::string &header) const;
};


#endif //SAMEENCODER_ALERT_H
