//
// Created by mburket on 12/4/18.
//

#ifndef SAMEENCODER_UI_H
#define SAMEENCODER_UI_H

#include <string>
#include <vector>

class UI {
public:
    static std::string getChoice(std::vector<std::string> *vector);
    static std::string getChoice(std::vector<std::string> *vector, int perLine);
    static int getIntFromUser();
};


#endif //SAMEENCODER_UI_H
