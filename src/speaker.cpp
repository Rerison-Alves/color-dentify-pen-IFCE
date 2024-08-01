#include <Arduino.h>
#include "speaker.h"
#include <XT_DAC_Audio.h>

Speaker::Speaker(int pin_S25){
    S25 = pin_S25;
    
    
}

void Speaker::play_audio(const unsigned char* sample){
    XT_Wav_Class Sound(sample); 
    XT_DAC_Audio_Class DacAudio(25,0);
    DacAudio.FillBuffer();
    if(Sound.Playing==false) 
     DacAudio.Play(&Sound);

}
