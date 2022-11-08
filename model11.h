#ifndef MODEL11_H
#define MODEL11_H

#include <iostream>
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
        void connect(node *lt, node *ll, node *r)       {
                lefttop = lt;
                leftlow = ll;
                right = r;
        }
        void applytop() {
                valuetop = lefttop->value*weighttop;
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
        void assigninit(double a)       {
                weighttop = a;
                weightlow = a;
        }
};
void printmodel(node *p, int a);

void printmodel(node *p, int a)
{
        int i;
        printf("\nmodel:\n");
        for(i=0;i<a;i++)        {
                printf("node%d\tweighttop:%f, weightlow: %f\n",i, (p+i)->weighttop, (p+i)->weightlow);
        }
        return;


}

#endif
