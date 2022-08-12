
#include "rawcordic.h"


THETA_TYPE cordic_phase[NUM_ITERATIONS] = {
		0.7853981, 0.4636476, 0.2449787, 0.1243549, 0.0624188,
			0.0312398, 0.0156237, 0.0078123, 0.0039062, 0.0019531,
			0.0009765, 0.0004883, 0.0002441, 0.0001221, 0.0000610    
};

void rawcordic(THETA_TYPE theta, COS_SIN_TYPE &s, COS_SIN_TYPE &c) 
{
#pragma HLS INTERFACE s_axilite port=c
#pragma HLS INTERFACE s_axilite port=s
#pragma HLS INTERFACE s_axilite port=theta

	FLAG_TYPE flag;
	if(theta > PI/2)
		{
		theta = PI - theta;
			flag = 1;
		}
		else if(theta < -PI/2)
		{
			theta = -PI - theta;
			flag = 2;
		}
		else
		{
			theta = theta;
			flag = 0;
		}
    // Set the initial vector that we will rotate 
    COS_SIN_TYPE current_cos = 0.607252935;
    COS_SIN_TYPE current_sin = 0.0;
    
    // This loop iteratively rotates the initial vector to find the
    // sine and cosine values corresponding to the input theta angle 
    for (int j = 0; j < NUM_ITERATIONS; j++) {
#pragma HLS UNROLL
#pragma HLS PIPELINE II=1

        // Multiply previous iteration by 2^(-j). This is equivalent to
        // a right shift by j on a fixed-point number.
        COS_SIN_TYPE cos_shift = current_cos >> j; 
        COS_SIN_TYPE sin_shift = current_sin >> j;
        
        // Determine if we are rotating by a positive or negative angle 
        if(theta >= 0) { 
            // Perform the rotation 
            current_cos = current_cos - sin_shift;
            current_sin = current_sin + cos_shift;
            
            // Determine the new theta
            theta = theta - cordic_phase[j];
        } else { 
            // Perform the rotation 
            current_cos = current_cos + sin_shift; 
            current_sin = current_sin - cos_shift;
            
            // Determine the new theta 
            theta = theta + cordic_phase[j];
        }
    }    
    // Set the sine and cosine values
	/*switch(int(flag))
	{
	case 1: {s = current_sin; c = -current_cos; }
	case 2: {s = current_sin; c = -current_cos; }
	default: {s = current_sin; c = current_cos; }
	}*/
	if(flag == 1)
		{
		s = current_sin;
		c = -current_cos;
		}
		else if(flag == 2)
		{
			s = current_sin;
			c = -current_cos;
		}
		else
		{
			s = current_sin;
			c = current_cos;
		}
}
