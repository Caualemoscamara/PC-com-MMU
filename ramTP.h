#ifndef RAMTP_H
#define RAMTP_H

#include <math.h>
#include <stdbool.h>
#include <stdio_ext.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//#include "leituraInstrucao.h"
//#include "cpu.h"
//#include "mmu.h"
//#include "gerarInst.h"

// novas
// criar funcao is atualizado

#define TAM_PALAVRAS 4  // Tamanho fixo de palavras em cada bloco
#define NUM_CONJUNTOS 8 // Número de conjuntos na cache
#define VIAS 2          // Número de blocos por conjunto (associatividade)
#define TAM_RAM 1000    // Quantidade total de blocos na RAM definido na main possivelmetne

typedef struct {
    bool inBloco_zero;              // se bloco 0 esta ocupado = true
    int endBloco;                   // Endereço do bloco na RAM
    int palavras[TAM_PALAVRAS];      // Dados armazenados
    int cacheHit;                    // Contador de hits
    int custo;                        // Custo do acesso
    bool atualizado;  
    time_t timestamp; 
} BlocoMemoria;

typedef struct {
    BlocoMemoria* blocos;             // Array de blocos dentro do conjunto
    int qtd_blocos_por_conjunto;      // Capacidade do conjunto (vias)
} ConjuntoCache;

typedef struct {
    ConjuntoCache* conjuntos;         // Array de conjuntos
    int qtd_conjuntos;                // Número total de conjuntos
    int total_blocos;                 // Quantidade total de blocos
    int custo_total;   
    int cache_full;                // Custo total dos acessos à cache
} cacheTP2;

typedef struct {
    BlocoMemoria* blocos;             // RAM armazena blocos sequenciais
    int tamanhoRam;                    // Tamanho total da RAM (em blocos)
    int ramFULL;
} RAM_TP2;

// Define uma estrutura que classifica as instruções dadas para uma operação
typedef struct {
    int add1;
    int endPalavra1;
    int add2;
    int endPalavra2;
    int add3;
    int endPalavra3;
    int opcode;
} Instrucao;


// Funções compartilhadas
cacheTP2* criarCache (int tamanho_da_cache,int num_conjuntos, int vias);

//RAM_TP2* criadorDeRamTp2(int qtd_de_conjuntos, int tamanhoRam, int qtd_total_de_blocos_por_conjunto);
RAM_TP2* criarRAM(int tamanhoRam);

void liberarRAM(RAM_TP2* ram);

void inicializarRAM (RAM_TP2 *);

void imprimeRamTp2 (RAM_TP2*r);

BlocoMemoria getDado(RAM_TP2* ram, int endConj, int endBloco);

void setDado(RAM_TP2* ram, int endConj, int endBloco, BlocoMemoria bloco);

void liberaCache(cacheTP2 *c);

void imprimeBloco(BlocoMemoria bloco);

#endif
