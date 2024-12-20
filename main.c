#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "logica.h"
#include "entradaSaida.h"

void calculaTempoProcessador(struct rusage usage){
    getrusage(RUSAGE_SELF, &usage);
    
    printf("\nTempo no modo de usuário rodando o processo: %ld.%06ld segundos\n", 
        usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
    printf("Tempo no modo de sistema rodando o processo: %ld.%06ld segundos\n",
        usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);
    
    long total_sec = usage.ru_utime.tv_sec + usage.ru_stime.tv_sec, 
        total_usec = usage.ru_utime.tv_usec + usage.ru_stime.tv_usec;
    
    if(total_usec > 1000000){
        total_usec -= 1000000;
        total_sec++;
    }
    printf("Tempo total do processo no processador: %ld.%06ld segundos\n",
        total_sec, total_usec);
    printf("Memória máxima usada ao mesmo tempo: %ld KB\n", usage.ru_maxrss);
}

void calculaTempoReal(struct timeval start, struct timeval end){
    long tempoRealMicro = abs(start.tv_usec - end.tv_usec);
    int diminuirSegundo = 0;
    if(start.tv_usec > end.tv_usec){
        tempoRealMicro = 1000000 - tempoRealMicro;
        diminuirSegundo = 1;
    }
    long tempoRealSegundo = abs(start.tv_sec - end.tv_sec);
    if(diminuirSegundo)
        tempoRealSegundo--;
    printf("Tempo passado na vida real: %ld.%06ld segundos\n",
        tempoRealSegundo, tempoRealMicro);
}

int main(int argc, char* argv[]){
    char* entrada = NULL;
    char* saida = NULL;
    char modo = 'b';
    struct timeval start, end;
    struct rusage usage;
    
    obterNomeArquivos(argc, argv, &entrada, &saida, &modo);
    FILE* fe = fopen(entrada, "r");
    if(fe == NULL){
        printf("Erro na abertura do arquivo de entrada!\n");
        return 0;
    }
    FILE* fs = fopen(saida, "w");
    if(fs == NULL){
        printf("Erro na abertura do arquivo de saida!\n");
        return 0;
    }
    while(!feof(fe)){
        gettimeofday(&start, NULL);
        Sudoku* s = geraSudoku(fe);
        if(s == NULL){
            fprintf(fs, "Entrada de sudoku invalido!\n\n");
            continue;
        }
        printaMatriz(s->matrizSudoku, s->tamanho);
        int resultado = resolveSudoku(s, modo);
        printf("\n\n%d\n\n", resultado);
        if(resultado){
            printaResultado(s, fs);
            fprintf(fs, "\n");
        }else
            fprintf(fs, "Sudoku Impossível\n\n");
        destroiSudoku(s);
        gettimeofday(&end, NULL);
        printf("====================================================================================\n");

        calculaTempoProcessador(usage);
        calculaTempoReal(start, end);

        printf("====================================================================================\n");
    }
    fclose(fe);
    fclose(fs);
    
    return 0;
}