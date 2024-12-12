#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "minHeap.h"

void troca(Celula* a, Celula* b){
    Celula temp = *a;
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

void heapify(Sudoku* sudoku, int i){
    int e = esquerda(i);
    int d = direita(i);
    int menor = i;
    if(e < sudoku->tamHeap && sudoku->heap[e].num_possiveis < sudoku->heap[i].num_possiveis)
        menor = e;
    if(d < sudoku->tamHeap && sudoku->heap[d].num_possiveis < sudoku->heap[menor].num_possiveis)
        menor = d;
    if(menor != i){
        troca(&sudoku->heap[menor], &sudoku->heap[i]);
        heapify(sudoku, menor);
    }
}

bool insere(Sudoku* sudoku, Celula elemento){

    sudoku->tamHeap++;
    int i = sudoku->tamHeap-1;
    sudoku->heap[i] = elemento;
    while(i != 0 && sudoku->heap[pai(i)].num_possiveis > sudoku->heap[i].num_possiveis){
        troca(&sudoku->heap[pai(i)], &sudoku->heap[i]);
        i = pai(i);
    }
}

Celula removeMin(Sudoku* sudoku){
    if(sudoku->tamHeap == 1){
        sudoku->tamHeap--;
        return sudoku->heap[0];
    }

    Celula raiz = sudoku->heap[0];
    sudoku->heap[0] = sudoku->heap[sudoku->tamHeap-1];
    sudoku->tamHeap--;
    heapify(sudoku, 0);

    return raiz;
}

void constroiHeapVazio(Sudoku* sudoku, int n){
    sudoku->heap = (Celula*)calloc(n, sizeof(sizeof(int)));
}

void constroiHeap(Sudoku* sudoku, Celula* vetor, int n){
    constroiHeapVazio(sudoku, n);
    for(int i = 0; i < n; i++)
        sudoku->heap[i] = vetor[i];
    for(int i = (sudoku->tamHeap/2)-1; i >= 0; i--)
        heapify(sudoku, i);
}