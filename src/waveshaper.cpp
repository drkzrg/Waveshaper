#include <usermodfx.h>
#include "fx_api.h"
#define 	M_PI   3.141592653589793f

static float distamt = 0.5f;

float __fast_inline waveshape(float in) {
    return 1.5f * in - 0.5f * in *in * in;
}

void MODFX_INIT(uint32_t platform, uint32_t api)
{
    distamt = 1.f;
}

void MODFX_PROCESS(const float *xn, float *yn,
                   const float *sub_xn, float *sub_yn,
                   uint32_t frames)
{
  // Effect processing loop
 
 float base_main;
 const float *main_yn_e = yn + 2 * frames;

// For double frames (AKA samples cause each frame = sample pair)
 for (int i=0;i<frames*2;i++)
  {
    // Waveshaping algorithm
    base_main = *(xn++) * ((distamt * 10.0f) + 1.f);
    *yn++ = waveshape(base_main);
  }
}

void MODFX_PARAM(uint8_t index, int32_t value)
{
  //Convert fixed-point q31 format to float
  const float valf = q31_to_f32(value);
  switch (index)
  {
    case 0:
      distamt = valf;
    break;
  //timeAssign a value to rate when turning the knob
  case 1:
    break;
  default:
    break;
  }
}