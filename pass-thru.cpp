
#include "hardware-init.cpp"

using namespace daisy;
using namespace daisysp;

DaisyPod pod;

// Audio callback: copy input to output
void AudioCallback(AudioHandle::InterleavingInputBuffer  in,
                   AudioHandle::InterleavingOutputBuffer out, size_t size)
{

    
    
    for(size_t i = 0; i < size; i+=2)
    {
        // passthrough left and right channels
        out[i] = in[i];
        out[i + 1] = in[i + 1];
    }
}

int main(void)
{
    // Initialize hardware
    intializeEffectHardware(AudioCallback);

    pod.led1.Set(1.0f, 0.0f, 0.0f); // red, green, blue
    pod.led2.Set(1.0f, 0.0f, 0.0f);

     pod.UpdateLeds();
    
    
    while(1)
    {
        // Keep running
      //  pod.Update();
    }
}
