#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "minHeap.h"

int troca(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int esquerda(int i){
    return 2*i+1;
}

int direita(int i){
    return 2*i+2;
}

int pai(int i){
    return (i-1)/2;
}

void heapify(MinHeap* heap, int i){
    int e = esquerda(i);
    int d = direita(i);
    int menor = i;
    if(e < heap->tam && heap->vetor[e] < heap->vetor[i])
        menor = e;
    if(d < heap->tam && heap->vetor[d] < heap->vetor[menor])
        menor = d;
    if(menor != i){
        troca(&heap->vetor[menor], heap->vetor[i]);
        heapify(heap, menor);
    }
}

bool insere(MinHeap* heap, int elemento){
    if(heap->tam == heap->capacidade){
        printf("Impossivel inserir, capacidade alcancada");
        return false;
    }

    heap->tam++;
    int i = heap->tam-1;
    heap->vetor[i] = elemento;
    while(i != 0 && heap->vetor[pai(i)] > heap->vetor[i]){
        troca(&heap->vetor[pai(i)], &heap->vetor[i]);
        i = pai(i);
    }
}

int removeMin(MinHeap* heap){
    if(heap->tam == 1){
        heap->tam--;
        return heap->vetor[0];
    }

    int raiz = heap->vetor[0];
    heap->vetor[0] = heap->vetor[heap->tam-1];
    heap->tam--;
    heapify(heap, 0);

    return raiz;
}

MinHeap* constroiHeapVazio(int n){
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->vetor = (int*)calloc(n, sizeof(sizeof(int)));
    heap->capacidade = n;
    return heap;
}

MinHeap* constroiHeap(int* vetor, int n, int capacidade){
    if(n > capacidade){
        printf("tamanho do vetor maior que capacidade\n");
        return NULL;
    }
    MinHeap* heap = constroiHeapVazio(capacidade);
    for(int i = 0; i < n, i++)
        heap->vetor[i] = vetor[i];
    for(int i = (heap->tam/2)-1; i >= 0; i--)
        heapify(heap, i);
    return heap;
}