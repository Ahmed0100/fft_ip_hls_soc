/*Source: Numerical Recipe In C
 * Modified by IIT Madras
 * The following code computes 32point FFT
 * The bit reversal positions are precomputed and stored in the header files.
 * The Twiddle Factor is decomposed into following form:
 * exp(ia + ib) = exp(ia)*exp(ib) = exp(ia) + Z*exp(ia)
 * Where Z = exp(ib) - 1 = -(1 - cos(b)) + isin(b) = -2*sin^2(b/2) + isin(b)
 * Z is precomputed and stored in header file.
 * */

#include "32fft.h"
#include "32fftvalues.h"

using namespace std;

void bitreverse(data_comp data_IN[N], data_comp data_OUT[N]) {   //do 32point bit reversal
	bitreversal_label1: for (int i=0;i<N;i++) {
		int index = rev_32[i];
		data_OUT[i] = data_IN[index];
	}
}

void FFT0(int FFT_stage,int pass_check,int index_shift,int pass_shift,data_comp data_IN[N], data_comp data_OUT[N]){

	int butterfly_span=0,butterfly_pass=0;
	FFT_label1: for (int i = 0; i < N/2; i++) {
		int index = butterfly_span << index_shift;
		int Ulimit = butterfly_span + (butterfly_pass<<pass_shift);
		int Llimit = Ulimit + FFT_stage;
		data_comp Product = W[index] * data_IN[Llimit];//calculate the product
		data_OUT[Llimit] = data_IN[Ulimit]-Product;
		data_OUT[Ulimit] = data_IN[Ulimit]+Product;
		if (butterfly_span<FFT_stage-1){
			butterfly_span++;
		} else if (butterfly_pass<pass_check-1) {
			butterfly_span = 0;	butterfly_pass++;
		} else {
			butterfly_span = 0;	butterfly_pass=0;
		}
	}
}


void FFT(data_comp data_IN[N], data_comp data_OUT[N]){

	static data_comp data_OUT0[N];
	static data_comp data_OUT1[N];
	static data_comp data_OUT2[N];
	static data_comp data_OUT3[N];
	static data_comp data_OUT4[N];

	bitreverse(data_IN, data_OUT0);  //calculate bitreverse order

	FFT0(1,16,4,1,data_OUT0,data_OUT1); //calculate the FFT
	FFT0(2,8,3,2,data_OUT1,data_OUT2);
	FFT0(4,4,2,3,data_OUT2,data_OUT3);
	FFT0(8,2,1,4,data_OUT3,data_OUT4);
	FFT0(16,1,0,5,data_OUT4,data_OUT);

}
