#include "daisysp.h"
#include "daisy_seed.h"

using namespace daisysp;
using namespace daisy;

#define hardwareCheckPin1 22
#define hardwareCheckPin2 23

//enums for state of the hardware
enum class Effect : int
{
    None = -1  // optional default
};

// compute effect from stateA, stateB (1–10)
inline Effect GetEffect(int stateA, int stateB)
{
    return static_cast<Effect>((stateA - 1) * 10 + (stateB - 1));
}

DaisySeed hardware;
AdcChannelConfig adc_cfg[2];

int main (void){

hardware.Configure();
hardware.Init();

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

switch(static_cast<int>(fx))
{
    case 0:
        // No effect selected
        break;
    case 1:
        // Handle effect 1 here
        break;
    default:
        // intialize Pod hardware

        break;


}
}