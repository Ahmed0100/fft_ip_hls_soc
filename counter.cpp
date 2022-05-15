int counter()
{
#pragma HLS INTERFACE s_axilite port=return
	static int ctr=0;
	ctr= ctr+1;
	return ctr;
}
