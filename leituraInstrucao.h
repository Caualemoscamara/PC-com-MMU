#ifndef LEITURAINSTRUCAO_H
#define LEITURAINSTRUCAO_H

#include "ramTP.h"

Instrucao* readInstructionsFromFile(const char* filename, int* numInstructions); // change
void libera_vetor_instuct (Instrucao* a);

#endif // LEITURAINSTRUCAO_H!