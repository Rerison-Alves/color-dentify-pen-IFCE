#include <Arduino.h>
#include "speaker.h"
#include "XT_DAC_Audio.h"

Speaker::Speaker(int pin_S25, int pin_vcc, int pin_gnd){
    S25 = pin_S25;
    vcc = pin_vcc;
    gnd = pin_gnd;
    
}

void Speaker::play_audio(sample){
    XT_Wav_Class Sound(sample); 
    XT_DAC_Audio_Class DacAudio(25,0);
    DacAudio.FillBuffer();
    DacAudio.Play(&Sound);

}
