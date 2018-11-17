//test_mouvement_SSE2.c
#include <stdio.h>
#include <stdlib.h>
#include "test_mouvement_SSE2.h"
#include "mouvement_SSE2.h"


#define BORD 2
#define NUMBER_IMAGES 299
#define VMIN 20
#define VMAX 240


void test_unitaire_FrameDifference_SSE2(){
    puts("---------------------------------------");
    puts("-- test_unitaire_FrameDifference_SSE2 --");
    puts("---------------------------------------");


    //Test lorsque le seuil = 20
    vuint8 pixelTest1 = init_vuint8_all(120, 130, 120, 130, 120, 130, 244, 255, 15, 223, 158, 35, 180, 254, 10, 2);
    vuint8 pixelTest2 = init_vuint8_all(100, 150, 141, 149, 99, 111, 20, 0, 15, 223, 159, 160, 255, 220, 10, 1);
    //OtTest = abs(pixelTest1 -pixelTest2)
    vuint8 OtTest = init_vuint8_all(20, 20, 21, 19, 21, 19, 224, 255, 0, 0, 1, 125, 75, 34, 0, 1);
    vuint8 EtTest = init_vuint8_all(255, 255, 255, 0, 255, 0, 255, 255, 0, 0, 0, 255, 255, 255, 0, 0);


    vuint8 min = _mm_min_epu8(pixelTest1, pixelTest2);
    vuint8 max = _mm_max_epu8(

}



void test_unitaire_SigmaDelta_SSE2(){


}


