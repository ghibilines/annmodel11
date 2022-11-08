#include <iostream>
#include <array>
#include <stdio.h>
#include <math.h>
#define NULL ((void *) 0)
struct node     {
        node *lefttop;
	node *leftlow;
        node *right;
        double value;
	double valuetop;
	double valuelow;
        double weighttop;
	double weightlow;
        void connect(node *lt, node *ll, node *r)	{
		lefttop = lt;
		leftlow = ll;
		right = r;
	}
	void applytop() {
                valuetop =  lefttop->value*weighttop;
        }
	void applylow() {
		valuelow = leftlow->value*weightlow;
	}
	void correcttop(node b, double c) {
        	weighttop -= 0.01*((b.value-c)/(c))*(valuetop/valuelow)*(weighttop/fabs(weighttop));
	}
	void correctlow(node b, double c) {
                weightlow -= 0.01*((b.value-c)/(c))*(valuelow/valuetop)*(weightlow/fabs(weightlow));
        }
	void assigninit(double a)	{
		weighttop = a; 
		weightlow = a;
	}

};
void printmodel(node *p, int a);

int main()
{
	double arr0[18] =  {2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 3.6};
       	double arr1[18] =  {1.0, 1.0, 3.0, 2.0, 5.0, 2.0, 6.0, 4.0, 1.0,  2.0, 1.0, 4.0, 2.0, 6.0, 3.0, 7.0, 5.0 , 1.2};
	node entry1,entry2,mid1,mid2,exit2,exit1;
	int len = 18;
	double margin = 0.04;
	//visualization
	//
	//entry1 - mid1 \
	//	 X	 exit2 - exit1
	//entry2 - mid2 /
	//setup
	entry1.connect(NULL, NULL, &mid1);
	entry2.connect(NULL, NULL, &mid2);
        mid1.connect(&entry1, &entry2, &exit2);
	mid2.connect(&entry2, &entry1, &exit2);
        exit2.connect(&mid1, &mid2, &exit1);
	exit1.connect(&exit2, &exit2, NULL);
	//assign values to a,b and weights
	mid1.assigninit(0.5);
	mid2.assigninit(0.5);
	exit2.assigninit(0.5);
	exit1.assigninit(0.5);
	//test values
	int i, j=0, k;
	double expect;
	//calculate
	for(i=0;i<len;i++)	{
		entry1.value = arr0[i];
	        entry2.value = arr1[i];
		expect = sqrt(arr0[i]*arr0[i]+arr1[i]*arr1[i]);
		exit2.value = 0.0;
		for(j=0;((1-margin)*expect > exit2.value) || (exit2.value > (1+margin)*expect);j++)	{
			mid1.applytop();
			mid1.applylow();
			mid1.value = (mid1.valuetop + mid1.valuelow);
			mid2.applytop();
			mid2.applylow();
			mid2.value = (mid2.valuetop + mid2.valuelow);
			exit2.applytop();
			exit2.applylow();
			exit2.value = (exit2.valuetop + exit2.valuelow);
			//correction
			exit2.correcttop(exit2,expect);
			exit2.correctlow(exit2,expect);
			if (j>0)	{
				mid1.correcttop(exit2,expect);
				mid1.correctlow(exit2,expect);
				mid2.correcttop(exit2,expect);
				mid2.correctlow(exit2,expect);
			}
			if (j==0)	{
				printf("GUESS:\t%d\t%f,%f\t%f\t%f\t%f margin\n", j,arr0[i],arr1[i], expect, exit2.value, ((exit2.value-expect)/expect));
			}
		}
		printf("DONE:\t%d\t%f,%f\t%f\t%f\n", j,arr0[i],arr1[i], expect, exit2.value);
	}
	node model[3];
	model[0] = exit2, model[1] = mid1, model[2] = mid2;
	printmodel(&model[0], 3);
}

void printmodel(node *p, int a)
{
	int i;
	printf("\nmodel:\n");
	for(i=0;i<a;i++)	{
		printf("node%d\tweighttop:%f, weightlow: %f\n",i, (p+i)->weighttop, (p+i)->weightlow);
	}
	return;


}
