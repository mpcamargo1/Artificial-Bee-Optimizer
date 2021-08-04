#ifndef LIB_H
#define LIB_H

#include<stdio.h>

#define AGENT 		50
#define DIMENSION	2
#define MAX_IT 		1000
#define MAX_TRIAL 	7
#define ONLOOKER 	20

typedef struct abc{
	double bee[AGENT][DIMENSION];
	double trial[AGENT];
	double prob[AGENT];
	double best_solution;
}ABC;

double optimize(ABC *abc);

#endif // LIB_H_
