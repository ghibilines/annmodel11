#include <iostream>
#include <array>
#include <stdio.h>
#include <math.h>
struct node     {
        node *lefttop;
	node *leftlow;
        node *right;
        double value;
	double valuetop;
	double valuelow;
        double weighttop;
	double weightlow;
        double applytop() {
                return lefttop->value*weighttop;
        }
	double applylow() {
		return leftlow->value*weightlow;
	}
};

int main()
{
	//think of good training data		5			9			14			19
	double arr0[18] =  {2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 3.6};
       	double arr1[18] =  {1.0, 1.0, 3.0, 2.0, 5.0, 2.0, 6.0, 4.0, 1.0,  2.0, 1.0, 4.0, 2.0, 6.0, 3.0, 7.0, 5.0 , 1.2};
	int len = 18;
	double margin = 0.04;
	//visualization
	//
	//entry1 - mid1 \
	//	 X	 exit - exit1
	//entry2 - mid2 /
	node entry1,entry2,mid1,mid2,exit,exit1;
	//setup
	entry1.right = &mid1;
        entry2.right = &mid2;
        mid1.right = &exit;
        mid2.right = &exit;
        mid1.lefttop = &entry1;
        mid1.leftlow = &entry2;
        mid2.lefttop = &entry2;
        mid2.leftlow = &entry1;
        exit.lefttop = &mid1;
        exit.leftlow = &mid2;
	exit.right = &exit1;
	exit1.lefttop = &exit;
	exit1.leftlow = &exit;
	//assign values to a,b and weights
	mid1.weighttop = 0.5;
	mid1.weightlow = 0.5;
	mid2.weighttop = 0.5;
	mid2.weightlow = 0.5;
	exit.weighttop = 0.5;
	exit.weightlow = 0.5;
	exit1.weighttop = 0.5;
	exit1.weightlow = 0.5;
	//test values
	int i, j=0, k;
	double expect;
	//calculate
	for(i=0;i<len;i++)	{
		entry1.value = arr0[i];
	        entry2.value = arr1[i];
		expect = sqrt(arr0[i]*arr0[i]+arr1[i]*arr1[i]);
		exit.value = 0.0;
		for(j=0;((1-margin)*expect > exit.value) || (exit.value > (1+margin)*expect);j++)	{
			mid1.valuetop = mid1.applytop();
			mid1.valuelow = mid1.applylow();
			mid1.value = (mid1.valuetop + mid1.valuelow);
			mid2.valuetop = mid2.applytop();
			mid2.valuelow = mid2.applylow();
			mid2.value = (mid2.valuetop + mid2.valuelow);
			exit.valuetop = exit.applytop();
			exit.valuelow = exit.applylow();
			exit.value = (exit.valuetop + exit.valuelow);
			//printf("%d\t%f\t%f\n", j, expect, exit.value);
			//correction
			exit.weighttop -= 0.01*((exit.value-expect)/(expect))*(exit.valuetop/exit.valuelow)*(exit.weighttop/fabs(exit.weighttop));
			exit.weightlow -= 0.01*((exit.value-expect)/(expect))*(exit.valuelow/exit.valuetop)*(exit.weightlow/fabs(exit.weightlow));
			if (j>0)	{
				mid1.weighttop -= 0.01*((exit.value-expect)/(expect))*(mid1.valuetop/mid1.valuelow)*(mid1.weighttop/fabs(mid1.weighttop));
				mid1.weightlow -= 0.01*((exit.value-expect)/(expect))*(mid1.valuelow/mid1.valuetop)*(mid1.weightlow/fabs(mid1.weightlow));
				mid2.weighttop -= 0.01*((exit.value-expect)/(expect))*(mid2.valuetop/mid2.valuelow)*(mid2.weighttop/fabs(mid2.weighttop));
                                mid2.weightlow -= 0.01*((exit.value-expect)/(expect))*(mid2.valuelow/mid2.valuetop)*(mid2.weightlow/fabs(mid2.weightlow));
			}
			if (j==0)	{
				printf("GUESS:\t%d\t%f,%f\t%f\t%f\t%f margin\n", j,arr0[i],arr1[i], expect, exit.value, ((exit.value-expect)/expect));
			}
		}
		printf("DONE:\t%d\t%f,%f\t%f\t%f\n", j,arr0[i],arr1[i], expect, exit.value);
	}
	printf("\nmodel:\n");
	printf("exit\tweighttop:%f, weightlow: %f\n", exit.weighttop, exit.weightlow);
	printf("mid1\tweighttop:%f, weightlow: %f\n", mid1.weighttop, mid1.weightlow);
	printf("mid2\tweighttop:%f, weightlow: %f\n", mid2.weighttop, mid2.weightlow);


}
