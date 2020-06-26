#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int n = 0,capacity = 0;
int count = 0;
int maxP,num;
float temp;
int bestSet[10];
FILE *fp;
FILE *fp1;
FILE *fp2;
int include[10];
int totalWeight = 0;
char ch[20];
int temp1 = 0;


//TO check for promising node
int promising(int i,int p,int c,int w,int len,int *weight,int *profit)
{
	if(c <= w)
		return 0;
	fprintf(fp1,"%d %d %d\n",p,w,kwf2(i+1,w,p,len,c,weight,profit));
	return (kwf2(i+1,w,p,len,c,weight,profit) > maxP);
}

//Method for knapsack with fraction
int kwf2(int i,int w,int p,int len,int c,int *weight,int *profit)
{
	int bound = p;
	while(c > w && len >= i)
	{
		if(w + weight[i-1] <= c)
		{
			w += weight[i-1];
			bound += profit[i-1];
		}
		else
		{
			temp = (float)(c-w)/(float)weight[i-1];
			w = c;
			bound += profit[i-1]*temp;
		}
		i++;
	}
	return bound;
}

void knapsack(int i,int p,int w,int c,int len,int *weight,int *profit)
{
	if(c >= w && maxP < p)
	{
		maxP = p;
		num = i;
		for(int j = 0;j < n;j++)
			bestSet[j] = include[j];
	}
	if(promising(i,p,c,w,len,weight,profit))
	{
		include[i+1] = 1;
		knapsack(i+1,p+profit[i],w+weight[i],c,len,weight,profit);
		include[i+1] = 0;
		knapsack(i+1,p,w,c,len,weight,profit);
	}
}
void backtrack(int *weight,int *profit)
{
  num = 0;
	maxP = 0;
  int t_weight = 0;
  int t_profit = 0;
	knapsack(0,0,0,capacity,n,weight,profit);
	for(int i = 0;i < n;i++)
	{
		if(bestSet[i] == 1)
		{
			t_profit += profit[i-1];
			t_weight += weight[i-1];
		}
	}
  for(int i = 0;i < n;i++)
	{
		if(bestSet[i] == 1)
		{
			count++;
		}
	}
	fprintf(fp,"%d %d %d\n",(int)count,(int)t_profit,(int)t_weight);
	for(int i = 0;i < n;i++)
	{
		if(bestSet[i] == 1)
		{
			fprintf(fp,"Item%d %d %d\n",(int)i,(int)profit[i-1],(int)weight[i-1]);
		}
	}

}

int main(int argc,char *argv[])
{
	if(argc == 2)
	{
    fp = fopen("output3.txt","w");
  	fp2 = fopen(argv[1],"r");
  	fp1 = fopen("entries3.txt","w");
  	int p,wt,temp2;
  	fscanf(fp2,"%d %d",&n,&capacity);
  	int profit[n];
  	float profit_weight[n];//profit per unit weight
  	int weight[n];
  	while(fscanf(fp2,"%s %d %d %d",ch,&temp2,&p,&wt) != EOF && n > temp1)
  	{
  		profit[temp1] = p;
  		weight[temp1] = wt;
  		temp1 = temp1 + 1;
  	}
  	for(int i = 0;i<n;i++)
  	{
  		profit_weight[i] = (double)profit[i]/(double)weight[i];

  	}
  	for(int i = 1;i<=n;i++)
  	{
  		for(int j = i;j<n-1;j++)
  		{
  			if(profit_weight[i] < profit_weight[j])
  			{
          profit_weight[i] = profit_weight[i] + profit_weight[j];
          profit_weight[j] = profit_weight[i] - profit_weight[j];
          profit_weight[i] = profit_weight[i] - profit_weight[j];
  			}
  		}
  	}
    for(int i = 0;i<n-1;i++)
  	{
  		for(int j = i+1;j<n;j++)
  		{
  			if(profit_weight[i] < profit_weight[j])
  			{
          profit[i] = profit[i] + profit[j];
          profit[j] = profit[i] - profit[j];
          profit[i] = profit[i] - profit[j];
  			}
  		}
  	}
    for(int i = 0;i<n-1;i++)
  	{
  		for(int j = i+1;j<n;j++)
  		{
  			if(profit_weight[i] < profit_weight[j])
  			{
          weight[i] = weight[i] + weight[j];
          weight[j] = weight[i] - weight[j];
          weight[i] = weight[i] - weight[j];
  			}
  		}
  	}
  	backtrack(weight,profit);
    fclose(fp);
    fclose(fp1);
    fclose(fp2);
	}
  else {
    printf("\nInvalid arguments\n");
    return 0;
  }

}
