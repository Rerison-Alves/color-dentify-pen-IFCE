#ifndef SPEAKER_H
#define SPEAKER_H

class Speaker{
public:
    Speaker(int pin_S25);
    void play_audio(const unsigned char* sample);
    

private:
    int S25;
};

#endif