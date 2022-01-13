#include "algo.h"
#include <stdio.h>

/*
 * This is an optimisation test running the qc algorithm using bit manipulation rather than Arithmatic 
 */

//IXI
int x_ixi(int x, int y) {
    return (0xf0 & y)|((x & 0xf0) >> 4);
	}
int y_ixi(int x, int y) {
    return (y & 0x0f << 4)|(x & 0x0f);
}
//XX
int x_xx(int x, int y) {
    return (x & 0xf << 4)^(y & 0xf);
	}
int y_xx(int x, int y) {
    return (0xf0 & x)^(y >> 4);
}

int main(){
	int x = x_ixi(64, 65);
	int y = y_ixi(64, 65);
	printf("Bellow should read x: 66, y:54")
	printf("x: %x, y: %x", x, y);
}