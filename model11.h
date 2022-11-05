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
