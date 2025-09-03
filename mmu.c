#include "mmu.h"
// tudo errado tem que usar o tipo especifico cacheTp2
/*
........
c1 c2 c3 ram

*/

 //ram cahce1 2 3, endereco na ram
 BlocoMemoria buscarMem (RAM_TP2* ram, cacheTP2* cache1, cacheTP2* cache2, cacheTP2* cache3, int endBloco){
    //int custo = 0;
   // printf ("chegou aqui1\n");
    if (cache1->cache_full <= 0){
        BlocoMemoria aux = cache1->conjuntos[0].blocos[0];
        int posicao_remove_conjunto = 0;
        int hold_bloco = 1;
        for (int i = 1; i < cache1->qtd_conjuntos; i++){
            if (aux.timestamp < cache1->conjuntos[i].blocos[0].timestamp ){ // && cache1->conjuntos[i].blocos[0].atualizado == true
                aux=cache1->conjuntos[i].blocos[0];
                posicao_remove_conjunto = i;
                hold_bloco = 0;
            }
            if(aux.timestamp < cache1->conjuntos[i].blocos[1].timestamp ){ // && cache1->conjuntos[i].blocos[1].atualizado == true
                aux=cache1->conjuntos[i].blocos[1];
                posicao_remove_conjunto = i;
                hold_bloco = 1;
            }
        }
        int holdAux = cache1->conjuntos[posicao_remove_conjunto].blocos[hold_bloco].endBloco;
        // funcao mover bloco da chace 1 para cahce 2 (cacheTP2 cahce1, cacheTP2 cache2, Bloco memoria aux, posicao bloco, posicao conjunto)
        //printf ("chegou aqui2\n");
        aux = movCache1Cache2(cache1, cache2, holdAux);
        //printf ("chegou aqui3\n");
        aux.custo = 10;
        return aux;
        
    }
    for (int i = 0; i < cache1->qtd_conjuntos; i++) {
        
        // Iterate through each bloco in the current conjunto
        for (int j = 0; j < cache1->conjuntos[i].qtd_blocos_por_conjunto; j++) {
            // Compare the endBloco with the address in the current bloco
            if (cache1->conjuntos[i].blocos[j].endBloco == endBloco) {
                // Cache hit found
                int custo = 10; // Set the cost for cache hit
                cache1->conjuntos[i].blocos[j].custo = custo;
                cache1->conjuntos[i].blocos[j].cacheHit = 1;  // Mark as cache hit
                return (cache1->conjuntos[i].blocos[j]); // Return the bloco
            }
        }
    }
   // printf ("chegou aqui4\n");
    //___________________________________________________________________________________________

    if (cache2->cache_full <= 0){
        BlocoMemoria aux = cache2->conjuntos[0].blocos[0];
        int posicao_remove_conjunto = 0;
        int hold_bloco = 1;
        for (int i = 1; i < cache2->qtd_conjuntos; i++){
            if (aux.timestamp < cache2->conjuntos[i].blocos[0].timestamp ){ //&& cache2->conjuntos[i].blocos[0].atualizado == true
                aux=cache2->conjuntos[i].blocos[0];
                posicao_remove_conjunto = i;
                hold_bloco = 0;
            }
            if(aux.timestamp < cache2->conjuntos[i].blocos[1].timestamp ){ // && cache2->conjuntos[i].blocos[1].atualizado == true
                aux=cache2->conjuntos[i].blocos[1];
                posicao_remove_conjunto = i;
                hold_bloco = 1;
            }
        }
        int holdAux = cache2->conjuntos[posicao_remove_conjunto].blocos[hold_bloco].endBloco;
        // funcao mover bloco da chace 2 para cahce 3 (cacheTP2 cahce2, cacheTP2 cache3, Bloco memoria aux, posicao bloco, posicao conjunto)
        aux = movCache2Cache3(cache2, cache3, holdAux);
        aux.custo = 110;
        return aux;
    }
    for (int i = 0; i < cache2->qtd_conjuntos; i++) {
        
        // Iterate through each bloco in the current conjunto
        for (int j = 0; j < cache2->conjuntos[i].qtd_blocos_por_conjunto; j++) {
            // Compare the endBloco with the address in the current bloco
            if (cache2->conjuntos[i].blocos[j].endBloco == endBloco) {
                // Cache hit found
                int custo = 110; // Set the cost for cache hit
                cache2->conjuntos[i].blocos[j].custo = custo;
                cache2->conjuntos[i].blocos[j].cacheHit = 1;  // Mark as cache hit
                return (cache2->conjuntos[i].blocos[j]); // Return the bloco
            }
        }
    }
    //printf ("chegou aqui5\n");
    //______________________________________________________

    if (cache3->cache_full <= 0){
        BlocoMemoria aux = cache3->conjuntos[0].blocos[0];
        int posicao_remove_conjunto = 0;
        int hold_bloco = 1;
        for (int i = 1; i < cache3->qtd_conjuntos; i++){
            if (aux.timestamp < cache3->conjuntos[i].blocos[0].timestamp && cache3->conjuntos[i].blocos[0].atualizado == true){
                aux=cache3->conjuntos[i].blocos[0];
                posicao_remove_conjunto = i;
                hold_bloco = 0;
            }
            if(aux.timestamp < cache3->conjuntos[i].blocos[1].timestamp && cache3->conjuntos[i].blocos[1].atualizado == true){
                aux=cache3->conjuntos[i].blocos[1];
                posicao_remove_conjunto = i;
                hold_bloco = 1;
            }
        }
     //   printf ("chegou aqui6\n");
        int holdAux = cache3->conjuntos[posicao_remove_conjunto].blocos[hold_bloco].endBloco;
        // funcao mover bloco da chace 3 para cahce ram (cacheTP2 cahce1, cacheTP2 cache2, Bloco memoria aux, posicao bloco, posicao conjunto)
        aux=movCache3RAM(cache3, ram, holdAux);
        aux.custo = 1110;
        return aux;
    }
    //printf ("chegou aqui7\n");
    for (int i = 0; i < cache3->qtd_conjuntos; i++) {
        
        // Iterate through each bloco in the current conjunto
        for (int j = 0; j < cache3->conjuntos[i].qtd_blocos_por_conjunto; j++) {
            // Compare the endBloco with the address in the current bloco
            if (cache3->conjuntos[i].blocos[j].endBloco == endBloco) {
                // Cache hit found
                int custo = 1110; // Set the cost for cache hit
                cache3->conjuntos[i].blocos[j].custo = custo;
                cache3->conjuntos[i].blocos[j].cacheHit = 1;  // Mark as cache hit
                return (cache3->conjuntos[i].blocos[j]); // Return the bloco
            }
        }
    }
   // printf ("chegou aqui8\n");
    // da ram para cahce 3

    // IF NAO ACHOU NA RAM FAZ ISSO TUDO AQUI
    if (ram->ramFULL <= 0){
        BlocoMemoria aux3 = ram->blocos[0];
        int m;
        for (int i = 1; i < 1000; i++){
            if(ram->blocos[i].timestamp < aux3.timestamp){
                aux3 = ram->blocos[i];
                m = i;
            }
        }

        aux3 = movRAMHD(ram,m);
        aux3.cacheHit =1;
        aux3.custo = 11100;

        return aux3;
    }


    for (int i = 0; i < 1000; i++)
    {
        if (ram->blocos[i].endBloco == endBloco) {
            //printf ("chegou aqui8\n");
            ram->blocos[endBloco%1000].custo = 11100;
            ram->blocos[endBloco%1000].cacheHit = 1;
            //printf ("chegou aqui9\n");
            return ram->blocos[endBloco%1000];
        }
    }
    

    BlocoMemoria aux2;
    //imprimeBloco (aux2);
    aux2 = movHDRAM(ram, endBloco);
    //imprimeBloco (aux2);
    endBloco %= 1000;
    aux2 = movRamCache3(ram, cache3, endBloco);
    //imprimeBloco (aux2);
    aux2 = movCache3Cache2(cache3, cache2,endBloco);
    aux2 = movCache2Cache1(cache2, cache1, endBloco);
    aux2.custo = 111100;
    aux2.cacheHit = 1;

    return aux2;
}


BlocoMemoria movRamCache3(RAM_TP2* ram, cacheTP2* cache3, int endBloco) {
    BlocoMemoria aux = ram->blocos[endBloco];
    int posicaoNaCache3 = endBloco % cache3->qtd_conjuntos;
   // printf("print 1 posicao na cache 3 :%d\n",posicaoNaCache3);
   // printf ("Bloco na ram\n");
   // imprimeBloco(ram->blocos[endBloco]);
    
    cache3->cache_full--;
    
    if(cache3->conjuntos[posicaoNaCache3].blocos->inBloco_zero == false){
        cache3->conjuntos[posicaoNaCache3].blocos[0] = aux;
        cache3->conjuntos[posicaoNaCache3].blocos->inBloco_zero = true;
        cache3->conjuntos[posicaoNaCache3].blocos[0].timestamp = time(NULL);
       //printf("bloco colocado da ram pra ca\n");
        //imprimeBloco (cache3->conjuntos[posicaoNaCache3].blocos[0]);
        return cache3->conjuntos[posicaoNaCache3].blocos[0];
    }
    else{
        cache3->conjuntos[posicaoNaCache3].blocos[1] = aux;
        cache3->conjuntos[posicaoNaCache3].blocos[1].timestamp = time(NULL);
        return cache3->conjuntos[posicaoNaCache3].blocos[1];
    }
    
}
// da cahce 3 pra 2
// ...... ....
BlocoMemoria movCache3Cache2(cacheTP2* cache3, cacheTP2* cache2, int endBloco){
    int posicaoNaCache3 = endBloco % cache3->qtd_conjuntos;
   // printf("posicao na cache 3 :%d\n",posicaoNaCache3);
    int posicaoNaCache2 = endBloco % cache2->qtd_conjuntos;
    cache2->cache_full--;
    cache3->cache_full++;
   // imprimeBloco(cache3->conjuntos[posicaoNaCache3].blocos[0]);
    BlocoMemoria aux;
    if(cache3->conjuntos[posicaoNaCache3].blocos->inBloco_zero == false){
        aux = cache3->conjuntos[posicaoNaCache3].blocos[1];
        aux.timestamp = time(NULL);
        //printf("aquizada");
    }
    else{
       aux = cache3->conjuntos[posicaoNaCache3].blocos[0];
       aux.timestamp = time(NULL);
       //printf("aquizada2");
    }

    if(cache2->conjuntos[posicaoNaCache2].blocos->inBloco_zero == false){
        cache2->conjuntos[posicaoNaCache2].blocos[0] = aux;
        cache2->conjuntos[posicaoNaCache2].blocos->inBloco_zero = true;
        return cache2->conjuntos[posicaoNaCache2].blocos[0];
    }
    else{
        cache2->conjuntos[posicaoNaCache2].blocos[1] = aux;
        cache2->conjuntos[posicaoNaCache2].blocos->inBloco_zero = true;
        return cache2->conjuntos[posicaoNaCache2].blocos[1];
    }

}
// cahce2 -> 1
BlocoMemoria movCache2Cache1(cacheTP2* cache2, cacheTP2* cache1, int endBloco) {
    int posicaoNaCache2 = endBloco % cache2->qtd_conjuntos;
    int posicaoNaCache1 = endBloco % cache1->qtd_conjuntos;
    cache1->cache_full--;
    cache2->cache_full++;
    
    BlocoMemoria aux;
    if(cache2->conjuntos[posicaoNaCache2].blocos->inBloco_zero == false){
        aux = cache2->conjuntos[posicaoNaCache2].blocos[1];
        aux.timestamp=time(NULL);
    }
    else{
        aux = cache2->conjuntos[posicaoNaCache2].blocos[0];
        aux.timestamp=time(NULL);
    }
        

    if(cache1->conjuntos[posicaoNaCache1].blocos->inBloco_zero == false){
        cache1->conjuntos[posicaoNaCache1].blocos[0] = aux;
        cache1->conjuntos[posicaoNaCache1].blocos->inBloco_zero = true;
        return cache1->conjuntos[posicaoNaCache1].blocos[0];
    }
    else{
        cache1->conjuntos[posicaoNaCache1].blocos[1] = aux;
        cache1->conjuntos[posicaoNaCache1].blocos->inBloco_zero = false;
        return cache1->conjuntos[posicaoNaCache1].blocos[1];
    }
    
}

// move cache3 -> cache2


// RAM -> cache3
// verificar 


//Cache1->Cache2
// ...... .....
BlocoMemoria movCache1Cache2(cacheTP2* cache1, cacheTP2* cache2, int endBloco) {
    int posicaoNaCache1 = endBloco % cache1->qtd_conjuntos;
    int posicaoNaCache2 = endBloco % cache2->qtd_conjuntos;
    cache1->cache_full++;
    cache2->cache_full--;
    // if inbloc0 == true entao info existe em bloco 0
    BlocoMemoria aux;
    if(cache1->conjuntos[posicaoNaCache1].blocos->inBloco_zero == false){
        aux = cache1->conjuntos[posicaoNaCache1].blocos[1];
        aux.timestamp=time(NULL);
    }
    else{
        aux = cache1->conjuntos[posicaoNaCache1].blocos[0];
        aux.timestamp=time(NULL);
    }
        
    // true

    if(cache2->conjuntos[posicaoNaCache2].blocos->inBloco_zero == false){
        cache2->conjuntos[posicaoNaCache2].blocos[0] = aux;
        cache2->conjuntos[posicaoNaCache2].blocos->inBloco_zero = true;
        return cache2->conjuntos[posicaoNaCache2].blocos[0];
    }
    else{
        cache2->conjuntos[posicaoNaCache2].blocos[1] = aux;
        cache2->conjuntos[posicaoNaCache2].blocos->inBloco_zero = false;
        return cache2->conjuntos[posicaoNaCache2].blocos[1];
    }
    
}

BlocoMemoria movCache2Cache3(cacheTP2* cache2, cacheTP2* cache3, int endBloco) {
    int posicaoNaCache2 = endBloco % cache2->qtd_conjuntos;
    int posicaoNaCache3 = endBloco % cache3->qtd_conjuntos;
    // if inbloc0 == true entao info existe em bloco 0    
    cache2->cache_full++;
    cache3->cache_full--;
    
    BlocoMemoria aux;
    if(cache2->conjuntos[posicaoNaCache2].blocos->inBloco_zero == false){
        aux = cache2->conjuntos[posicaoNaCache2].blocos[1];
        aux.timestamp=time(NULL);
    }
    else{
        aux = cache2->conjuntos[posicaoNaCache2].blocos[0];
        aux.timestamp=time(NULL);
    }

    if(cache3->conjuntos[posicaoNaCache3].blocos->inBloco_zero == false){
        cache3->conjuntos[posicaoNaCache3].blocos[0] = aux;
        cache3->conjuntos[posicaoNaCache3].blocos->inBloco_zero = true;
        return cache3->conjuntos[posicaoNaCache3].blocos[0];
    }
    else{
        cache3->conjuntos[posicaoNaCache3].blocos[1] = aux;
        cache3->conjuntos[posicaoNaCache3].blocos->inBloco_zero = false;
        return cache3->conjuntos[posicaoNaCache3].blocos[1];
    }

}

// inicializa o timestamp uma vez quando sai da ram
// adicionar timestapm
BlocoMemoria movCache3RAM(cacheTP2* cache3, RAM_TP2* ram, int endBloco){
    int posicaoNaCache3 = endBloco % cache3->qtd_conjuntos;
    BlocoMemoria aux;
    cache3->cache_full++;

    if(cache3->conjuntos[posicaoNaCache3].blocos->inBloco_zero == false){
        aux = cache3->conjuntos[posicaoNaCache3].blocos[1];
        aux.timestamp=time(NULL);
    }
    else{
        aux = cache3->conjuntos[posicaoNaCache3].blocos[0];
        aux.timestamp=time(NULL);
    }
    ram->blocos[endBloco] = aux;
    return aux;
}
// adicinar timestamp
BlocoMemoria movHDRAM(RAM_TP2* ram, int endBloco){
    int posicao_na_ram = endBloco % 1000;
    BlocoMemoria aux;
    FILE *ptr;
    ptr = fopen("hd.bin", "rb");
    fseek(ptr,(endBloco * sizeof(BlocoMemoria)), SEEK_SET);

    fread(&aux, sizeof(BlocoMemoria), 1, ptr);
    fclose (ptr);
    aux.timestamp = time(NULL);
    ram->blocos[posicao_na_ram] = aux;
    ram->ramFULL--;
    return aux;

}

BlocoMemoria movRAMHD(RAM_TP2* ram, int endBloco){
    FILE *ptr;
    ptr = fopen("hd.bin", "wb");

    fseek(ptr,(endBloco * sizeof(BlocoMemoria)), SEEK_SET);
    fwrite(&ram->blocos[endBloco], sizeof(BlocoMemoria), 1, ptr);

    fclose(ptr);
    ram->ramFULL++;
    return ram->blocos[endBloco];
}