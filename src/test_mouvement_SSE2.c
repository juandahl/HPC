//test_mouvement_SSE2.c
#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"
#include "vnrutil.h"

#include "mymacro.h"
#include "test_mouvement_SSE2.h"
#include "mouvement_SSE2.h"


#define BORD 2
#define NUMBER_IMAGES 299
#define VMIN 20
#define VMAX 240
#define N 2


void test_unitaire_FrameDifference_SSE2(){
    puts("****************************************");
    puts("** test_unitaire_FrameDifference_SSE2 **");
    puts("****************************************");

    vuint8 tmpOt;
    vuint8 signe = init_vuint8(128);
    vuint8 whitePixel = init_vuint8(255);

    //Test lorsque le seuil = 20
    vuint8 thresholdTest = init_vuint8(20);
    vuint8 pixelTest1 = init_vuint8_all(120, 130, 120, 130, 120, 130, 244, 255, 15, 223, 158, 35, 180, 254, 10, 2);
    vuint8 pixelTest2 = init_vuint8_all(100, 150, 141, 149, 99, 111, 20, 0, 15, 223, 159, 160, 255, 220, 10, 1);
    //OtTest = abs(pixelTest1 -pixelTest2)
    vuint8 OtTest = init_vuint8_all(20, 20, 21, 19, 21, 19, 224, 255, 0, 0, 1, 125, 75, 34, 0, 1);
    vuint8 EtTest = init_vuint8_all(255, 255, 255, 0, 255, 0, 255, 255, 0, 0, 0, 255, 255, 255, 0, 0);


    vuint8 minI = _mm_min_epu8(pixelTest1, pixelTest2);
    vuint8 maxI = _mm_max_epu8(pixelTest1, pixelTest2);
	
    tmpOt = _mm_sub_epi8(maxI, minI);
    display_vuint8(OtTest, " %d ", "Ot Test\t\t");
    printf("\n");
    display_vuint8(tmpOt, " %d ", "Ot result\t");
    printf("\n\n");

    vuint8 result = _mm_cmplt_epi8(_mm_sub_epi8(OtTest, signe), _mm_sub_epi8(thresholdTest, signe)); //Met 255 si inferieur au seuil et 0 sinon
    display_vuint8(EtTest," %d ", "Et Test\t\t");
    printf("\n");
    /*display_vuint8(result, " %d ", "Et result\t");
    printf("\n");*/

    result = _mm_andnot_si128(result, whitePixel);
    display_vuint8(result," %d ", "Et Result\t");
    printf("\n");
}





void test_unitaire_SigmaDelta_SSE2(){

    puts("***********************************");
    puts("** test_unitaire_SigmaDelta_SSE2 **");
    puts("***********************************");

    vuint8 It = init_vuint8_all(255, 0, 1, 0, 162, 10, 158, 23, 200, 255, 254, 70, 56, 30, 7, 98); 

    vuint8 Mt0 = init_vuint8_all(255, 0, 0, 1, 161, 8, 160, 26, 200, 254, 255, 65, 57, 35, 24, 90);
    vuint8 MtTest;
    vuint8 one = init_vuint8(1);
    vuint8 signe = init_vuint8(128);

////////////////////////step1////////////////////

    printf("*********** Step 1 ***********\n");
    display_vuint8(It," %d ","It\t");
    printf("\n");
    display_vuint8(Mt0," %d ","Mt0\t");
    printf("\n\n");


    vuint8 Mt0Add1 = _mm_add_epi8(Mt0, one); //Mt0 + 1
    vuint8 Mt0Sub1 = _mm_sub_epi8(Mt0, one); //Mt0 - 1

    //if Mt0 < It
    vuint8 result = _mm_cmplt_epi8(_mm_sub_epi8(Mt0, signe), _mm_sub_epi8(It, signe));
    MtTest = _mm_or_si128(_mm_and_si128(result, Mt0Add1), _mm_andnot_si128(result, Mt0)); 

    //if Mt0 > It
    result = _mm_cmpgt_epi8(_mm_sub_epi8(Mt0, signe), _mm_sub_epi8(It, signe));
    MtTest = _mm_or_si128(_mm_and_si128(result, Mt0Sub1), _mm_andnot_si128(result, MtTest));

    display_vuint8(MtTest, " %d ","Mt  \t");
    printf("\n");

    printf("Mt attendu 255  0  1  0  162  9  159  25  200  255  254  66  56  34  23  91\n\n");

////////////////////////step2////////////////////

    printf("*********** Step 2 ***********\n");

    It = init_vuint8_all(120, 130, 120, 130, 120, 130, 244, 255, 15, 223, 158, 35, 180, 254, 10, 2);
    MtTest = init_vuint8_all(100, 150, 141, 149, 99, 111, 20, 0, 15, 223, 159, 160, 255, 220, 10, 1);

    vuint8 max = _mm_max_epu8(It,MtTest);
    vuint8 min = _mm_min_epu8(It, MtTest);
    //abs(tmpMt - It)
    vuint8 OtTest = _mm_sub_epi8(max, min);

    display_vuint8(It," %d ","It\t");
    printf("\n");
    display_vuint8(MtTest," %d ","Mt\t");
    printf("\n\n");
    display_vuint8(OtTest, " %d ","Ot\t");
    printf("\n");
    printf( "Ot attendu 20  20  21  19  21  19  224  255  0  0  1  125  75  34  0  1\n\n");

////////////////////////step3////////////////////

    printf("*********** Step 3 update ***********\n");

    OtTest = init_vuint8_all(20, 20, 21, 19, 21, 19, 224, 255, 0, 0, 1, 125, 75, 34, 0, 1);

    vuint8 NTimesOt = init_vuint8(0);

    for(int x = 0; x < N; x++)
    {
        NTimesOt = _mm_adds_epu8(NTimesOt, OtTest);
    }
    display_vuint8(OtTest, " %d ","Ot\t\t");
    printf("\n");
    display_vuint8(NTimesOt, " %d ","2*Ot\t\t");
    printf("\n");

    printf("NTimesOt attendu 40  40  42  38  42  38  255  255  0  0  2  250  150  68  0  2\n\n");

    printf("*********** Step 3 clamping ***********\n");

    vuint8 VMAXSIMD = init_vuint8(VMAX);
    vuint8 VMINSIMD = init_vuint8(VMIN);

    vuint8 VtTest = init_vuint8_all(80, 0, 20, 19, 18, 54, 98, 158,  210,  251, 255,  130, 101, 129,  201, 125);

    vuint8 VtResult = _mm_max_epu8(_mm_min_epu8(VtTest, VMAXSIMD), VMINSIMD);

    display_vuint8(VtTest, " %d ","Vt_Init\t\t");
    printf("\n");

    display_vuint8(VtResult, " %d ","Vt calculé\t");
    printf("\n");

    printf("Vt attendu	 80  20  20  20  20  54  98  158  210  240  240  130  101  129  201  125\n\n");


    printf("*********** Step 4 ***********\n");

    vuint8 whitePixel = init_vuint8(255);

    OtTest = init_vuint8_all(10, 108, 202, 64, 128, 60, 90, 255, 0, 255, 0,  187, 209, 80, 18, 166);
    VtTest = init_vuint8_all(10, 107, 203, 64, 128, 50, 50, 0, 255, 255, 0, 177, 208, 88, 19, 166);

    result = _mm_cmplt_epi8(_mm_sub_epi8(OtTest, signe), _mm_sub_epi8(VtTest, signe)); 
    result = _mm_andnot_si128(result, whitePixel);

    display_vuint8(OtTest," %d ", "Ot\t");
    printf("\n");
    display_vuint8(VtTest, " %d ", "Vt\t");
    printf("\n");

    display_vuint8(result," %d ", "Et\t");
    printf("\n");

    printf("Et attendu 255  255  0  255  255  255  255  255  0  255  255  255  255  0  0  255\n\n");

}


