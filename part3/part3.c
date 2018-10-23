#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>
#include<string.h>


//define the global variables
int N;	//the number of cities
int *final_path;	//the shortest path of cities the people traveled
bool *visited;	// in order to record whether the city is checked
double final_res;	//the final distance of the shortest path

//define the function
void copyToFinal(int *curr_path);
double firstMin(double adj[N][N], int i);
double secondMin(double adj[N][N], int i);
void TSPRec(double adj[N][N], double curr_bound, double curr_weight, int level, int curr_path[]);
void TSP(double adj[N][N]);
double **readFile(double **C,char *name);

double **readFile(double **C,char *name){
	FILE *fp;
	if((fp=fopen(name,"r"))==NULL)
	{
		printf("this file cannot be opened.\n");
		exit(0);
	}
	if(feof(fp))
	{
		printf("this file is empty\n");
		fclose(fp);
		exit(0);
	}
	int N;
	fscanf(fp,"%d\n",&N);
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++)
			fscanf(fp,"%lf ",&C[i][j]);
		fscanf(fp,"\n");
	}
	return C;
}

void copyToFinal(int *curr_path){
	for (int i = 0; i < N; i++){
		final_path[i] = curr_path[i];
	}
	final_path[N] = curr_path[0];
}

double firstMin(double adj[N][N], int i){
	double min = (double) INT_MAX;
	for (int k = 0; k < N; k++){
		if (adj[i][k] < min && i != k){
			//printf("min: %lf  adj: %lf\n", min, adj[i][k]);
			min = adj[i][k];
		}
	}
	return min;
}

double secondMin(double adj[N][N], int i){
	double first = (double) INT_MAX, second = (double) INT_MAX;
	for (int j = 0; j < N; j++){
		if (i == j) continue;
		if (adj[i][j] <= first){
			second = first;
			first = adj[i][j];
		}else if (adj[i][j] < second){
			second = adj[i][j];
		}
	}
	return second;
}

void TSPRec(double adj[N][N], double curr_bound, double curr_weight, int level, int curr_path[]){
	if (level == N){
		double curr_res = 0;
		if (adj[curr_path[level-1]][0] != 0){
			curr_res = curr_weight + adj[curr_path[level-1]][curr_path[0]];
		}
		//printf("res: %lf\n", curr_res);
		if (curr_res < final_res){
			copyToFinal(curr_path);
			final_res = curr_res;
		}
		return;
	}
	for (int i = 0; i < N; i++){
		if (adj[curr_path[level-1]][i] != 0 && visited[i] == false){
			double temp = curr_bound;
			curr_weight += adj[curr_path[level-1]][i];

			if (level == 1){
				double temp2 = firstMin(adj, curr_path[level-1]) + firstMin(adj, i);
				curr_bound = temp2/2;
			}else {
				double temp3 = secondMin(adj, curr_path[level-1]) + firstMin(adj, i);
				curr_bound = temp3/2;
			}

			if (curr_bound + curr_weight < final_res){
				curr_path[level] = i;
				visited[i] = true;
				TSPRec(adj, curr_bound, curr_weight, level+1, curr_path);
			}
			curr_weight -= adj[curr_path[level-1]][i];
			curr_bound = temp;
			for(int j=0;j<N;j++)
				visited[j]=false;
			for (int j = 0; j <= level-1; j++){
				visited[curr_path[j]] = true;
			}
		}
	}
}

void TSP(double adj[N][N]){
	int curr_path[N+1];

	double curr_bound = 0;
	for(int i=0;i<(N+1);i++){
		curr_path[i]=-1;
	}
	for(int j=0;j<N;j++)
		visited[j]=false;
	for (int i = 0; i < N; i++){
		curr_bound += (firstMin(adj, i) + secondMin(adj, i));
	}
	curr_bound /= 2;
	printf("start bound: %lf\n", curr_bound);
	visited[0] = true;
	curr_path[0] = 0;
	TSPRec(adj, curr_bound, 0, 1, curr_path);
}



int main(int argc, const char *args[]){
	if (argc != 2){
		printf("please input the number of cities");
	}
	final_res = INT_MAX;
	char nameTime[20]="mixTime";
	char nameMoney[20]="mixMoney";
	FILE *in;
	in = fopen("bestDistance", "r");
	fscanf(in, "%d\n", &N);

	N = (int) strtol(args[1], NULL, 10);
	double sumTime=0.0;
	double sumMoney=0.0;
	if(N<1 || N>14){
		printf("invalid input");
		return 0;
	}
	final_path = (int *) malloc((N+1) * sizeof(int));
	if(final_path==NULL){
		printf("malloc error");
		return -1;
	}
	visited = (bool *) malloc(N * sizeof(bool));
	if(visited==NULL){
		printf("malloc error");
		return -1;
	}
	double **bestTime=(double**)malloc(N*sizeof(double*));
	if(bestTime==NULL){
			printf("malloc error");
			return -1;
	}
	for(int i=0;i<N;i++){
			bestTime[i]=(double*)malloc(N*sizeof(double));
			if(bestTime[i]==NULL){
				printf("malloc error");
				return -1;
			}
	}
	double **bestMoney=(double**)malloc(N*sizeof(double*));
	if(bestMoney==NULL){
			printf("malloc error");
			return -1;
	}
	for(int i=0;i<N;i++){
			bestMoney[i]=(double*)malloc(N*sizeof(double));
			if(bestTime[i]==NULL){
				printf("malloc error");
				return -1;
			}
	}
	double adj[N][N];
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			fscanf(in, "%lf", &adj[i][j]);
			printf("%lf ", adj[i][j]);
		}
		fscanf(in, "%*[^\n]%*c");
		printf("\n");
	}
	TSP(adj);
	printf("Minimum cost : %lf\n", final_res);
	printf("Path Taken : ");
	for (int i=0; i<=N; i++){
		printf("%d ", final_path[i]);
	}
	printf("\n");
	bestTime=readFile(bestTime,nameTime);
	bestMoney=readFile(bestMoney,nameMoney);
	for(int j=0;j<N;j++){
		sumTime+=bestTime[final_path[j]][final_path[j+1]];
		sumMoney+=bestMoney[final_path[j]][final_path[j+1]];
	}
	printf("The sum of time of shortest path is %lf \n",sumTime);
	printf("The sum of money of shortest path is %lf \n",sumMoney);
	return 0;
	for(int k=0;k<N;k++){
		free(bestTime[k]);
		free(bestMoney[k]);
	}
	free(final_path);
	free(visited);
}



