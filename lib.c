#include"lib.h"
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<math.h>

#define MAX_IT_EB 			25
#define MAX_IT_OB 			25
#define LOWER 				100
#define UPPER 				100


double get_random(int M,int N);
double fitness(double *x);
double function(double *x);
int selectbee(ABC *abc);
void employed_bees(ABC *abc);
void onlooker_bees(ABC *abc);
void scout_bees(ABC *abc);
void buildprobabilities(ABC *abc);
void initialize(ABC *abc);
void printSolution(ABC *abc);

double get_random(int M,int N){

	return (M + rand() / (RAND_MAX / (N - M + 1) + 1));

}

double randfrom(double min, double max) 
{
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}


double optimize(ABC *abc){
	srand(time(NULL));
	initialize(abc);
	for(int i=0;i<MAX_IT;i++){
		employed_bees(abc);
		onlooker_bees(abc);
		scout_bees(abc);
	}
	printSolution(abc);
	return 1;


}

void printSolution(ABC *abc){
	double best_solution = function(abc->bee[0]);
	int index = 0;
	for(int i=1;i<AGENT;i++){
		if(function(abc->bee[i])< best_solution){
			best_solution = function(abc->bee[i]);
			index = i;
		}
	}
	printf("f(x,y) = %lf x = %lf, y = %lf\n",best_solution,abc->bee[index][0],abc->bee[index][1]);


}

void initialize(ABC *abc){

	for(int i=0;i<AGENT;i++){
		abc->bee[i][0] = get_random(-15,-5);
		abc->bee[i][1] = get_random(-3,3);
	
	}



}

void employed_bees(ABC *abc){

	for(int a=0;a<MAX_IT_EB;a++){
		for(int i=0;i<AGENT;i++){
			int index_j = get_random(0,AGENT-1);
			int index_dimension = get_random(0,DIMENSION-1);
			double aux[DIMENSION];
			memcpy(aux,abc->bee[index_j],sizeof abc->bee[index_j]);
			
			aux[index_dimension] = abc->bee[i][index_dimension] + randfrom(-1,1)*(abc->bee[i][index_dimension] - abc->bee[index_j][index_dimension]);
			
			if(function(aux) < function(abc->bee[i])){
				memcpy(abc->bee[i],aux,sizeof abc->bee[i]);	
			}
			else
				abc->trial[i]++; 	
		}
	
	}


}

void onlooker_bees(ABC *abc){
	
	buildprobabilities(abc);
	int i=0;
	for(int a=0;a<MAX_IT_OB;a++){
		i = selectbee(abc);
		int index_j = get_random(0,AGENT-1);
		int index_dimension = get_random(0,DIMENSION-1);
		double aux[DIMENSION];
		memcpy(aux,abc->bee[index_j],sizeof abc->bee[index_j]);
		
		aux[index_dimension] = abc->bee[i][index_dimension] + randfrom(-1,1)*(abc->bee[i][index_dimension] - abc->bee[index_j][index_dimension]);
		
		if(function(aux) < function(abc->bee[i])){
			memcpy(abc->bee[i],aux,sizeof aux);
		
		}
		else
			abc->trial[i]++; 	
		
		
	}
}	



int selectbee(ABC *abc){
	double prob = (double)rand()/RAND_MAX;
	double acc = 0;
	int i,index_selected;
	for(i=0;i<AGENT;i++){
		acc += abc->prob[i];
		//fprintf(stderr,"%lf e %lf\n",acc,prob);
		if(prob < acc){
			index_selected = i;
			break;
		}
	}
	//fprintf(stderr,"Selecionado %d\n",index_selected);
	return index_selected;

}

void buildprobabilities(ABC *abc){
	double acc=0;
	for(int i=0;i<AGENT;i++)
		acc += fitness(abc->bee[i]);
	
	for(int a=0;a<AGENT;a++){
		abc->prob[a] = fitness(abc->bee[a])/acc;
	}
	
}


void scout_bees(ABC *abc){

	for(int i=0;i<AGENT;i++){
		if(abc->trial[i] >= MAX_TRIAL){
			abc->trial[i] = 0;
			int dimension = get_random(0,DIMENSION-1);

			abc->bee[i][dimension] = LOWER + randfrom(0,1)*(UPPER - LOWER);
			
		
		}
	
	}

}


double fitness(double *x){

	if (function(x) >= 0)
		return 1/(1+function(x));
	else
		return 1 + (-1*function(x));

}

double function(double *x){

	return 100*(sqrt(fabs(x[1] - 0.01*pow(x[0],2)))) + 0.01*fabs(x[0] + 10);
	
	

}



