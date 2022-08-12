#include "cordiccart2pol.h"

	/*acc_t cordic_phase[NO_ITER] = {
	    45, 26.565, 14.036, 7.125,
	    3.576, 1.790, 0.895, 0.448,
		0.224,0.112,0.056,0.028,
		0.014,0.007,0.0035,0.0017
	};*/
	acc_t cordic_phase[NO_ITER] = {
		0.785385,0.463639838,0.244974557,0.12435291,
		0.062417764,0.03123931,0.015623467,0.00781221,
		0.003906165,0.00195309,0.000976546,0.000488273,
		0.000244137,0.000122068,0.0000610341,0.0000305171
	};
void cordiccart2pol(data_t x, data_t y, data_t * r,  acc_t * theta)
{
#pragma HLS INTERFACE s_axilite port=theta
#pragma HLS INTERFACE s_axilite port=r
#pragma HLS INTERFACE s_axilite port=x
#pragma HLS INTERFACE s_axilite port=y
	//write your code here
	data_t gain =0.60725;
	acc_t acc=0;
	data_t current_x;
	data_t current_y;

	//First rotate:90
	if(y>=0){
		current_x=y;
		current_y=-x;
		acc = acc + 1.570796;
	}else{
		current_x=-y;
	    current_y=x;
	    acc = acc - 1.570796;
	}


	//This loop iteratively rotates the initial vector to x axis
	for(coef_t j = 0; j < NO_ITER; j++){
#pragma HLS PIPELINE II=1
#pragma HLS UNROLL

	    data_t shift_x = current_x>>j;
	    data_t shift_y = current_y>>j;

	    if(current_y >= 0){
	        //Perform the rotation
	        current_x = current_x + shift_y;
	        current_y = current_y - shift_x;

	        //Determine the new theta
	        acc = acc + cordic_phase[j];
	    }else{
	    	//Perform the rotation
	    	current_x = current_x - shift_y;
	    	current_y = current_y + shift_x;

	    	//Determine the new theta
	    	acc = acc - cordic_phase[j];
	    }
	}
	//Set the final r and theta values
	*r = current_x * gain;
	*theta = acc;
	//*theta =(current_y>0) ? acc : (6.2831852+acc) ;

}
