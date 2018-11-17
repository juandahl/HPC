
//bench_mouvement_SSE2.c
#include <stdio.h>
#include <stdlib.h>
#include "vnrdef.h"
#include "vnrutil.h"
#include "nrdef.h"
#include "nrutil.h"
#include "mouvement_SSE2.h"
#include "mymacro.h"
#include "bench_mouvement_SSE2.h"

#define BORD 2
#define NUMBER_IMAGES 299
#define VMIN 20
#define VMAX 240


void getMatrixSIMD(vuint8 **vX1, uint8 **Itm1, int vi0, int vi1, int vj0, int vj1)
{
    vuint8 x;
    vuint8 T[1];
    uint8 *p = (uint8*) T;
    int cpt = 0;

    for(int i = vi0; i <=vi1; i++)
    {
        for(int j = vj0; j <= vj1; j++)
        {
            for(int k = 0; k < 16; k++)
            {
                p[k] = Itm1[i][j*16+k];
            }
            vX1[i][j] = T[0];
        }
    }
}

void getMatrixNum(vuint8 **vX1, uint8 **Itm1, int vi0, int vi1, int vj0, int vj1)
{
    vuint8 T[1];
    vuint8 x;

    uint8 *p = (uint8*) T;
    int cpt = 0;

    for(int i = vi0; i <=vi1; i++)
    {
        for(int j = vj0; j <= vj1; j++)
        {
            x = _mm_load_si128(&vX1[i][j]);
            _mm_store_si128(T, x);
            for(int k = 0; k < 16; k++)
            {
                Itm1[i][j*16+k] = p[k];
            }
        }
    }
}

void test_routine_FrameDifference_SSE2(int threshold)
{
    puts("---------------------------------------");
    puts("-- test_routine_FrameDifference_SSE2 --");
    puts("---------------------------------------");
    //initialisation des variables
    char imagePath[50];
    char outputPath[50];
    char initialImagePath[50] = "hall/hall000000.pgm";

    double numcycles, totalCycle = 0;
    char *format = "%6.2f \n";
    int iter, niter = 2;
    int run, nrun = 5;
    double t0, t1, dt, tmin, t;
    long nrl, nrh, ncl, nch; // variables needed to load images
    vuint8 vthreshold = init_vuint8(threshold);

    // ------------ //
    // -- calcul -- //
    // ------------ //

    //load image ui8 format
    uint8 **I0 =  LoadPGM_ui8matrix(initialImagePath, &nrl, &nrh, &ncl, &nch);
    uint8 **It = ui8matrix(nrl, nrh, ncl, nch);
    uint8 **Et = ui8matrix(nrl, nrh, ncl, nch);

    //vector initialization
    vuint8 ** vI0 = vui8matrix_s(nrl, nrh, ncl, nch); 
    vuint8 ** vIt = vui8matrix_s(nrl, nrh, ncl, nch); 
    vuint8 ** vEt = vui8matrix_s(nrl, nrh, ncl, nch);

    // 

    //convert matrix uint8 to vector
    int vnrl, vnrh, vncl, vnch; 
    s2v(nrl, nrh, ncl, nch, 16, &vnrl, &vnrh, &vncl, &vnch);
    getMatrixSIMD(vI0, I0,  vnrl, vnrh, vncl, vnch);

    for(int i = 1; i <= NUMBER_IMAGES; i++)
    {
        sprintf(imagePath, "hall/hall000%03d.pgm", i);
	    It = LoadPGM_ui8matrix(imagePath, &nrl, &nrh, &ncl, &nch);
        getMatrixSIMD(vIt, It,  vnrl, vnrh, vncl, vnch);

        CHRONO(routine_FrameDifference_SSE2(vIt, vI0, vEt, vnrl, vnrh, vncl, vnch, vthreshold), numcycles);        
        totalCycle+=numcycles;

        //update Its 
        dup_vui8matrix(vIt, vnrl, vnrh, vncl, vnch, vI0);

        //Save the image
        sprintf(outputPath, "FrameDifference/hall000%03d.pgm", i-1);
        getMatrixNum(vEt, Et, vnrl, vnrh, vncl, vnch);
        SavePGM_ui8matrix(Et, nrl, nrh, ncl, nch, outputPath);
    }

    // -------------- //
    // -- Results -- //
    // ------------- //
    BENCH(printf("Cycles Total FrameDifference = "));
    BENCH(printf("%6.2f\n", totalCycle));

    BENCH(printf("Cycles per image FrameDifference = "));
    BENCH(printf("%6.2f\n", totalCycle / NUMBER_IMAGES));

    BENCH(printf("Cycles per pixel FrameDifference = "));
    BENCH(printf("%6.2f\n", totalCycle / ((nch+1)*(nrh+1))));


    compare_with_ground_truth("FrameDifference");

    // ---------- //
    // -- free -- //
    // ---------- //
    free_ui8matrix(I0, nrl, nrh, ncl, nch );

    free_vui8matrix(vI0, vnrl, vnrh, vncl, vnch);
    free_vui8matrix(vIt, vnrl, vnrh, vncl, vnch);
    free_vui8matrix(vEt, vnrl, vnrh, vncl, vnch);

}

void test_routine_SigmaDelta_SSE2(){

    puts("----------------------------------");
    puts("-- test_routine_SigmaDelta_SSE2 --");
    puts("----------------------------------");

    //Inicialization variables
    //cycles variables
    double cycles;

    char *format = "%6.2f \n";
    double cycleTotal = 0;
    int iter, niter = 2;
    int run, nrun = 5;
    double t0, t1, dt, tmin, t;

    char imagePath[50];
    char outputPath[50];
    long nrl, nrh, ncl, nch; // variables needed to load images
    double numCycles, totalCycles = 0; //cycles counters 
    char initialImagePath[50] = "hall/hall000000.pgm"; 
    
    //inicial matrix(step 0)
    uint8** It1 = LoadPGM_ui8matrix(initialImagePath, &nrl, &nrh, &ncl, &nch);

    uint8 **Mt1 =  ui8matrix(nrl, nrh, ncl, nch);
    uint8 **Vt1 =  ui8matrix(nrl, nrh, ncl, nch);

    //initial matrix (step1)
    uint8 **It = ui8matrix(nrl, nrh, ncl, nch);
    uint8 **Et = ui8matrix(nrl, nrh, ncl, nch);
    uint8 **Mt =  ui8matrix(nrl, nrh, ncl, nch);
    uint8 **Vt =  ui8matrix(nrl, nrh, ncl, nch);

    //vector initialization
    int vnrl, vnrh, vncl, vnch; 
    s2v(nrl, nrh, ncl, nch, 16, &vnrl, &vnrh, &vncl, &vnch); 

    //inicial matrix(step 0)
    vuint8** vIt1 = LoadPGM_ui8matrix(initialImagePath, &nrl, &nrh, &ncl, &nch);

    vuint8 ** vMt1 =  vui8matrix_s(nrl, nrh, ncl, nch);
    vuint8 ** vVt1 =  vui8matrix_s(nrl, nrh, ncl, nch);

    //initial matrix (step1)
    vuint8 ** vIt = vui8matrix_s(nrl, nrh, ncl, nch);
    vuint8 ** vEt = vui8matrix_s(nrl, nrh, ncl, nch);
    vuint8 ** vMt = vui8matrix_s(nrl, nrh, ncl, nch);
    vuint8 ** vVt = vui8matrix_s(nrl, nrh, ncl, nch);


    // ------------ //
    // -- calcul -- //
    // ------------ //
    getMatrixSIMD(vIt1, It, vnrl, vnrh, vnrl, vnrh);    
    CHRONO( routine_SigmaDelta_step0_initialisation(vIt1, vMt1, vVt1, vnrl, vnrh, vncl, vnch), cycles);
    totalCycles = totalCycles + cycles;


    for(int i = 1; i <= NUMBER_IMAGES; i++)
    {
        sprintf(imagePath, "hall/hall000%03d.pgm", i );        

        It = LoadPGM_ui8matrix(imagePath, &nrl, &nrh, &ncl, &nch);
        getMatrixSIMD(vIt, It, vnrl, vnrh, vncl, vnch );

        CHRONO(routine_SigmaDelta_step1_SSE2(vIt, vVt1, vVt, vMt1, vMt, vEt, vVt, vnrl, vnrh, vncl, vnch), cycles);
        totalCycles = totalCycles + cycles;

        getMatrixNum(vEt, Et, vnrl, vnrh, vncl, vnch);

        sprintf(outputPath,"SigmaDelta/hall000%03d.pgm",i-1);
        SavePGM_ui8matrix(Et, nrl, nrh, ncl, nch, outputPath);
        
        //update state of matrix
        dup_vui8matrix(vMt, vnrl, vnrh, vncl, vnch, vMt1);
        dup_vui8matrix(vVt, vnrl, vnrh, vncl, vnch, vVt1);
        dup_vui8matrix(vIt, vnrl, vnrh, vncl, vnch, vIt1);
    }

    // -------------- //
    // -- Results -- //
    // ------------- //
    BENCH(printf("Cycles Total Sigma Delta = "));
    BENCH(printf("%6.2f\n", totalCycles));

    BENCH(printf("Cycles per image Sigma Delta = "));
    BENCH(printf("%6.2f\n", totalCycles / NUMBER_IMAGES));

    BENCH(printf("Cycles per pixel Sigma Delta = "));
    BENCH(printf("%6.2f\n", totalCycles / ((nch+1)*(nrh+1))));

    compare_with_ground_truth("SigmaDelta");

    // ---------- //
    // -- free -- //
    // ---------- //
    free_ui8matrix(It1, nrl, nrh, ncl, nch );
    free_ui8matrix(Mt1, nrl, nrh, ncl, nch );
    free_ui8matrix(Vt1, nrl, nrh, ncl, nch );

    free_ui8matrix(It, nrl, nrh, ncl, nch );
    free_ui8matrix(Mt, nrl, nrh, ncl, nch );
    free_ui8matrix(Vt, nrl, nrh, ncl, nch );
    free_ui8matrix(Et, nrl, nrh, ncl, nch );
}

void test_routine_FrameDifference_SSE2_thread(int threshold)
{
    puts("---------------------------------------");
    puts("-- test_routine_FrameDifference_SSE2 --");
    puts("---------------------------------------");
    //initialisation des variables
    char imagePath[50];
    char outputPath[50];
    char initialImagePath[50] = "hall/hall000000.pgm";

    double numcycles, totalCycle = 0;
    char *format = "%6.2f \n";
    int iter, niter = 2;
    int run, nrun = 5;
    double t0, t1, dt, tmin, t;
    long nrl, nrh, ncl, nch; // variables needed to load images
    vuint8 vthreshold = init_vuint8(threshold);

    // ------------ //
    // -- calcul -- //
    // ------------ //

    //load image ui8 format
    uint8 **I0 =  LoadPGM_ui8matrix(initialImagePath, &nrl, &nrh, &ncl, &nch);
    uint8 **It = ui8matrix(nrl, nrh, ncl, nch);
    uint8 **Et = ui8matrix(nrl, nrh, ncl, nch);

    //vector initialization
    vuint8 ** vI0 = vui8matrix_s(nrl, nrh, ncl, nch); 
    vuint8 ** vIt = vui8matrix_s(nrl, nrh, ncl, nch); 
    vuint8 ** vEt = vui8matrix_s(nrl, nrh, ncl, nch);

    // 

    //convert matrix uint8 to vector
    int vnrl, vnrh, vncl, vnch; 
    s2v(nrl, nrh, ncl, nch, 16, &vnrl, &vnrh, &vncl, &vnch);
    getMatrixSIMD(vI0, I0,  vnrl, vnrh, vncl, vnch);

    for(int i = 1; i <= NUMBER_IMAGES; i++)
    {
        sprintf(imagePath, "hall/hall000%03d.pgm", i);
	    It = LoadPGM_ui8matrix(imagePath, &nrl, &nrh, &ncl, &nch);
        getMatrixSIMD(vIt, It,  vnrl, vnrh, vncl, vnch);

        CHRONO(routine_FrameDifference_SSE2_thread(vIt, vI0, vEt, vnrl, vnrh, vncl, vnch, vthreshold), numcycles);        
        totalCycle+=numcycles;

        //update Its 
        dup_vui8matrix(vIt, vnrl, vnrh, vncl, vnch, vI0);

        //Save the image
        sprintf(outputPath, "FrameDifference/hall000%03d.pgm", i-1);
        getMatrixNum(vEt, Et, vnrl, vnrh, vncl, vnch);
        SavePGM_ui8matrix(Et, nrl, nrh, ncl, nch, outputPath);
    }

    // -------------- //
    // -- Results -- //
    // ------------- //
    BENCH(printf("Cycles Total FrameDifference = "));
    BENCH(printf("%6.2f\n", totalCycle));

    BENCH(printf("Cycles per image FrameDifference = "));
    BENCH(printf("%6.2f\n", totalCycle / NUMBER_IMAGES));

    BENCH(printf("Cycles per pixel FrameDifference = "));
    BENCH(printf("%6.2f\n", totalCycle / ((nch+1)*(nrh+1))));


    compare_with_ground_truth("FrameDifference");

    // ---------- //
    // -- free -- //
    // ---------- //
    free_ui8matrix(I0, nrl, nrh, ncl, nch );

    free_vui8matrix(vI0, vnrl, vnrh, vncl, vnch);
    free_vui8matrix(vIt, vnrl, vnrh, vncl, vnch);
    free_vui8matrix(vEt, vnrl, vnrh, vncl, vnch);
}


