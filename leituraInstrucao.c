#include "leituraInstrucao.h"

#define N_INST 1000 // Number of instructions (based on your initial comment)

Instrucao* readInstructionsFromFile(const char* filename, int* numInstructions) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return NULL;
    }

    Instrucao* instructions = malloc((N_INST+1) * sizeof(Instrucao));
    if (instructions == NULL) {
        printf("Memory allocation failed.\n");
        fclose(file);
        return NULL;
    }

    int i = 0;
    while (i < N_INST && fscanf(file, "%d:%d:%d:%d:%d:%d:%d\n",
            &instructions[i].opcode, &instructions[i].add1,
            &instructions[i].endPalavra1, &instructions[i].add2,
            &instructions[i].endPalavra2, &instructions[i].add3,
            &instructions[i].endPalavra3) == 7) {
        i++;
    }
    

    *numInstructions = (i+1);

    fscanf(file, "%d", &instructions[i].opcode);

    fclose(file);
   
    return instructions;
}
/*
int main() {
    int numInstructions = 0;
    Instrucao* instructions = readInstructionsFromFile("programa.txt", &numInstructions);

    if (instructions != NULL) {
        printf("Instructions read: %d\n", numInstructions);

        // For testing: print the instructions
        for (int i = 0; i < numInstructions; i++) {
            printf("Instrucao %d: add1=%d, endBloco1=%d, add2=%d, endBloco2=%d, add3=%d, endBloco3=%d, opcode=%d\n",
                i, instructions[i].add1, instructions[i].endBloco1, instructions[i].add2,
                instructions[i].endBloco2, instructions[i].add3, instructions[i].endBloco3, instructions[i].opcode);
        }

        // Free the memory allocated for instructions
        free(instructions);
    }

    return 0;
}
*/
void libera_vetor_instuct (Instrucao* a){
    free (a);
    return;
}