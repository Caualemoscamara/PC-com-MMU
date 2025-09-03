#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "gerarInst.h"
#include "ramTP.h"

int rep[5][7];
int inst[10000][7];

void instGenerator () {
    FILE *arquivo = fopen("programa.txt", "w");
    int endOpCode = -1;
    int random;
    int instruc[8] = {6, 6, 6, 6, 6, 6, 6, 6};
    
    srand(time(NULL));

    for (int i = 0; i < N_FOR; i++) {
        random = rand() % N_OPCODE;
        rep[i][0] = random;
        for (int j = 1; j <= (instruc[random]); j += 2) {
            rep[i][j] = rand() % N_MEM;
            rep[i][j + 1] = rand() % N_WORD;
        }
    }

    for (int i = 0; i < N_INST;) {
        random = (rand() % 100) + 1;
        if (random <= N_PROB && i + N_FOR < N_INST) {
            for (int j = 0; j < N_FOR; j++) {
                for (int k = 0; k < 7; k++) {
                    inst[i + j][k] = rep[j][k];
                }
            }
            i += N_FOR;
        } else {
            random = rand() % N_OPCODE;
            inst[i][0] = random;
            for (int j = 1; j <= instruc[random]; j += 2) {
                inst[i][j] = rand() % N_MEM;
                inst[i][j + 1] = rand() % N_WORD;
            }
            i++;
        }
    }

    for (int i = 0; i < N_INST; i++) {
        for (int k = 0; k < 6; k++) {
            fprintf(arquivo, "%d:", inst[i][k]);
        }
        fprintf(arquivo, "%d\n", inst[i][6]);
    }
    fprintf(arquivo,"%d\n",endOpCode);

    fclose(arquivo);
}

/*

void instGenerator() {
    FILE *arquivo = fopen("programa.txt", "w");

    if (arquivo == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    int random;
    int instruc[8] = {6, 6, 6, 6, 6, 6, 6, 6}; // Example instruction sizes (just as in your original code)
    
    srand(time(NULL));

    // Generating instructions with opcodes restricted to 0, 1, and -1
    for (int i = 0; i < N_INST; i++) {
        random = rand() % 3 - 1; // Random value between -1 and 1 (inclusive)

        // Ensure opcode is between 0 and 1 or -1
        int opcode = (random == -1) ? -1 : (random % 2); // Limiting opcode to 0, 1, or -1
        
        // Write the instruction line to the file
        // jautar com tamanho da ram
        fprintf(arquivo, "%d:%d:%d:%d:%d:%d:%d\n", 
                rand() % 1000, rand() % 1000, rand() % 1000, rand() % 1000, 
                rand() % 1000, rand() % 1000, opcode);
    }

    fclose(arquivo);
}

*/

/*
// lidando com o opcode
void instGenerator() {
    FILE *arquivo = fopen("programa.txt", "w");

    if (arquivo == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    int random;
    int instruc[8] = {6, 6, 6, 6, 6, 6, 6, 6}; // Example instruction sizes (just as in your original code)

    srand(time(NULL));

    // Generating instructions with opcodes restricted to 0, 1 for all but the last one
    for (int i = 0; i < N_INST; i++) {
        // For all but the last instruction, opcode can be either 0 or 1
        int opcode = (i == N_INST - 1) ? -1 : (rand() % 2); // Last instruction gets opcode = -1

        // Write the instruction line to the file
        fprintf(arquivo, "%d:%d:%d:%d:%d:%d:%d\n", 
                abs(rand() % 1000), abs(rand() % 4), abs(rand() % 1000), abs(rand() % 4), 
                abs(rand() % 1000), abs(rand() % 4), opcode);
    }

    fclose(arquivo);
}


*/