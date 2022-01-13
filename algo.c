#include "algo.h"

/*
 * This is an optimisation test running the qc algorithm using Arithmatic rather than bit manipulation
 */

//IXI
int x_ixi(int x, int y, int d) {
    return (y - d) + (x / 0x10);
	}
int y_ixi(int b, int d) {
    return (d * 0x10) + b;
}

//XX
int x_xx(int b, int d) {
	return b * 0x10 + d;
	}
int y_xx(int x, int y, int b) {
	return (x - b) + (y / 0x10);
}

int main(){
	int x = x_ixi(64);
	int y = y_ixi(65);
	printf("x: %x, y: %x", x, y);
}