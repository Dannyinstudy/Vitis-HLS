#include "rawcordic.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define RAND (rand()%181) - (rand()%181)
#define Test_round 100
#define STANDARD 0.1
int main()
{
	srand(RAND_MAX);
	int i;
	for(i=0; i<Test_round; i++)
	{
		THETA_TYPE data_in = (THETA_TYPE)(RAND * 3.1415926/180);
		COS_SIN_TYPE sin_out;
		COS_SIN_TYPE cos_out;
		COS_SIN_TYPE sin_ref;
		COS_SIN_TYPE cos_ref;
		sin_ref = (COS_SIN_TYPE)sin((float)data_in);
		cos_ref = (COS_SIN_TYPE)cos((float)data_in);
		rawcordic(data_in, sin_out, cos_out);

		if(abs((float)(sin_ref - sin_out))>STANDARD || abs((float)(cos_ref - cos_out))>STANDARD)
		{
			cout<<sin_out<<sin_ref<<cos_out<<cos_ref<<endl;
			cout<<"Error: error is too big"<<endl;
			return(-1);
		}
		cout << setfill(' ') << setw(18) << right << sin_ref;
		cout << setfill(' ') << setw(18) << right << sin_out;
		cout << setfill(' ') << setw(18) << right << cos_ref;
		cout << setfill(' ') << setw(18) << right << cos_out;
		cout <<endl;
	}
	cout<<"Success: C - verification pass"<<endl;
	return(0);
}
