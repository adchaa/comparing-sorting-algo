#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 10000

void readTestFile(char * fileName, int *restrict array , size_t size){
  FILE * f = fopen(fileName,"r");
  if (f == NULL){
    fprintf(stderr, "cannot open the file");
    exit(1);
  }

  for(int i = 0 ; i< size ; i++)
    fscanf(f, "%d,", &array[i]);
}

void printArray(int *restrict array, size_t size){
  printf("[");
  for (int i =0; i<size;i++){
    printf("%d,",array[i]);
  }
  printf("]\n");
}

void swap(int * a,int * b){
  *a = *a ^ *b;
  *b = *a ^ *b;
  *a = *a ^ *b;
}

void bubbleSort(int *restrict array, size_t size){
  int swapped = 1;
  while(swapped){
    swapped = 0;
    for (int i = 1;i< size;i++){
      if (array[i-1] > array[i]){
        swap(&array[i-1], &array[i]);
        swapped = 1;
      }
    }
  }
}

int main(){
  char fileName[256];
  int array[ARRAY_SIZE];

  sprintf(fileName, "test_files/TEST_%d",ARRAY_SIZE);
  readTestFile(fileName, array, ARRAY_SIZE);

  clock_t before = clock();
  bubbleSort(array, ARRAY_SIZE);
  clock_t after = clock();
  clock_t diff_ms  = (after - before) * 1000 / CLOCKS_PER_SEC;

  printf("Time taken %ld ms \n",diff_ms);

  return 0;
}
