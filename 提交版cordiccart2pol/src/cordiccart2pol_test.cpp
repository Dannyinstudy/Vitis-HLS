#include "cordiccart2pol.h"
#include <math.h>
#include <stdio.h>



struct Rmse
{
	int num_sq;
	float sum_sq;
	float error;

	Rmse(){ num_sq = 0; sum_sq = 0; error = 0; }

	float add_value(float d_n)
	{
		num_sq++;
		sum_sq += (d_n*d_n);
		error = sqrtf(sum_sq / num_sq);
		return error;
	}

};


Rmse rmse_theta;
Rmse rmse_r;


void run_test(data_t x, data_t y, double golden_theta, double golden_r,	data_t r,acc_t theta)
{
	//data_t r;
	//data_t theta;

	cordiccart2pol(x, y, &r,  &theta);

	rmse_theta.add_value((float)theta - golden_theta);
	rmse_r.add_value((float)r - golden_r);
}


int main()
{
	data_t x;
	data_t y;
	data_t r,r1,r2,r3;
	acc_t theta,theta1,theta2,theta3;


	printf("---Testing results----------------------------------\n");

	// Test1
	run_test(0.8147, 0.1269, 0.154521173805634, 0.824523923242982,r,theta);
	printf("   r           theta\n");
	printf("%0.15f %0.15f\n", (float)r, (float)theta);

	// Test 2
	run_test(0.6323, -0.2785, -0.414888412375609, 0.690916449362729,r1,theta1);
	printf("   r           theta\n");
	printf("%0.15f %0.15f\n", (float)r1, (float)theta1);
	// Test 3
	run_test(-0.5469, -0.9575, -2.089751217098013, 1.102681214132172,r2,theta2);
	printf("   r           theta\n");
	printf("%0.15f %0.15f\n", (float)r2, (float)theta2);
	// Test 4
	run_test(-0.4854, 0.7003, 2.176897679895152, 0.852075847562880,r3,theta3);
	printf("   r           theta\n");
	printf("%0.15f %0.15f\n", (float)r3, (float)theta3);

	printf("---RMS error----------------------------------\n");
	printf("----------------------------------------------\n");
	printf("   RMSE(R)           RMSE(Theta)\n");
	printf("%0.15f %0.15f\n", rmse_r.error, rmse_theta.error);
	printf("----------------------------------------------\n");


	float error_threshold = 0.001;

    int success = (rmse_r.error < error_threshold) && (rmse_theta.error < error_threshold);

    if (success) return 0;
    else return 1;

}
