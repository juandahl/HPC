//test_mouvement_SSE2.c
#include <stdio.h>
#include <stdlib.h>
#include "vnrdef.h"
#include "vnrutil.h"
#include "nrdef.h"
#include "nrutil.h"
#include "mouvement_SSE2.h"
#include "mymacro.h"

#define BORD 2
#define NUMBER_IMAGES 299
#define VMIN 20
#define VMAX 240


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
    uint8 **Itm1 =  LoadPGM_ui8matrix(initialImagePath, &nrl, &nrh, &ncl, &nch);
    uint8 **It = ui8matrix(nrl, nrh, ncl, nch);
    uint8 **Et = ui8matrix(nrl-BORD, nrh+BORD, ncl-BORD, nch+BORD);

    for(int i = 1; i <= NUMBER_IMAGES; i++)
    {
        sprintf(imagePath, "hall/hall000%03d.pgm", i);
	    It = LoadPGM_ui8matrix(imagePath, &nrl, &nrh, &ncl, &nch);
        CHRONO(routine_FrameDifference_SSE2(It, Itm1, Et, nrl, nrh, ncl, nch, vthreshold), numcycles);
        
        totalCycle+=numcycles;

        sprintf(outputPath, "FrameDifference/hall000%03d.pgm", i-1);
        SavePGM_ui8matrix(Et, nrl, nrh, ncl, nch, outputPath);
        copy_ui8matrix_ui8matrix(It, nrl, nrh, ncl, nch, Itm1);
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
    free_ui8matrix(It, nrl, nrh, ncl, nch );
    free_ui8matrix(Itm1, nrl, nrh, ncl, nch );
    free_ui8matrix(Et, nrl-BORD, nrh+BORD, ncl-BORD, nch+BORD );
}



void test_unitaire_SigmaDelta_SSE2(){


}


/*
void test_routine_SigmaDelta_SSE2(vuint8 threshold){

    puts("----------------------------------");
    puts("-- test_routine_SigmaDelta_SSE2 --");
    puts("----------------------------------");

    //initialisation des variables
    vuint NUMBER_IMAGES = init_vuint8(299);
}

*/