#ifndef CPU_H
#define CPU_H
#include "ramTP.h"
#include "mmu.h"
typedef struct {
    BlocoMemoria registradores[3];
    int PC;
    Instrucao* programa; // fazer agora criador de vetor com base no arquivo txt gerado
    int opcode;
    int custo;

    cacheTP2* cache1;
    cacheTP2* cache2;
    cacheTP2* cache3;

} CPU;

typedef struct{
    int c1Miss;
    int c2Miss;
    int c3Miss;
    
    int c1Hit;
    int c2Hit;
    int c3Hit;

    int ramMiss;

   long long int custoFinal;
} MissAndHit;

//void liberaCpu (CPU*c);
CPU* criarCPU(int tamC1, int tamC2, int tamC3, int nInst, int numConj, int vias);
MissAndHit * valoresInicia ();
void iniciarCPU(CPU* cpu, RAM_TP2* ram, Instrucao* programa, MissAndHit* valores);
void liberaCUPUAU (CPU*c);
void liberaValores(MissAndHit* m);

void imprimeCPU (CPU* c);
void imprimeMissAndHit (MissAndHit* m);
#endif
