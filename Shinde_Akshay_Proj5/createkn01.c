#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>

#define MIN_N_LIMIT 4
#define MAX_N_LIMIT 8
#define MIN_PROFIT_LIMIT 10
#define MAX_PROFIT_LIMIT 30
#define MIN_WEIGHT_LIMIT 5
#define MAX_WEIGHT_LIMIT 20

int n = 0;
int capacity = 0;
int sumWeight = 0;

int main(int argc, char *argv[]) {
  if(argc == 2){
    srand((unsigned) time(NULL));
    FILE *fp;
    while(n < MIN_N_LIMIT || n > MAX_N_LIMIT) {
      n = (rand() % MAX_N_LIMIT) + MIN_N_LIMIT;
    }
    printf("\nSelected n value is:%d",n);
    int p[n], wt[n];

    for(int i =1; i <= n; i++) {
      while(p[i] < MIN_PROFIT_LIMIT || p[i] > MAX_PROFIT_LIMIT) {
        p[i] = (rand() % MAX_PROFIT_LIMIT) + MIN_PROFIT_LIMIT;
      }
      while(wt[i] < MIN_WEIGHT_LIMIT || wt[i] > MAX_WEIGHT_LIMIT) {
        wt[i] = (rand() % MAX_WEIGHT_LIMIT) + MIN_WEIGHT_LIMIT;
      }
      sumWeight += wt[i];
    }

    capacity = floor(0.6 * sumWeight);
    printf("\nCapacity is:%d\n",capacity);
    fp = fopen(argv[1], "w");
    fprintf(fp, "%d\t%d\n", n, capacity);
    for(int i = 1; i <= n; i++) {
      fprintf(fp, "Item\t%d\t%d\t%d\n", i, p[i], wt[i]);
    }
    fclose(fp);
  }
  else{
    printf("Insufficicent arguments passed.No file.\n");
    return 0;
  }
}
