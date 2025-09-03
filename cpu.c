#include "cpu.h"
// adicionadas agr
//#include <math.h>
//#include <stdbool.h>
//#include <stdio_ext.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <time.h>

#include "geradorHD.h"
#include "gerarInst.h"
#include "leituraInstrucao.h"
//#include "geradorInterupcao.h"

CPU* criarCPU(int tamC1, int tamC2, int tamC3, int nInst, int numConj, int vias){
    CPU* cpu = malloc(sizeof(CPU));
   // cpu->registradores = malloc(3 * sizeof(BlocoMemoria));
    //cpu->programa = malloc((nInst+1) * sizeof(Instrucao));
    cpu->PC = 0;
    cpu->opcode = 0;
    cpu->custo = 0;

    cpu->cache1 = criarCache(tamC1, numConj, vias);
    cpu->cache2 = criarCache(tamC2, numConj, vias);
    cpu->cache3 = criarCache(tamC3, numConj, vias);
    return cpu;
}


MissAndHit * valoresInicia (){
    MissAndHit* m = malloc(sizeof(MissAndHit));
    m->c1Hit = 0;
    m->c2Hit = 0;
    m->c3Hit = 0;

    m->c1Miss = 0;
    m->c2Miss = 0;
    m->c3Miss = 0;
    m->ramMiss = 0;
    m->custoFinal = 0;

    return m;
}

void liberaValores(MissAndHit* m){
    free (m);
}

void iniciarCPU(CPU* cpu, RAM_TP2* ram, Instrucao* programa, MissAndHit* valores){
   // cpu->programa = programa;
    int k = 0;
    while (cpu->opcode != -1) {
       // Instrucao inst = cpu->programa[cpu->PC];
        cpu->opcode = programa[k].opcode;
        

        if (cpu->opcode != -1) {
            cpu->registradores[0] = buscarMem(ram, cpu->cache1, cpu->cache2, cpu->cache3,programa[k].add1);
            cpu->registradores[1] = buscarMem(ram, cpu->cache1, cpu->cache2, cpu->cache3,programa[k].add2); //  buscarMem (RAM_TP2* ram, cacheTP2* cache1, cacheTP2* cache2, cacheTP2* cache3, int endBloco);
            cpu->registradores[2] = buscarMem(ram, cpu->cache1, cpu->cache2, cpu->cache3,programa[k].add3);

            for (int i = 0; i < 3; i++) {
                    if (cpu->registradores[i].custo == 10 && cpu->registradores[i].cacheHit == 1){
                        valores->c1Hit++;
                        continue;
                    }
                    else if(cpu->registradores[i].custo == 110 && cpu->registradores[i].cacheHit == 1){
                        valores->c1Miss++;
                        valores->c2Hit++;
                        continue;
                    }
                    else if(cpu->registradores[i].custo == 1110 && cpu->registradores[i].cacheHit == 1){
                        valores->c1Miss++;
                        valores->c2Miss++;
                        valores->c3Hit++;
                        continue;
                    }
                    else if(cpu->registradores[i].custo == 11100 && cpu->registradores[i].cacheHit == 1){
                        valores->c1Miss++;
                        valores->c2Miss++;
                        valores->c3Miss++;
                        continue;
                    }
                    else if (cpu->registradores[i].custo == 111100 && cpu->registradores[i].cacheHit == 1){ // achou no hd
                        valores->c1Miss++;
                        valores->c2Miss++;
                        valores->c3Miss++;
                        valores->ramMiss++;
                        continue;
                         
                    }
            }
        }
        

            // Executar instrução
            // modifiquei verificar
            if (cpu->opcode == 0) { // Soma
                cpu->registradores[2].palavras[programa[k].endPalavra3] += cpu->registradores[0].palavras[programa[k].endPalavra1] + cpu->registradores[1].palavras[programa[k].endPalavra2];
            } else if (cpu->opcode == 1) { // Subtração
                cpu->registradores[2].palavras[programa[k].endPalavra3] -= cpu->registradores[0].palavras[programa[k].endPalavra1] - cpu->registradores[1].palavras[programa[k].endPalavra2];
            } else if (cpu->opcode == 2) { // interupcao
                // ai chegando aqui o que acontece e que roda se o interuptr de instrucoes
                // e depois volta para o programa
                //printf("!!!!chegou aqui!!!!\n");
                interuptGen();
                int max = 0;
                Instrucao *a = readInstructionsFromFile("interupt.txt", &max);
                RAM_TP2 *ramz = criarRAM (TAM_RAM);
                //executa isntrucoes na cpufake
                CPU *jcpu = criarCPU(16,32,64,N_INST,NUM_CONJUNTOS,VIAS);

                iniciarCPU(jcpu, ramz, a, valores);
                //printf("ACABOU A INTERUPCAO...\n");
                free(a);
                cpu->registradores[2].palavras[programa[k].endPalavra3] += 1;
                cpu->opcode = 0;
                liberarRAM(ramz);
                liberaCUPUAU(jcpu);
                
            } 

            cpu->registradores[2].atualizado = true;
            //possivel timestamp
            cpu->custo += cpu->registradores[0].custo + cpu->registradores[1].custo + cpu->registradores[2].custo;

            cpu->PC++;
            valores->custoFinal+= cpu->custo;
            k++;
        
    }
}

void liberaCUPUAU (CPU*c){
    liberaCache(c->cache1);
    liberaCache(c->cache2);
    liberaCache(c->cache3);
    //free(c->programa);
    //for(int i = 0; i<3; i++)
       // free(c->registradores[i]);
   // free(c->registradores);
    free(c);
    return;
    
}

void imprimeCPU (CPU* c){
    printf ("CPU:\n");
    printf ("PC: %d\n", c->PC);
    printf ("Custo: %d\n", c->custo);
    printf ("Opcode: %d\n", c->opcode);
    printf ("Registradores:\n");
  //  for (int i = 0; i < 3; i++) {
        //printf("Registrador %d: ", i+1);
        //imprimeBloco(*c->registradores[i]);
   // }
}
void imprimeMissAndHit (MissAndHit* m){
    printf ("Miss e Hit:\n");
    printf ("Cache 1: Miss: %d, Hit: %d\n", m->c1Miss, m->c1Hit);
    printf ("Cache 2: Miss: %d, Hit: %d\n", m->c2Miss, m->c2Hit);
    printf ("Cache 3: Miss: %d, Hit: %d\n", m->c3Miss, m->c3Hit);
    printf ("Custo final: %lld\n", m->custoFinal);
    printf ("RAM Miss: %d\n", m->ramMiss);
    printf ("Custo total erros: %d\n", m->c1Miss + m->c2Miss + m->c3Miss + m->ramMiss);
    printf ("Custo total acertos: %d\n", m->c1Hit + m->c2Hit + m->c3Hit); // Custo total de acertos
    printf ("Executado com uma probabilidade de repeticao de: %d\n",N_PROB); // Custo total de acertos e erros
}