#ifndef __32FFT_H__
#define __32FFT_H__

#include <math.h>
#include <complex>
//#include <ap_fixed.h>

using namespace std;
#define N 32

typedef float data_t;
//typedef ap_fixed<16,8> data_t;
typedef complex<data_t> data_comp;


#include "32fftvalues.h"
void FFT(data_comp data_IN[N], data_comp data_OUT[N]);

#endif
