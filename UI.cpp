//
// Created by mburket on 12/4/18.
//

#include <iostream>
#include "UI.h"

#define TRUE 1

std::string UI::getChoice(std::vector<std::string> *vector) {
    return getChoice(vector, 1);
}

std::string UI::getChoice(std::vector<std::string> *vector, int perLine) {
    int count = 1;
    for (auto &it : *vector) {
        std::cout << "[" << count << "] " << it << " ";
        if (count % perLine == 0) {
            std::cout << std::endl;
        }
        count++;
    }

    bool inputValid = false;
    unsigned long choice;
    std::cout << std::endl;
    do {
        printf("Enter choice: ");
        std::cin >> choice;
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

int UI::getIntFromUser() {
    while (TRUE) {
        std::string strNumber;
        std::cin >> strNumber;
        int i;
        try {
            i = stoi(strNumber);
        } catch  (std::invalid_argument) {
            continue;
        }
        return i;
    }
}
