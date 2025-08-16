#include "daisy_pod.h"
#include "daisysp.h"

using namespace daisy;
using namespace daisysp;

DaisyPod pod;

// Audio callback: copy input to output
void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{

    
    
    for(size_t i = 0; i < size; i++)
    {
        // passthrough left and right channels
        out[0][i] = in[0][i];
        out[1][i] = in[1][i];
    }
}

int main(void)
{
    // Initialize hardware
    pod.Init();
    pod.SetAudioBlockSize(4);
    pod.StartAdc();
    pod.StartAudio(AudioCallback);

    pod.led1.Set(1.0f, 0.0f, 0.0f); // red, green, blue
    pod.led2.Set(1.0f, 0.0f, 0.0f);

     pod.UpdateLeds();
    
    
    while(1)
    {
        // Keep running
      //  pod.Update();
    }
}
