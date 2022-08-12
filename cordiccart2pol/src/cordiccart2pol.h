#ifndef CORDICCART2POL_H
#define CORDICCART2POL_H
#include "ap_fixed.h"

#define NO_ITER 16

typedef int   coef_t;
typedef ap_fixed<32,2,AP_RND, AP_SAT> data_t;
typedef float acc_t;

void cordiccart2pol(data_t x, data_t y, data_t * r,  acc_t * theta);
//theta type is acc_t no data_t because when test it will minus float and error

#endif
