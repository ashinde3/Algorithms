#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

int n = 0,capacity = 0;
int p,wt;
int temp, temp1 = 0;
int count = 0;
int totalWeight = 0;
int totalProfit = 0;
FILE *fp;
FILE *fp1;
int profit;
int weight;
int new_weight = 0;
int new_profit = 0;
int new_element[20];
char ch[20];

//Bruteforce method
int bruteforce(int *w, int *p) {
  int i,k;
  int total_combination = pow(2,n);
  int elements[n];
  memset(elements,0,sizeof(elements));
  for(i = 0; i < total_combination; i++) {
    //int j = n;
    profit = 0;
    weight = 0;

    k = 1;
    for(int m = 0; m < n; m++) {
      if(elements[m] == 1) {
        weight += w[m];
        profit += p[m];
      }
    }
    if((new_profit < profit) && (weight <= capacity)){
      new_profit = profit;
      for(int j = 0; j < n; j++) {
        new_element[j] = elements[j];
      }
    }
    for(int j = 0; j < n; j++) {
      elements[j] += k;
      k = elements[j] / 2;
      elements[j] = elements[j] % 2;
    }
  }
  return new_profit;
}

int main(int argc, char *argv[]) {
  if(argc == 2) {
    fp = fopen("output1.txt","w");
    fp1 = fopen(argv[1],"r");
    fscanf(fp1,"%d\t%d", &n,&capacity);
    int profit[n],weight[n];
    while(fscanf(fp1,"%s\t%d\t%d\t%d",ch,&temp,&p,&wt) != EOF && n > temp1) {
        profit[temp1] = p;
        weight[temp1] = wt;
        temp1++;
    }
    bruteforce(weight,profit);
    for(int i = 0; i < n; i++) {
      if(new_element[i] == 1) {
        totalWeight += weight[i];
      }
    }
    for(int i = 0; i < n; i++) {
      if(new_element[i] == 1) {
        count++;
      }
    }

    fprintf(fp,"%d\t%d\t%d\n", count,bruteforce(weight,profit),totalWeight);

    for(int i = 0; i < n; i++) {
      if(new_element[i] == 1)
        fprintf(fp,"Item\t%d\t%d\t%d\n",i+1,profit[i],weight[i]);
    }
    fclose(fp1);
    fclose(fp);
  }
  else {
    printf("\nInvalid arguments.\n");
    return 0;
  }
}
