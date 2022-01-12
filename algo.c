#include "algo.h"

/*
 * This is an optimisation test running the qc algorithm using Arithmatic rather than bit manipulation
 */

//IXI
int x_ixi(int x, int y, int d) {
    x = (y - d) + (x / 0x10);
	return x;
	}
int y_ixi(int b, int d) {
    int y = (d * 0x10) + b;
	return y;
}

//XX
int x_xx(int b, int d) {
	int x = b * 0x10 + d;
	return x;
	}
int y_xx(int x, int y, int b) {
	y = (x - b) + (y / 0x10);
	return y;
}
