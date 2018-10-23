
#include<stdio.h>
#include <stdlib.h>
#include<math.h>
#include <string.h>
#include<limits.h>



typedef struct {
		int **type; 		// the type of transportation, 0:air,1:car,2:rail
		float **time; 	// the time between any two cities
		float **money;	// the money of ticket between two cities
		float **distance;
}city;

const int air_speed=550;	//	the average speed of airplane
const int car_speed=65;	// 	the average speed of car
const int rail_speed=59;	// 	the average speed of rail


city *malloc_matrix(city *C,int N);
void free_matrix(city *C,int N);
city *read_distance(city *C,char *way);
city *read_money(city *C,char *way);
float find_max(float A,float B,float C);
float find_min(float A,float B,float C);

city *malloc_matrix(city *C,int N){
	C =(city*)malloc(sizeof(city));
	if(C==NULL)
	{
		printf("malloc error");
		return(NULL);
	}
	C->type=(int**)malloc(N*sizeof(int*));
	if(C->type==NULL)
		return NULL;
	for(int i=0;i<N;i++){
		C->type[i]=(int*)malloc(N*sizeof(int));
		if(C->type[i]==NULL){
			for (int j = 0; j < i; j++)
				free(C->type[j]);
			return NULL;
		}
	}
	C->time=(float**)malloc(N*sizeof(float*));
	if(C->time==NULL)
		return NULL;
	for(int i=0;i<N;i++){
		C->time[i]=(float*)malloc(N*sizeof(float));
		if(C->time[i]==NULL){
			for (int j = 0; j < i; j++)
				free(C->time[j]);
		return NULL;
		}
	}
	C->money=(float**)malloc(N*sizeof(float*));
	if(C->money==NULL)
		return NULL;
	for(int i=0;i<N;i++){
		C->money[i]=(float*)malloc(N*sizeof(float));
		if(C->money[i]==NULL){
			for (int j = 0; j < i; j++)
				free(C->money[j]);
		return NULL;
		}
	}
	C->distance=(float**)malloc(N*sizeof(float*));
	if(C->distance==NULL)
		return NULL;
	for(int i=0;i<N;i++){
		C->distance[i]=(float*)malloc(N*sizeof(float));
		if(C->distance[i]==NULL){
			for (int j = 0; j < i; j++)
				free(C->distance[j]);
		return NULL;
		}
	}
	return C;
}


void free_matrix(city *C,int N){
	for(int i=0;i<N;i++){
		if(C->type[i]!=NULL)
			free(C->type[i]);
	}
	free(C->type);
	for(int i=0;i<N;i++){
		if(C->time[i]!=NULL)
			free(C->time[i]);
	}
	free(C->time);
	for(int i=0;i<N;i++){
		if(C->money[i]!=NULL)
			free(C->money[i]);
	}
	free(C->money);
	for(int i=0;i<N;i++){
		if(C->distance[i]!=NULL)
			free(C->distance[i]);
	}
	free(C->distance);
}


city *read_distance(city *C,char *way){
	FILE *fp;
	if((fp=fopen(way,"r"))==NULL)
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
			fscanf(fp,"%f ",&C->distance[i][j]);
		fscanf(fp,"\n");
	}
	return C;
}

city *read_money(city *C,char *way){
	FILE *fp;
	if((fp=fopen(way,"r"))==NULL)
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
			fscanf(fp,"%f ",&C->money[i][j]);
		fscanf(fp,"\n");
	}
	return C;
}
void storeFile(city *C,int N){
	FILE *oc;
	oc=fopen("bestDistance","w");
	if (oc!=NULL){
		fprintf(oc,"%d\n",N);
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++)
				fprintf(oc,"%f ",C->distance[i][j]);
			fprintf(oc,"\n");
		}
	}
	fclose(oc);
	FILE *op;
	op=fopen("mixTime","w");
	if (op!=NULL){
		fprintf(op,"%d\n",N);
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++)
				fprintf(op,"%f ",C->time[i][j]);
			fprintf(op,"\n");
		}
	}
	fclose(op);
	FILE *ok;
	ok=fopen("mixType","w");
	if (ok!=NULL){
		fprintf(ok,"%d\n",N);
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++)
				fprintf(ok,"%d ",C->type[i][j]);
			fprintf(ok,"\n");
		}
	}
	fclose(ok);
	FILE *om;
	om=fopen("mixMoney","w");
	if (om!=NULL){
		fprintf(om,"%d\n",N);
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++)
				fprintf(om,"%f ",C->money[i][j]);
			fprintf(om,"\n");
		}
	}
	fclose(om);
}


city *calculate_time(city *C,int speed,int N){
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
			C->time[i][j]=0.0;
	}
	for(int i=0;i<(N-1);i++)
	{
		for(int j=i+1;j<N;j++)
		{
			C->time[i][j]=(C->distance[i][j]/speed);
			C->time[j][j]=C->time[i][j];
		}
	}
	return C;
}

float find_max(float A,float B,float C){
	float max;
	max=A;
	if(B>max)
		max=B;
	if(C>max)
		max=C;
	return max;
}

float find_min(float A,float B,float C){
	float min;
	min=A;
	if(B<min)
		min=B;
	if(C<min)
		min=C;
	return min;
}


int main(int argc, const char * argv[]){
	if (argc != 2) {
		printf("please input a weight whose range is[0 1]");
	    	return 1;
	 }
	double weight = strtod(argv[1], NULL);
	int N=14;
	city City_air=*malloc_matrix(&City_air,N);
	city City_car=*malloc_matrix(&City_car,N);
	city City_rail=*malloc_matrix(&City_rail,N);
	city City_mix=*malloc_matrix(&City_mix,N);
	char way_air[20]="distance_air.txt";
	char way_car[20]="distance_car.txt";
	char way_rail[20]="distance_rail.txt";
	char money_air[20]="money_air.txt";
	char money_car[20]="money_car.txt";
	char money_rail[20]="money_rail.txt";
	City_air=*read_distance(&City_air,way_air);
	City_car=*read_distance(&City_car,way_car);
	City_rail=*read_distance(&City_rail,way_rail);
	City_air=*read_money(&City_air,money_air);
	City_car=*read_money(&City_car,money_car);
	City_rail=*read_money(&City_rail,money_rail);
	City_air=*calculate_time(&City_air,air_speed,N);
	City_car=*calculate_time(&City_car,car_speed,N);
	City_rail=*calculate_time(&City_rail,rail_speed,N);
	float max_time, max_money,min_time,min_money;
	float scale_time,scale_money;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++){
			City_mix.type[i][j]=0;
			City_mix.time[i][j]=0.0;
			City_mix.money[i][j]=0.0;
			City_mix.distance[i][j]=0.0;
		}
	}
	for(int i=0;i<(N-1);i++)
	{
		for(int j=i+1;j<N;j++)
		{
			max_time=find_max(City_air.time[i][j],City_car.time[i][j],City_rail.time[i][j]);
			min_time=find_min(City_air.time[i][j],City_car.time[i][j],City_rail.time[i][j]);
			max_money=find_max(City_air.money[i][j],City_car.money[i][j],City_rail.money[i][j]);
			min_money=find_min(City_air.money[i][j],City_car.money[i][j],City_rail.money[i][j]);
			scale_time=(max_time-min_time);
			scale_money=(max_money-min_money);
			float air=(weight*City_air.time[i][j]/scale_time+(1-weight)*City_air.money[i][j]/scale_money);
			float car=(weight*City_car.time[i][j]/scale_time+(1-weight)*City_car.money[i][j]/scale_money);
			float rail=(weight*City_rail.time[i][j]/scale_time+(1-weight)*City_rail.money[i][j]/scale_money);
			City_mix.distance[i][j]=find_min(air,car,rail);
			City_mix.distance[j][i]=City_mix.distance[i][j];
			if(City_mix.distance[i][j]==car){
				City_mix.type[i][j]=1;
				City_mix.type[j][i]=1;
				City_mix.time[i][j]=City_car.time[i][j];
				City_mix.time[j][i]=City_mix.time[i][j];
				City_mix.money[i][j]=City_car.money[i][j];
				City_mix.money[j][i]=City_mix.money[i][j];
			}
			else if(City_mix.distance[i][j]==air){
				City_mix.type[i][j]=0;
				City_mix.type[j][i]=0;
				City_mix.time[i][j]=City_air.time[i][j];
				City_mix.time[j][i]=City_mix.time[i][j];
				City_mix.money[i][j]=City_air.money[i][j];
				City_mix.money[j][i]=City_mix.money[i][j];
			}
			else{
				City_mix.type[i][j]=2;
				City_mix.type[j][i]=2;
				City_mix.time[i][j]=City_rail.time[i][j];
				City_mix.time[j][i]=City_mix.time[i][j];
				City_mix.money[i][j]=City_rail.money[i][j];
				City_mix.money[j][i]=City_mix.money[i][j];
			}
		}
	}
	storeFile(&City_mix,N);
	free_matrix(&City_air,N);
	free_matrix(&City_car,N);
	free_matrix(&City_rail,N);
	free_matrix(&City_mix,N);
}
