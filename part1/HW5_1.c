#include<stdio.h>
#include <stdlib.h>
#include<math.h>
#include <string.h>

typedef struct {
		char **name;
		float *latitude;
		float *longtitude;
		float **distance;
}city;

float  R=6371.004;
float  Pi=3.14;

city *malloc_matrix(city *C,int N){
		 C =(city*)malloc(sizeof(city));
		if(C==NULL)
		{
			printf("malloc error");
			return(NULL);
		}
		C->name=(char**)malloc(N*sizeof(char*));
		if(C->name==NULL)
			return NULL;
		for(int i=0;i<N;i++){
			C->name[i]=(char*)malloc(20*sizeof(char));
			if(C->name[i]==NULL){
				for (int j = 0; j < i; j++)
					free(C->name[j]);
			return NULL;
			}
		}
		C->distance=(float**)malloc(N*sizeof(float*));
			if(C->distance==NULL)
				return NULL;
			for(int i=0;i<N;i++){
				C->distance[i]=(float*)malloc(20*sizeof(float));
					if(C->distance[i]==NULL){
						for (int j = 0; j < i; j++)
							free(C->distance[j]);
					return NULL;
				}
			}
		C->latitude=(float*)malloc(N*sizeof(float));
		if(C->latitude==NULL)
			return NULL;
		C->longtitude=(float*)malloc(N*sizeof(float));
		if(C->longtitude==NULL)
			return NULL;
		return C;
}

void free_matrix(city *C,int N){
	for(int i=0;i<N;i++){
		if(C->name[i]!=NULL)
			free(C->name[i]);
	}
	free(C->name);
	for(int i=0;i<N;i++){
		if(C->distance[i]!=NULL)
			free(C->distance[i]);
	}
	free(C->distance);
	free(C->latitude);
	free(C->longtitude);
}

float radian(float d){
	 return d*Pi/180.0;
}
void storeFile(city *C,int N){
	FILE *oc;
	oc=fopen("distance_air.txt","w");
	if (oc!=NULL){
		fprintf(oc,"%d ",N);
		for(int i=0;i<(N+1);i++){
			if(i==0){
				for(int j=0;j<N;j++)
					fprintf(oc,"%s ",C->name[j]);
				fprintf(oc,"\n");
			}
			else{
				fprintf(oc,"%s ",C->name[i-1]);
				for(int k=0;k<N;k++)
					fprintf(oc,"%f ",C->distance[k][i-1]);
				fprintf(oc,"\n");
			}
		}
	}
	fclose(oc);
}
int main(){
	FILE *fp;
	if((fp=fopen("Longandlati.txt","r"))==NULL)
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
	int cityNumber;
	fscanf(fp,"%d\n",&cityNumber);
	//printf("%d\n",cityNumber);
	city City=*malloc_matrix(&City,cityNumber);
	for(int i=0;i<cityNumber;i++){
		fscanf(fp,"%s %f %f\n",City.name[i],&City.latitude[i],&City.longtitude[i]);
		//printf("%s %f %f\n",City.name[i],City.latitude[i],City.longtitude[i]);
	}
	for(int i=0;i<cityNumber;i++)
	{
		for(int j=0;j<cityNumber;j++)
			City.distance[i][j]=0.0;
	}
	for(int i=0;i<(cityNumber-1);i++)
	{
		for(int j=i+1;j<cityNumber;j++)
		{
			double radLat1=radian(City.latitude[i]);
			double radLat2=radian(City.latitude[j]);
			double A=radLat1-radLat2;
			float B=radian(City.longtitude[i])-radian(City.longtitude[j]);
			float C=2*asin(sqrt(pow(sin(A/2),2)+cos(radLat1)*cos(radLat2)*pow(sin(B/2),2)));
			City.distance[i][j]=0.62137*(C*R*10000)/10000;
			//printf("%d and %d is :%.3f\n",i,j,City.distance[i][j]);
			City.distance[j][i]=City.distance[i][j];
		}
	}
	storeFile(&City,cityNumber);
	//out(&City,cityNumber);
	free_matrix(&City,cityNumber);
}

int out(city *C,int N){
	for(int i=0;i<N;i++)
		printf("\t%s",C->name[i]);
	printf("\n");
	for(int i=0;i<N;i++)
	{
		printf("%s",C->name[i]);
		for(int j=0;j<N;j++)
			printf("\t%f",C->distance[i][j]);
		printf("\n");
	}
}
