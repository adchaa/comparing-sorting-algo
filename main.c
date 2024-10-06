#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int sizes[] = {1000,5000,10000,20000,50000,100000};
const size_t sizes_length = sizeof(sizes)/sizeof(sizes[0]);
typedef  void (*sort_func_t)(int *restrict array, size_t size);

void readTestFile(char *restrict fileName, int *restrict array , size_t size){
  FILE * f = fopen(fileName,"r");
  if (f == NULL){
    fprintf(stderr, "cannot open the file");
    exit(1);
  }
  for(int i = 0 ; i< size ; i++)
    fscanf(f, "%d,", &array[i]);
}

void writeToFile(char * fileName,char * content){
  FILE * f = fopen(fileName,"w");
  if (f == NULL){
    fprintf(stderr, "cannot open the file");
    exit(1);
  }
  fwrite(content,strlen(content),1,f);
}

void printArray(int *restrict array, size_t size){
  printf("[");
  for (int i =0; i<size;i++){
    printf("%d,",array[i]);
  }
  printf("]\n");
}

void swap(int *restrict a,int *restrict b){
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

void insertionSort(int *restrict array, size_t size){
  for(int i =1;i<size;i++){
    int j = i;
    while ((j > 0) && (array[j] < array[j-1])) {
      swap(&array[j], &array[j-1]);
      j--;
    }
  }
}

int isSorted(int *restrict array,int size){
  for (int i =0;i<size-1;i++)
    if(array[i] > array[i+1]) return 0;
  return 1;
}

sort_func_t getSortFunction(char * str){
  if(strcmp(str, "inseration") == 0){
    return &insertionSort;
  }

  if(strcmp(str, "bubble") == 0){
    return &bubbleSort;
  }
  return NULL;
}

int main(int argc,char ** argv){
  if(argc < 2){
    fprintf(stderr, "provide more args\n");
    return 1;
  }
  char fileName[256];
  char content[5000];
  char * algo_name = argv[1];

  sort_func_t sortFunction = getSortFunction(algo_name);

  sprintf(content,"size,time\n");
  for(int i=0;i< sizes_length;i++){
    int array_size = sizes[i];
    int array[array_size];

    sprintf(fileName, "test_files/TEST_%d",array_size);
    readTestFile(fileName, array, array_size);

    clock_t before = clock();
    sortFunction(array, array_size);
    clock_t after = clock();
    clock_t diff_ms  = (after - before) * 1000 / CLOCKS_PER_SEC;

    assert(isSorted(array,array_size));
    char temp[256];
    sprintf(temp,"%d,%ld\n",array_size,diff_ms);
    strcat(content, temp);
  }

  printf("%s\n",content);
  char fileTestName[256];
  sprintf(fileTestName,"benchmark_result/%s.csv",algo_name);
  writeToFile(fileTestName, content);
  return 0;
}
