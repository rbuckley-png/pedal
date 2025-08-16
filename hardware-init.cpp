#include "daisysp.h"
#include "daisy_seed.h"
#include "daisy_pod.h"

using namespace daisysp;
using namespace daisy;

#define hardwareCheckPin1 22
#define hardwareCheckPin2 23

// pointer for audio callback
using AudioCb = void (*)(AudioHandle::InterleavingInputBuffer,
                         AudioHandle::InterleavingOutputBuffer,
                         size_t);

//enums for state of the hardware  
enum class Effect : int
{
    POD = 99, 
    OVERDRIVE = 2,
    NONE = -1  // optional default
};

// compute effect from stateA, stateB (1–10)
inline Effect GetEffect(int stateA, int stateB)
{
    return static_cast<Effect>((stateA - 1) * 10 + (stateB - 1));
}

DaisySeed hardware;
AdcChannelConfig adc_cfg[2];


void initializePodHardware(AudioCb AudioCallback){
static DaisyPod pod;
     pod.Init();
    pod.SetAudioBlockSize(4);
     pod.StartAdc();
    pod.StartAudio(AudioCallback);
}


void intializeEffectHardware(AudioCb AudioCallback){ 
//hardware.Configure();
hardware.Init();

//add a delay maybe?? to allow voltage to stabilize

//make adc config objects
adc_cfg[0].InitSingle(hardware.GetPin(hardwareCheckPin1));
adc_cfg[1].InitSingle(hardware.GetPin(hardwareCheckPin2));

// Init and start ADC
hardware.adc.Init(adc_cfg, 2);
hardware.adc.Start();

float hw_state1 = hardware.adc.GetFloat(0);
float hw_state2 = hardware.adc.GetFloat(1);

int stateA = (int)ceil(hw_state1 * 10.0f); // 1-10
int stateB = (int)ceil(hw_state2 * 10.0f); // 1-10 

Effect fx = GetEffect(stateA, stateB);

hardware.adc.Stop();
hardware.DeInit();

switch(fx)
{
    case Effect::NONE:
    
        break;
    case Effect::POD:
        initializePodHardware(AudioCallback);
        break;
    case Effect::OVERDRIVE:
        // Handle effect 1 here
        break;
    default:
        // TO:DO intialize Pod hardware

        break;


}
}
    // Initialize the Daisy Seed hardware

