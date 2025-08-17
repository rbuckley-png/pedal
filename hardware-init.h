#pragma once

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
    NONE = -1
};

// Function declarations
Effect readHardwareState();      /// Reads the hardware state and returns the effect
Effect GetEffect(int stateA, int stateB);  ///Helper Function that Computes the effect from two states (1-10) 
void intializeEffectHardware(AudioCb AudioCallback); /// Initializes the effect hardware based on the Effect state 
void initializePodHardware(AudioCb AudioCallback); /// Initializes the Daisy Pod hardware if the effect is POD



// Global variables
extern DaisySeed hardware;
extern AdcChannelConfig adc_cfg[2];