#include "geradorHD.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define N_INST2 100 //numero de instrucoes
#define N_FOR2 5     //numero de instrucoes que vao se repetir
#define N_MEM2 3000  //numero da memoria para endereco do bloco
#define N_PROB2 90   //probabilidade de repeticao
#define N_OPCODE2 2  //numero maximo de opcodes
#define N_WORD2 4    //numero de palavras no bloco


void criarHD(int nBlocos){
    FILE *arquivo = fopen("hd.bin", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    


    srand(time(NULL));
    BlocoMemoria bloco;
    for (int i = 0; i < nBlocos; i++) {
        bloco.endBloco = i;
        bloco.custo = 0; 
        bloco.cacheHit = 0;
        bloco.palavras[0] = rand(); // Preencher com valores aleatórios
        for(int j = 1; j < 4; j++) {
            bloco.palavras[j] += (1 + bloco.palavras[0]);
        }
        bloco.atualizado = false; // Inicializa como não atualizado
        
        size_t result = fwrite(&bloco, sizeof(BlocoMemoria), 1, arquivo);
        if (result != 1) {
            printf("Erro ao escrever o bloco no arquivo.\n");
            fclose(arquivo);
            return;
        }
    }

    fclose(arquivo);
}







void interuptGen(void){
    int rep[5][7];
    int inst[10000][7];

        FILE *arquivo = fopen("interupt.txt", "w");
        int endOpCode = -1;
        int random;
        int instruc[8] = {6, 6, 6, 6, 6, 6, 6, 6};
        
        srand(time(NULL));
    
        for (int i = 0; i < N_FOR2; i++) {
            random = rand() % N_OPCODE2;
            rep[i][0] = random;
            for (int j = 1; j <= (instruc[random]); j += 2) {
                rep[i][j] = rand() % N_MEM2;
                rep[i][j + 1] = rand() % N_WORD2;
            }
        }
    
        for (int i = 0; i < N_INST2;) {
            random = (rand() % 100) + 1;
            if (random <= N_PROB2 && i + N_FOR2 < N_INST2) {
                for (int j = 0; j < N_FOR2; j++) {
                    for (int k = 0; k < 7; k++) {
                        inst[i + j][k] = rep[j][k];
                    }
                }
                i += N_FOR2;
            } else {
                random = rand() % N_OPCODE2;
                inst[i][0] = random;
                for (int j = 1; j <= instruc[random]; j += 2) {
                    inst[i][j] = rand() % N_MEM2;
                    inst[i][j + 1] = rand() % N_WORD2;
                }
                i++;
            }
        }
    
        for (int i = 0; i < N_INST2; i++) {
            for (int k = 0; k < 6; k++) {
                fprintf(arquivo, "%d:", inst[i][k]);
            }
            fprintf(arquivo, "%d\n", inst[i][6]);
        }
        fprintf(arquivo,"%d\n",endOpCode);
    
        fclose(arquivo);
    
}
