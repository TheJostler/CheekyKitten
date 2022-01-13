#include "algo.h"

/*
 * This is an optimisation test running the qc algorithm using bit manipulation rather than Arithmatic 
 */

//IXI
int x_ixi(int x, int y) {
    x = (0xf0 & y)^(x >> 4);
	return x;
	}
int y_ixi(int x, int y) {
    y = (y&0xf<<4)^(x&0xf);
	return y;
}
//XX
int x_xx(int x, int y) {
    x = (x&0xf<<4)^(y&0xf);
	return x;
	}
int y_xx(int x, int y) {
    y = (0xf0 & x)^(y >> 4);
	return y;
}