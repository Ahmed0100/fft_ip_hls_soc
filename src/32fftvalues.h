#ifndef __32FFTVALUES_H__
#define __32FFTVALUES_H__
#define FFT_LENGTH 32


const int rev_32[]={

0,16,8,24,4,20,12,28,2,18,10,26,6,22,14,30,1,17,9,25,5,21,13,29,3,19,11,27,7,23,15,31,

};


const float scale = 1.0;

const data_comp W[FFT_LENGTH/2] = {

	data_comp(cos(2 * M_PI *0/ FFT_LENGTH) * scale,-sin(2 * M_PI *0/ FFT_LENGTH) * scale),
    data_comp(cos(2 * M_PI *1/ FFT_LENGTH) * scale,-sin(2 * M_PI *1/ FFT_LENGTH) * scale),
    data_comp(cos(2 * M_PI *2/ FFT_LENGTH) * scale,-sin(2 * M_PI *2/ FFT_LENGTH) * scale),
    data_comp(cos(2 * M_PI *3/ FFT_LENGTH) * scale,-sin(2 * M_PI *3/ FFT_LENGTH) * scale),
    data_comp(cos(2 * M_PI *4/ FFT_LENGTH) * scale,-sin(2 * M_PI *4/ FFT_LENGTH) * scale),
    data_comp(cos(2 * M_PI *5/ FFT_LENGTH) * scale,-sin(2 * M_PI *5/ FFT_LENGTH) * scale),
    data_comp(cos(2 * M_PI *6/ FFT_LENGTH) * scale,-sin(2 * M_PI *6/ FFT_LENGTH) * scale),
    data_comp(cos(2 * M_PI *7/ FFT_LENGTH) * scale,-sin(2 * M_PI *7/ FFT_LENGTH) * scale),
    data_comp(cos(2 * M_PI *8/ FFT_LENGTH) * scale,-sin(2 * M_PI *8/ FFT_LENGTH) * scale),
    data_comp(cos(2 * M_PI *9/ FFT_LENGTH) * scale,-sin(2 * M_PI *9/ FFT_LENGTH) * scale),
    data_comp(cos(2 * M_PI *10/ FFT_LENGTH) * scale,-sin(2 * M_PI *10/ FFT_LENGTH) * scale),
    data_comp(cos(2 * M_PI *11/ FFT_LENGTH) * scale,-sin(2 * M_PI *11/ FFT_LENGTH) * scale),
    data_comp(cos(2 * M_PI *12/ FFT_LENGTH) * scale,-sin(2 * M_PI *12/ FFT_LENGTH) * scale),
    data_comp(cos(2 * M_PI *13/ FFT_LENGTH) * scale,-sin(2 * M_PI *13/ FFT_LENGTH) * scale),
    data_comp(cos(2 * M_PI *14/ FFT_LENGTH) * scale,-sin(2 * M_PI *14/ FFT_LENGTH) * scale),
    data_comp(cos(2 * M_PI *15/ FFT_LENGTH) * scale,-sin(2 * M_PI *15/ FFT_LENGTH) * scale),

};

#endif


