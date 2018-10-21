//
// Created by Matthew Burket on 10/18/18.
//

#ifndef SAMEENCODER_AUDIO_H
#define SAMEENCODER_AUDIO_H
#include <vector>

class Audio {
public:
     static void generate_tone(double freq, std::vector<double> &vector, long length);
     static void generate_afsk(std::vector<double> &vector, std::vector<bool> &message);
     static void generate_dual_tone(double freq1, double freq2, std::vector<double> &vector, long length);
};
#endif //SAMEENCODER_AUDIO_H
