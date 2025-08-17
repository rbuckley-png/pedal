#include "hardware-init.h"

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

Effect fx = readHardwareState();
    switch(fx){
        case Effect::NONE:
            break;
        case Effect::POD:
            initializePodHardware(AudioCallback);
            break;
        case Effect::OVERDRIVE:
            break;
        default:
         initializePodHardware(AudioCallback);
            break;
    }
}

// compute effect from stateA, stateB (1–10)
inline Effect GetEffect(int stateA, int stateB)
{
    return static_cast<Effect>((stateA - 1) * 10 + (stateB - 1));
}


Effect readHardwareState(){
    //reaad pins and find effect
    hardware.Init();

    adc_cfg[0].InitSingle(hardware.GetPin(hardwareCheckPin1));
    adc_cfg[1].InitSingle(hardware.GetPin(hardwareCheckPin2));

    hardware.adc.Init(adc_cfg, 2);
    hardware.adc.Start();

    float hw_state1 = hardware.adc.GetFloat(0);
    float hw_state2 = hardware.adc.GetFloat(1);

    int state1 = (int)ceil(hw_state1 * 10.0f);
    int state2 = (int)ceil(hw_state2 * 10.0f);

    Effect fx = GetEffect(state1, state2);

    hardware.adc.Stop();
    hardware.DeInit();

    return fx;
}

    // Initialize the Daisy Seed hardware

