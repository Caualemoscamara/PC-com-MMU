#include "ramTP.h"

cacheTP2* criarCache(int tamanho_cache, int num_conjuntos, int vias) {
    // Aloca espaço pra cache
    cacheTP2* c = malloc(sizeof(cacheTP2));
    c->qtd_conjuntos = num_conjuntos;
    c->total_blocos = tamanho_cache;
    c->custo_total = 0;
    c->cache_full = tamanho_cache*2;

    // Aloca espaço pros conjuntos
    c->conjuntos = malloc(num_conjuntos * sizeof(ConjuntoCache));

    //cada conjunto aloca espaço pros blocos
    for (int i = 0; i < num_conjuntos; i++) {
        c->conjuntos[i].qtd_blocos_por_conjunto = vias;
        c->conjuntos[i].blocos = malloc(vias * sizeof(BlocoMemoria));

        c->conjuntos[i].blocos->inBloco_zero = false;  // bloco está vazio
        }
    

    return c;
}

void liberaCache(cacheTP2 *c){
   
    for (int i = 0; i < c->qtd_conjuntos; i++)
        free(c->conjuntos[i].blocos);
    
    free (c->conjuntos);
    free(c);
   
    return;
}

// ram alocada 
RAM_TP2* criarRAM(int tamanhoRam) {
    // Aloca a estrutura da RAM
    RAM_TP2* ram = malloc(sizeof(RAM_TP2));
    //if (ram == NULL) return NULL; // Verifica erro de alocação
    
    // Define o tamanho da RAM
    ram->tamanhoRam = tamanhoRam;
    ram->ramFULL = tamanhoRam;

    // Aloca os blocos de memória da RAM
    ram->blocos = malloc(tamanhoRam * sizeof(BlocoMemoria));
    if (ram->blocos == NULL) {
        //free(ram); // Libera a RAM caso falhe a alocação dos blocos
        // pode dar falha de segmentacao tentar liberar algo que nao foi alocado
       // return NULL;
    }

    return ram;
}

void liberarRAM(RAM_TP2* ram) {
    if (ram == NULL) return;//pode dar erro 
    
    free(ram->blocos);
    free(ram);
}


void inicializarRAM(RAM_TP2* ram) {
    if (ram == NULL) return;

    srand(time(NULL));

    for (int i = 0; i < ram->tamanhoRam; i++) {
        ram->blocos[i].endBloco = i; // O endereço do bloco é seu índice na RAM
        ram->blocos[i].cacheHit = 0;
        ram->blocos[i].custo = 0;
        ram->blocos[i].atualizado = false;

        int palavra_num_atual = rand();
        // Inicializa os dados das palavras dentro do bloco
        for (int j = 0; j < TAM_PALAVRAS; j++) {
            ram->blocos[i].palavras[j] = palavra_num_atual+j;  // Pode ser alterado conforme necessidade
        }
    }
}



void imprimeBloco(BlocoMemoria bloco){
    int aux1, aux2, aux3;
    aux1 = bloco.cacheHit;
    aux2 = bloco.custo;
    aux3 = bloco.endBloco;

    printf("valor de cache hit atual: %d, custo atual do bloco: %d, endereco do bloco solicitado %d \n", aux1, aux2, aux3);

    for (int i = 0; i < TAM_PALAVRAS; i++){
        printf("Palavra[%d]: %d\n",i,bloco.palavras[i]);
    }
}

void imprimeRamTp2 (RAM_TP2*r){
    for(int i = 0; i < r->tamanhoRam; i++){
        imprimeBloco(r->blocos[i]);
    }
    return;
}