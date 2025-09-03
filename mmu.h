
#ifndef MMU_H
#define MMU_H

#include "ramTP.h"

BlocoMemoria buscarMem (RAM_TP2* , cacheTP2* , cacheTP2* , cacheTP2* , int );
BlocoMemoria movRamCache3(RAM_TP2* , cacheTP2* , int );
BlocoMemoria movCache3Cache2(cacheTP2* , cacheTP2* , int );
BlocoMemoria movCache2Cache1(cacheTP2* , cacheTP2* , int );
BlocoMemoria movCache1Cache2(cacheTP2* , cacheTP2* , int );
BlocoMemoria movCache2Cache3(cacheTP2* , cacheTP2* , int );
BlocoMemoria movCache3RAM(cacheTP2* , RAM_TP2* , int );


// nova

BlocoMemoria movHDRAM(RAM_TP2* , int );
BlocoMemoria movRAMHD(RAM_TP2* , int );

#endif