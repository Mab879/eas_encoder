//
// Created by mburket on 12/1/18.
//

#ifndef SAMEENCODER_ALERT_H
#define SAMEENCODER_ALERT_H

#include <vector>
#include <string>

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
};


#endif //SAMEENCODER_ALERT_H
