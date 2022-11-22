#include <iostream>
#include <stdio.h>
#include <math.h>
#include "model11.h"
#define NULL ((void *) 0)

main()
{
	double x[100], y[100], res[100], r2[100];
	int i,j,k,l, len=100;
	double weight[4], rsq,temp,ybar,a,b,c,margin =0.04, mrg;

	node nd[5];
	nd[0].connect(&nd[2],&nd[1],NULL);
        nd[1].connect(&nd[3],&nd[4],&nd[0]);
        nd[2].connect(NULL, &nd[3], NULL);
        nd[3].connect(NULL,NULL,&nd[1]);
        nd[4].connect(NULL,NULL,&nd[1]);
        nd[0].assigninit(0.5,0.5);
        nd[1].assigninit(0.5,0.5);
        nd[4].value=1.0;
	for(i=0;i<len;i++)      {
                x[i] = i+1;
                y[i] = 7*x[i]*x[i] + 6*x[i] + 5*sqrt(x[i]) - 30;
                temp += y[i];
        }
        ybar = temp/len;
	r2[0] = -1000;
	for(i=1;i<len;i++)	{
		weight[0] = nd[0].weighttop;
        	weight[1] = nd[0].weightlow;
               	weight[2] = nd[1].weighttop;
               	weight[3] = nd[1].weightlow;
		//pick random number between 0 and 99
		j = (rand() % 99);
		//init polinomial node
		nd[3].value = x[j];
		nd[2].weightlow = x[j];
		//run model
		runmodel(&nd[0],2,'+');
		//biases towards mean, if y[j] = ybar mrg=0.01-> more training
		mrg = margin -0.02*fabs(y[j]/ybar);
		//correct until margin is satisfied
		for(k=0;nd[0].value<(1-mrg)*y[j] || nd[0].value>(1+mrg)*y[j];k++)	{
			if (k==0) printf("initial guess:\t%f\t%f\t%d\n",nd[0].value,y[j],k);
			runmodel(&nd[0],2,'+');
			correctonce(&nd[0],&nd[0],y[j],1,1,j);
		}
		printf("final guess:\t%f\t%f\t%d,number%d\n",nd[0].value,y[j],k,j);
		//calculate res
		for(l=0;l<len;l++)      {
        	        nd[3].value = x[l];
                	nd[2].weightlow = x[l];
                	runmodel(&nd[0],2,'+');
                	res[l] = nd[0].value;

	               	a += (res[l]-y[l])*(res[l]-y[l]);
	               	b += (ybar - y[l])*(ybar - y[l]);
	       	}
		//calculate r2
		r2[i] = 1 - (a/b);
		printf("r^2:i:%d,%f,i:%d,%f,\n",i-1,r2[i-1],i,r2[i]);
		if (r2[i]<r2[i-1]) break;
	}
	k=i;
	printf("DONE\n");
	//recover weights
	nd[0].weighttop = weight[0];
	nd[0].weightlow = weight[1];
	nd[1].weighttop = weight[2];
	nd[1].weightlow = weight[3];
	//fin
	printmodel(&nd[0],3);
	for(i=0;i<len;i++)	{
		nd[3].value = x[i];
		nd[2].weightlow = x[i];
		runmodel(&nd[0],2,'+');
		res[i] = nd[0].value;
		
		a += (res[i]-y[i])*(res[i]-y[i]);
                b += (ybar - y[i])*(ybar - y[i]);
	}
	for(i=0;i<len;i++)	{
		printf("expected:%f\tmodel:%f\n",y[i],res[i]);
	}
	rsq = 1 - (a/b);
	printf("r^2:%f, %f\n",rsq, r2[k-1]);
}
