#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define proNum 5   //Number of processes	(change here)
#define resTypes 3 //Number of resource types	(change here)
void printSeq(int* data,int num);
int main()
{
int i,j,k;
bool safe;	// safe state
bool check;	// check Need<Work
bool Finish[proNum];

//Initial Value Here
int Max[proNum][resTypes] = {{2,5,3},{2,4,5},{6,2,4},{2,4,3},{5,6,3}};
int Allocation[proNum][resTypes]= {{1,1,3},{0,2,5},{3,1,2},{2,3,2},{1,2,3}};
int Available[resTypes]={1,1,1};

int Need[proNum][resTypes];

for(i=0;i<proNum;i++)
for(j=0;j<proNum;j++)	
	{
	Need[i][j] = Max[i][j] - Allocation[i][j];
	}

//Safety Algorithm
int Work[resTypes];
for(i=0;i<resTypes;i++)
	{
	Work[i] = Available[i];
	}

for(i=0;i<proNum;i++)
	{
	Finish[i] = false;
	}
printf("Sequence of Processes \n");
for(k=0;k<proNum;k++)	//maximum loop can be possible
	{
	for(i=0;i<proNum;i++)	//check every processes in each loop
		{	
		check = true;
		for(j=0;j<resTypes;j++)
			{
			if(Need[i][j] <= Work[j]);
			else check = false;
			}
		if((Finish[i] == false)&&(check == true))
			{
			printf("No: %d \n",i);
			printf("Need:       ");
			printSeq(Need[i],resTypes);
			printf("Work Now:   ");
			printSeq(Work,resTypes);
			printf("Allocation: ");
			printSeq(Allocation[i],resTypes);
		
			for(j=0;j<resTypes;j++)
				{
				Work[j]+=Allocation[i][j];
				}
			printf("Work After: ");
			printSeq(Work,resTypes);
			Finish[i] = true;
			}
		}
	}
printf("\n");
safe = true;
for(i=0;i<proNum;i++)
	{
	if(Finish[i] == true);
	else safe = false;
	}

if(safe == false) 
	{
	printf("The system is not safe.\n");
	exit(0);
	}
else printf("The system is safe.\n");
	

//Resource Request Algorithm
printf("Resource Request Section \n");
int procNo=0;
int reqNo[resTypes];
while(1)
	{
	printf("Available Resource: ");
	printSeq(Available,resTypes);
	printf("\n");
	printf("Enter Process No. \n");
	scanf("%d", &procNo);
	if(procNo >= proNum) 
		{
		printf("Wrong Number of process.\n");
		continue;	
		}
	printf("Enter Request Number for each resource types. \n");
	for(i=0;i<resTypes;i++)
		{
		printf("%d(Need:%d): ",i,Need[procNo][i]);
		scanf("%d", &reqNo[i]);
		}
	printf("Check if request <= Need\n");
	check = true;
	for(i=0;i<resTypes;i++)
		{
			if(reqNo[i]>Need[procNo][i]) 
			{
			printf("Error Wrong Number of require.\n");
			check = false;			
			break;
			}
		}
	if(check==true)
		printf("ok\n");
	else
		continue;
	printf("Check if request <= Available\n");
	check = true;
	for(i=0;i<resTypes;i++)
		{
			if(reqNo[i]>Available[i]) 
			{
			printf("No resource, P.%d Must wait.\n",procNo);
			check = false;
			break;
			}
			
		}
	if(check==true)
		printf("ok\n");
	else
		continue;
	for(i=0;i<resTypes;i++)
		{
		Available[i] -= reqNo[i];
		Allocation[procNo][i] +=  reqNo[i];
		Need[procNo][i] -= reqNo[i];
		}
	printf("Check if process finish \n");
	check = true;
	for(i=0;i<resTypes;i++)
		{
		if(Need[procNo][i] != 0) check = false;
		}
	if(check == true)
		{
		printf("P.%d finished, return resources\n",procNo);
		for(i=0;i<resTypes;i++)
			{
			Available[i] += Allocation[procNo][i] ;
			Allocation[procNo][i] =0;
			}
		printf("Ok\n");
		}
	else printf("No\n");
	}
}

void printSeq(int *data,int num)
{
	int i;
	for(i=0;i<num;i++)
		{
		printf("%d ",data[i]);
		}
	printf("\n");
}

