#include <iostream>
#include <array>
#include <stdio.h>
#include <math.h>
#include "model11.h"
#define NULL ((void *) 0)

int main()
{
	double arr0[18] =  {2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 3.6};
       	double arr1[18] =  {1.0, 1.0, 3.0, 2.0, 5.0, 2.0, 6.0, 4.0, 1.0,  2.0, 1.0, 4.0, 2.0, 6.0, 3.0, 7.0, 5.0 , 1.2};
	//node entry1,entry2,mid1,mid2,exit2,exit1;
	node nd[6];
	int len = 18;
	double margin = 0.04;
	//visualization
	//
	//nd[4] - nd[2] \
	//  	X  	 nd[1] - nd[0]
	//nd[5] - nd[3] /
	//
	//setup
	nd[4].connect(NULL,NULL,&nd[2]);
	nd[5].connect(NULL,NULL,&nd[3]);
	nd[2].connect(&nd[4],&nd[5],&nd[1]);
	nd[3].connect(&nd[4],&nd[5],&nd[1]);
	nd[1].connect(&nd[2],&nd[3],&nd[0]);
	nd[0].connect(&nd[1],NULL,NULL);
	//assign values to a,b and weights
	nd[2].assigninit(0.5,0.5);
	nd[3].assigninit(0.5,0.5);
	nd[1].assigninit(0.5,0.5);
	nd[0].assigninit(0.5,0.5);
	printmodel(&nd[1], 3);
	//test values
	int i, j=0, k;
	double expect;
	//calculate
	for(i=0;i<len;i++)	{
		nd[4].value = arr0[i];
	        nd[5].value = arr1[i];
		expect = sqrt(arr0[i]*arr0[i]+arr1[i]*arr1[i]);
		nd[1].value = 0.0;
		for(j=0;((1-margin)*expect > nd[1].value) || (nd[1].value > (1+margin)*expect);j++)	{
			//running model
			runmodel(&nd[1],2,'+');
			//correction
			correctonce(&nd[1],&nd[1],expect,1.0,2,j);
			//print initial guess
			if (j==0)	{
				printf("GUESS:\t%d\t%f,%f\t%f\t%f\t%f margin\n", j,arr0[i],arr1[i], expect, nd[1].value, ((nd[1].value-expect)/expect));
			}
		}
		printf("DONE:\t%d\t%f,%f\t%f\t%f\n", j,arr0[i],arr1[i], expect, nd[1].value);
	}
	printmodel(&nd[1], 3);
	double test[2] = {1.0, 9.0};
	predictmodel(&nd[1], 2, &test[0], 5, '+');
	printf("test:\t%f\n",nd[1].value);
}
