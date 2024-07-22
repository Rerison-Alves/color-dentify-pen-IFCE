#ifndef SPEAKER_H
#define SPEAKER_H

class Speaker{
public:
    Speaker(int pin_S25, int pin_vcc, int pin_gnd);
    void play_audio(sample);
    

private:
    int S25, vcc, gnd;
};

#endif