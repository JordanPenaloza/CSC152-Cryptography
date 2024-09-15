#include <stdio.h>
#include <stdlib.h>

int* createRandomPermutation(int n){
	int* array = (int*)malloc(n * sizeof(int));
	int random;
	int tmp;
	for(int i = 0; i < n; i++){
		array[i] = i;
	}
	for (int i = 0; i < n; i++){
		random = rand() % n;
		tmp = array[i];
		array[i] = array[random];
		array[random] = tmp;	
	}
	return array;
}
