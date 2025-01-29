#include "algo.h"

//IXI
int x_ixi(int x, int y) {
    return (y & 0xf0)^(x >> 4);
}
int y_ixi(int x, int y) {
    return ((y & 0xf) << 4)^(x & 0xf);
}
//XX
int x_xx(int x, int y) {
    return ((x & 0xf) << 4)^(y & 0xf);
}
int y_xx(int x, int y) {
    return (x & 0xf0)^(y >> 4);
}
