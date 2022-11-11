#include <iostream>
#include <stdio.h>
#include <math.h>
#include "model11.h"
#define NULL ((void *) 0)

main()
{
	double col1[28] = {5.1,5.7,6.3,4.9,6.6,7.2,4.7,7.0,5.8,4.6,5.5,7.1,5.0,6.4,6.7,5.4,4.6,6.3,4.9,5.0,7.3,5.2,4.4,6.5,7.6,4.9,6.9,6.5};
	double col2[28] = {3.5,2.8,3.3,3.0,2.9, 3.6,3.2,3.2,2.7,3.1, 2.3,3.0,3.6,3.2,2.5, 3.9,3.4,3.3,2.5,3.4, 2.9,2.7,2.9,2.8,3.0, 3.1,3.1,3.0};
	double col3[28] = {1.4,4.5,6.0,1.4,4.6, 6.1,1.3,4.7,5.1,1.5, 4.0,5.9,1.4,4.5,5.8, 1.7,1.4,4.7,4.5,1.5, 6.3,3.9,1.4,4.6,6.6, 1.5,4.9,5.8};
	double col4[28] = {0.2,1.3,2.5,0.2,1.3, 2.5,0.2,1.4,1.9,0.2, 1.3,2.1,0.2,1.5,1.8, 0.4,0.3,1.6,1.7,0.2, 1.8,1.4,0.2,1.5,2.1, 0.1,1.5,2.2};
	double type[28] = {1.0,2.0,3.0,1.0,2.0, 3.0,1.0,2.0,3.0,1.0, 2.0,3.0,1.0,2.0,3.0, 1.0,1.0,2.0,3.0,1.0, 3.0,2.0,1.0,2.0,3.0, 1.0,2.0,3.0};
	int i,len=28;
	//for(i=0;scanf("%f,%f,%f,%f,%f\n",col1[i],col2[i],col3[i],col4[i],type[i]);i++)
	//{}
	//constants,variables and model layout
	//v1	 nd7 \
	//	      nd3 \
	//c1	 nd8 / 	   \
	//v2	 nd9 \ 	   nd1  \
	//	      nd4 /      \
	//c2	 nd10 /	          \
	//v3	 nd11 \	  	 nd0
	//	       nd5 \      /
	//c3	 nd12 /     \    /
	//v4	 nd13 \	    nd2 /
	//	       nd6 /
	//c4	 nd14 /
	//
	node nd[15];
	//first
	nd[14].connect(NULL,NULL,&nd[6]);
	nd[13].connect(NULL,NULL,&nd[6]);
	nd[12].connect(NULL,NULL,&nd[5]);
	nd[11].connect(NULL,NULL,&nd[5]);
	nd[10].connect(NULL,NULL,&nd[4]);
	nd[9].connect(NULL,NULL,&nd[4]);
	nd[8].connect(NULL,NULL,&nd[3]);
	nd[7].connect(NULL,NULL,&nd[3]);
	//second
	nd[6].connect(&nd[13],&nd[14],&nd[2]);
	nd[5].connect(&nd[11],&nd[12],&nd[2]);
	nd[4].connect(&nd[9],&nd[10],&nd[1]);
	nd[3].connect(&nd[7],&nd[8],&nd[1]);
	//third
	nd[2].connect(&nd[5],&nd[6],&nd[0]);
	nd[1].connect(&nd[3],&nd[4],&nd[0]);
	//exit
	nd[0].connect(&nd[1],&nd[2],NULL);
	//weights for second,third and exit layer
	nd[6].assigninit(0.5,0.5);
	nd[5].assigninit(0.5,0.5);
	nd[4].assigninit(0.5,0.5);
	nd[3].assigninit(0.5,0.5);
	nd[2].assigninit(0.5,0.5);
	nd[1].assigninit(0.5,0.5);
	nd[0].assigninit(0.5,0.5);
	int j,k, temp;
	double margin=0.16;
	printmodel(&nd[0],7);
	for(j=0;j<len;j++)	{
		nd[7].value = col1[j];
		nd[8].value = 1.0;
		nd[9].value = col2[j];
		nd[10].value = 1.0;
		nd[11].value = col3[j];
		nd[12].value = 1.0;
		nd[13].value = col4[j];
		nd[14].value = 1.0;
		//shart
		nd[0].value = 0.0;
		//expect is type array
		for(k=0;((1-margin)*type[j] > nd[0].value) || (nd[0].value > (1+margin)*type[j]);k++ )
		{
			//run the model to nd6
			runmodel(&nd[0],6,'+');
			//correct to nd6
			correctonce(&nd[0],&nd[0],type[j],6,k);
			if (k==0)       {
				temp = roundn(nd[0].value);
                                printf("GUESS:\t%d\t%f,%f,%f,%f\t%f\t%f,%d\t%f margin\n", k,col1[j],col2[j],col3[j],col4[j],type[j],nd[0].value,temp, ((nd[0].value-type[j])/type[j]));
			}
		}
		temp = roundn(nd[0].value);
		printf("DONE:\t%d\t%f,%f,%f,%f\t%f\t%f,%d\t%f margin\n", k,col1[j],col2[j],col3[j],col4[j],type[j],nd[0].value, temp, ((nd[0].value-type[j])/type[j]));
	}
	printmodel(&nd[0],7);
}
