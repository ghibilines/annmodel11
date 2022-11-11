#ifndef MODEL11_H
#define MODEL11_H

#include <iostream>
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
        void connect(node *lt, node *ll, node *r)       {
                lefttop = lt;
                leftlow = ll;
                right = r;
        }
	double applytop() {
                if (lefttop == NULL)	{
			valuetop = 0;
		}
		else	{
			valuetop = lefttop->value*weighttop;
		}
		return valuetop;
        }
	double applylow() {
		if (leftlow == NULL)	{
			valuelow = 0;
		}
		else	{
			valuelow = leftlow->value*weightlow;
		}
		return valuelow;
	}
	void correcttop(node b, double c) {
        	weighttop -= 0.01*(( b.value-c)/(c))*(valuetop/valuelow)*(weighttop/fabs(weighttop));
	}
	void correctlow(node b, double c) {
                weightlow -= 0.01*(( b.value-c)/(c))*(valuelow/valuetop)*(weightlow/fabs(weightlow));
        }
	void assigninit(double a, double b)       {
                weighttop = a; 
		weightlow = b;
        }
};
void printmodel(node *p, int a);
void runmodel(node *p, int a, int operand);
void correctonce(node *p,node *ex, double expect, int a, int loop);
int roundn(double a);
void predictmodel(node *ex, int entry, double *values, int nodes, int operand);


void printmodel(node *p, int a)
{
        int i;
        printf("\nmodel:\n");
        for(i=0;i<a;i++)        {
                printf("node%d\tweighttop:%f, weightlow: %f\n",i, (p+i)->weighttop, (p+i)->weightlow);
        }
        return;


}

void runmodel(node *p, int a, int operand)
{
	switch (operand)	{
		case '+':
			for(;a>=0;a--)	{
				(p+a)->value = (p+a)->applytop() + (p+a)->applylow();
			}
			break;
		case '*':
			for(;a>=0;a--)	{
				(p+a)->value = (p+a)->applytop() * (p+a)->applylow();
			}
			break;
		default:
			printf("runmodel:ERROR; unrecognised operand\n");
			break;
	}
	return;
}

void correctonce(node *p,node *ex, double expect, int a, int loop)
{
	int i;
	(p)->correcttop(*ex,expect);
	(p)->correctlow(*ex,expect);
	if (loop>0)	{
		for(i=1;i<=a;i++)	{
			(p+i)->correcttop(*ex,expect);
			(p+i)->correctlow(*ex,expect);
		}
	}
	return;
}

int roundn(double a)
{
        int b;
        if (a-((int) a) >= 0.5) {
                b = 1;
        }
        else    {
                b = 0;
        }
        return ((int) a + b);
}

void predictmodel(node *ex, int entry, double *values, int nodes, int operand)
{
        int i;
        for(i=0;i<entry;i++)    {
                (ex+nodes-1-i)->value = *(values+i);
        }
        runmodel(ex, nodes-entry-1, operand);
        return;
}

#endif
