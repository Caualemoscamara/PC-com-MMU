#include "ramTP.h"
#include "leituraInstrucao.h"
#include "gerarInst.h"
#include "mmu.h"
#include "cpu.h"
#include"geradorHD.h"

#define NUMERO_BLOCOS_HD 3000

int main () {
    instGenerator();
    int instrucoesLidas = 0;
    Instrucao *a = readInstructionsFromFile ("programa.txt", &instrucoesLidas);
    

    printf ("Instrucoes lidas: %d\n", instrucoesLidas);
    criarHD(NUMERO_BLOCOS_HD);
    // ram 100
    RAM_TP2 *r = criarRAM (TAM_RAM);
    //inicializarRAM (r);
    MissAndHit *m = valoresInicia ();
    
    CPU *c = criarCPU (16,32,64,N_INST,NUM_CONJUNTOS,VIAS);

   // imprimeCPU (c);
    //imprimeMissAndHit (m);
    //BlocoMemoria aux5 = movHDRAM (r,3000);
    //imprimeBloco(aux5);
    
    iniciarCPU(c, r, a, m);

    printf("M5:\n");
    imprimeCPU (c);
    imprimeMissAndHit (m);
    // Libera a porra toda
    liberaValores(m);
    liberaCUPUAU (c);
    liberarRAM(r);
    libera_vetor_instuct (a);
    /*
    inicializarRAM (r);
    MissAndHit *m = valoresInicia ();
  //  imprimeRamTp2(r);

    CPU *c = criarCPU (16,24,32,N_INST,NUM_CONJUNTOS,VIAS);
    // programa que chama o inicia cpu
   
    
    //funcao para imprimir o miss e o hit
    imprimeMissAndHit (m);
    imprimeCPU (c);

    // librea toda memoria alocada
    liberaCUPUAU (c);
    liberarRAM(r);
    liberaValores(m);
    libera_vetor_instuct (a);
    */

    return 0;

}

