
#include "hardware-init.h"

using namespace daisy;
using namespace daisysp;


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
    
    
    while(1)
    {
        // Keep running
      //  pod.Update();
    }
}
