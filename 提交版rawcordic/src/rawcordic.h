#include <ap_fixed.h>

#define WA 17
#define FA 14
#define WS 16
#define FS 14
#define NUM_ITERATIONS 15


typedef ap_fixed<WA, WA-FA> THETA_TYPE;
typedef ap_fixed<WS, WS-FS> COS_SIN_TYPE;
typedef ap_uint<2> FLAG_TYPE;
const THETA_TYPE PI = 3.1415926;
void rawcordic(THETA_TYPE theta, COS_SIN_TYPE &s, COS_SIN_TYPE &c);