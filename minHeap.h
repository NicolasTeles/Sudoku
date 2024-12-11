#ifndef HEAP
#define HEAP

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct minHeap{
    int tam;
    int capacidade;
    int* vetor;
}MinHeap;

int troca(int* a, int* b);

int esquerda(int i);

int direita(int i);

int pai(int i);

void heapify(MinHeap* heap, int i);

bool insere(MinHeap* heap, int elemento);

int removeMin(MinHeap* heap);

#endif