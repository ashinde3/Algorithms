#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define MAX_LIMIT 999999

int n = 0,capacity = 0;
int temp;
FILE *fp;
FILE *fp1;
FILE *fp2;
int count = 0;
int totalWeight = 0;
char ch[20];
int Arr[MAX_LIMIT][MAX_LIMIT];
int knapsack[MAX_LIMIT][MAX_LIMIT];
int t_n;
int t_cap;
int t_n2;
int t_cap2;

int dynamicKnapsack(int *weight, int *profit, int n, int M) {
  if(n != 0 || M > 0) {
    for(int i = n-1;i>=0;i--)
		{
      if((weight[i] > M) || (dynamicKnapsack(weight,profit,n-1,M) > (profit[i] + dynamicKnapsack(weight,profit,n-1,M-weight[i]))))
      {
        knapsack[n][M] = 0;
      }
      else
      {
        knapsack[n][M] = 1;
      }
			if(weight[i] > M)
			{
				return dynamicKnapsack(weight,profit,n-1,M);
			}
			else if((dynamicKnapsack(weight,profit,n-1,M)) > (profit[i] + dynamicKnapsack(weight,profit,n-1,M-weight[i])))
      {
        Arr[n][M] = dynamicKnapsack(weight,profit,n-1,M);
        return dynamicKnapsack(weight,profit,n-1,M);
      }
      else
      {
        // knapsack[n][M] = 0;
        Arr[n][M] = profit[i] + dynamicKnapsack(weight,profit,n-1,M-weight[i]);
        return profit[i] + dynamicKnapsack(weight,profit,n-1,M-weight[i]);
      }
		}
  }
  return 0;
}

int main(int argc, char *argv[]) {
  if(argc == 2){
    int p,wt,temp2 = 0,temp1 = 0;
    fp = fopen("output2.txt","w");
    fp1 = fopen("entries2.txt","w");
    fp2 = fopen(argv[1],"r");
    fscanf(fp2,"%d %d",&n,&capacity);
    //printf("n=%d\ncap=%d\n",n,capacity);
    int profit[n],weight[n];
    while(fscanf(fp2,"%s %d %d %d",ch,&temp2,&p,&wt) != EOF && n > temp1)
    {
      profit[temp1] = p;
      weight[temp1] = wt;
      temp1++;
    }
    dynamicKnapsack(weight,profit,n,capacity);
  	t_n = n;
    t_cap = capacity;
  	for(int i = 0;i<n;i++)
  	{
  		if(knapsack[t_n][t_cap] == 1)
  		{
  			count++;
  			totalWeight += weight[t_n-1];
  			t_cap -= weight[t_n-1];
  		}
  		t_n--;
  	}
  	fprintf(fp,"%d %d %d\n",count,dynamicKnapsack(weight,profit,n,capacity),totalWeight);
  	t_n2 = n;
    t_cap2 = capacity;
    int p1,w1;
    //printf("countentr=%d\n",count);
  	for(int i = n;i >= 1;i--)
  	{
  		if(knapsack[t_n2][t_cap2] == 1)
  		{
        // p1 = profit[t_n2-1];
        // w1 = weight[t_n2-1];
   			fprintf(fp,"Item%d %d %d\n",t_n2,profit[t_n2-1],weight[t_n2-1]);
   			t_cap2 -= weight[n-1];
  		}
  		t_n2--;
  	}
  	for(int i = 1;i<=n;i++)
  	{
  		fprintf(fp1,"row%d ",i);
  		for(int j = 0;j<=capacity;j++)
  		{
  			if(Arr[i][j] != 0)
  			{
  				fprintf(fp1,"  %d ",Arr[i][j]);
  			}
  		}
  		fprintf(fp1,"\n");
  	}
    fclose(fp);
    fclose(fp1);
    fclose(fp2);
  }


}
