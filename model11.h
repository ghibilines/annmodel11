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
        void correcttop(double b, double c) {
                weighttop -= 0.01*((b-c)/(c))*(valuetop/valuelow)*(weighttop/fabs(weighttop));
        }
        void correctlow(double b, double c) {
                weightlow -= 0.01*((b-c)/(c))*(valuelow/valuetop)*(weightlow/fabs(weightlow));
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
