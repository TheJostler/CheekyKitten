#include "algo.h"

/*
 * This is an optimisation test running the qc algorithm using bit manipulation rather than Arithmatic 
 */

//IXI
int x_ixi(int x, int y) {
    return (0xf0 & y)^((x & 0xf0) >> 4);
	}
int y_ixi(int x, int y) {
    return (y & 0xf << 4)^(x & 0xf);
}
//XX
int x_xx(int x, int y) {
    return (x & 0xf << 4)^(y & 0xf);
	}
int y_xx(int x, int y) {
    return (0xf0 & x)^(y >> 4);
}