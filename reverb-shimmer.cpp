#include "daisysp.h"
#include "daisy_seed.h"

using namespace daisysp;
using namespace daisy;

DaisySeed    hw;
PitchShifter DSY_SDRAM_BSS ps;
Oscillator   osc;

ReverbSc   reverb;
AdEnv      env;
Metro      tick;

float pot_1, pot_2;

static void AudioCallback(AudioHandle::InterleavingInputBuffer  in,
                          AudioHandle::InterleavingOutputBuffer out,
                          size_t                                size)
{
    float outl, outr, inl, inr;

    pot_1 = hw.adc.GetFloat(0);
    pot_2 = hw.adc.GetFloat(1);

    for(size_t i = 0; i < size; i += 2)
    {
        inl = in[i];
        inr = in[i + 1];
        // reverb
        reverb.Process(inl, inr, &outl, &outr);
        // reverb.SetFeedback(0.85f * pot_2);
        // ps.SetTransposition(12.0f * pot_2);

        outl = pot_1 * outl + (1 - pot_1) * inl;
        outr = pot_1 * outr + (1 - pot_1) * inr;

        // shift
        outl = ps.Process(outl);
        outr = ps.Process(outr);

        outl = inl + outl;
        outr = inr + outr;

        out[i] = outr;
        out[i + 1] = outl;
    }
}

void InitInputs() {
    AdcChannelConfig adcConfig[2];
    adcConfig[0].InitSingle(seed::A0);
    adcConfig[1].InitSingle(seed::A6);
    hw.adc.Init(adcConfig, 2);
}

int main(void)
{
    // PS PORTION
    // initialize seed hardware and daisysp modules
    float sample_rate;
    hw.Configure();
    hw.Init();
    hw.SetAudioBlockSize(4);

    sample_rate = hw.AudioSampleRate();

    // Initialize reverb
    reverb.Init(sample_rate);
    reverb.SetFeedback(0.85f);    // Set reverb feedback amount
    reverb.SetLpFreq(10000.0f);   // Set low-pass filter frequency

    ps.Init(sample_rate);
    // set transposition 1 octave up (12 semitones)
    ps.SetTransposition(12.0f);

    //setup oscillator
    osc.Init(sample_rate);
    osc.SetFreq(440.f);
    osc.SetWaveform(Oscillator::WAVE_TRI);

    InitInputs();
    hw.adc.Start();

    // start callback
    hw.StartAudio(AudioCallback);

    while(1) {}
}


