// Created by Bradly Landucci

#include <usermodfx.h>
#include "fx_api.h"

// Initializing Params //
static float distamt = 0.5f;
static float wet = 0.5f;

// Simple waveshaping algorithm //
// x' = 3/2x - 1/2(x^3)
// https://www.musicdsp.org/en/latest/Effects/114-waveshaper-simple-description.html
float __fast_inline waveshape(float in) 
{
    return 1.5f * in - 0.5f * in *in * in;
}

// Initializing Platform //
void MODFX_INIT(uint32_t platform, uint32_t api)
{
}

// Main DSP Process Block //
// Sub values to be ignored, only used for prologue
void MODFX_PROCESS(const float *xn, float *yn,
                   const float *sub_xn, float *sub_yn,
                   uint32_t frames)
{
  float base_main;
  float wet_signal;

  // Effect processing loop //
  // For double frames (AKA samples cause each frame = sample pair)
  for (int i=0;i<frames*2;i++)
  {
    float xn_cur = *xn++;

    // Waveshaping algorithm // 
    // DRY + WET
    wet_signal = (wet * ((xn_cur * ((distamt * 10.0f) + 1.f)) - xn_cur));
    base_main = xn_cur + wet_signal;
    *yn++ = waveshape(base_main);
  }
}

// Param Controls //
void MODFX_PARAM(uint8_t index, int32_t value)
{
  //Convert fixed-point q31 format to float
  const float valf = q31_to_f32(value);
  switch (index)
  {
    case 0:
      distamt = valf;
      break;
    case 1:
      wet = valf;
      break;
    default:
      break;
  }
}