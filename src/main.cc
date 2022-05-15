
/*
 * Test and profile FFT application in software
 */

#include "32fft.h"
#include "xcounter.h"
#include "xfft.h"

#define TOL 0.1
#define NORM(x) ((x) * (x)).real()

void writeToFFT(XFft * xfptr, float *dr,float * di)
{
	XFft_Write_data_IN_M_real_Words(xfptr,0,(int *)dr,N);
	XFft_Write_data_IN_M_imag_Words(xfptr,0,(int *)di,N);
}
void readFromFFT(XFft * xfptr, float *dr,float * di)
{
	XFft_Read_data_IN_M_real_Words(xfptr,0,(int *)dr,N);
	XFft_Read_data_IN_M_imag_Words(xfptr,0,(int *)di,N);
}
void dispf(float a) {
	int q = a;
	if (a < 0) q--;
	int r = (1000 * (a-q));
	xil_printf("%d.%03d", q, r);
}

int main()
{
	xil_printf("HI\n");
	XCounter xc;
	XCounter* xcptr = &xc;
	XFft xf;
	XFft * xfptr = &xf;

	float in_r[N],in_i[N];
	float out_r[N],out_i[N];
	data_comp data_in[N]={
#include "inp_cpp.txt"
	};
	data_comp data_out[N];
	data_comp data_exp[N]={
		#include "out_cpp.txt"
	};
	for(int i=0;i<N;i++)
	{
		in_r[i]=data_in[i].real();
		in_i[i]=data_in[i].imag();
	}

    XFft_Initialize(xfptr,0);
	XCounter_Initialize(xcptr, 0);
	XCounter_EnableAutoRestart(xcptr);
	XCounter_Start(xcptr);

	int swResult=0,hwResult=0;

	int t1 = XCounter_Get_return(xcptr);
	FFT(data_in,data_out);
	int t2 = XCounter_Get_return(xcptr);
	int tsw = t2-t1;
	for(int k=0;k<N;k++){
		if(NORM(data_exp[k]-data_out[k])>TOL)
		{
			xil_printf("SW-ERROR: [%d] \t ", k);
			dispf(data_out[k].real());
			xil_printf(" vs exp:\t ");
			dispf(data_exp[k].real());
			xil_printf("\r\n");
			swResult ++;
		}
	}
	t1 = XCounter_Get_return(xcptr);
	writeToFFT(xfptr,in_r,in_i);
	t2 = XCounter_Get_return(xcptr);
	XFft_Start(xfptr);
	int ctr=0;
	while(XFft_IsDone(xfptr) && (ctr<1000)) ctr++;
	if(ctr == 1000)
	{
		xil_printf("Time Out! Expect Errors \r\n");
	}

	int t3 = XCounter_Get_return(xcptr);
	readFromFFT(xfptr,out_r,out_i);
	int t4 = XCounter_Get_return(xcptr);
	for(int k=0;k<N;k++){
		if(NORM(data_exp[k]-data_out[k])>TOL)
		{
			xil_printf("HW-ERROR: [%d] \t ", k);
			dispf(out_r[k]);
			xil_printf(" vs exp:\t ");
			dispf(data_exp[k].real());
			xil_printf("\r\n");
			hwResult ++;
		}
	}

	if (swResult != 0)
		xil_printf("FAIL SW: %d errors\r\n", swResult);
	else if (hwResult != 0)
		xil_printf("FAIL HW: %d errors\r\n", hwResult);
	else
		xil_printf("PASS\r\n");


	xil_printf("SW FFT cycles: %d\r\n", tsw);
	xil_printf("Write to FFT cycles: %d\r\n", t2-t1);
	xil_printf("Compute FFT cycles: %d\r\n", t3-t2);
	xil_printf("Read from FFT cycles: %d\r\n", t4-t3);

	return swResult+hwResult;

}
