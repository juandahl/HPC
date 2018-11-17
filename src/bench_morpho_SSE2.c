//test_morpho.c
#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"

#include "nrutil.h"
#include "mymacro.h"

#include "bench_morpho.h"

#define NUMBER_IMAGES 299
#define BORD 2

//unit test for frame difference
void test_routine_FrameDif_fermeture3x3(int threshold)
{
    puts("----------------------------------------");
    puts("-- test_routine_FrameDif_fermeture3x3 --");
    puts("----------------------------------------");

    //Inicialization variables
    //cycles variables
    double cycles;

    char *format = "%6.2f \n";
    double cycleTotal = 0;
    int iter, niter = 2;
    int run, nrun = 5;
    double t0, t1, dt, tmin, t;

    //
    char imagePath[50] = "hall/hall000000.pgm";
    char outputPath[50];
    long nrl, nrh, ncl, nch; // variables needed to load images
    double numCycles, totalCycles; //cycles counters     
    totalCycles = 0;

    //inicial matrix
    uint8 **Itm1 =  LoadPGM_ui8matrix(imagePath, &nrl, &nrh, &ncl, &nch);
    uint8 **It = ui8matrix(nrl, nrh, ncl, nch);
    uint8 **Et = ui8matrix(nrl-BORD, nrh+BORD, ncl-BORD, nch+BORD); //output frame_dif
    uint8 **B = ui8matrix(nrl-BORD, nrh+BORD, ncl-BORD, nch+BORD); //output fermeture

    // ------------ //
    // -- calcul -- //
    // ------------ //

    for(int i = 1; i <= NUMBER_IMAGES; i++)
    {
        sprintf(imagePath, "hall/hall000%03d.pgm", i );
        MLoadPGM_ui8matrix(imagePath, &nrl, &nrh, &ncl, &nch, It);

        //run frame diff
        CHRONO( routine_FrameDifference(It, Itm1, Et, nrl, nrh, ncl, nch, threshold), numCycles);
        totalCycles = totalCycles + numCycles;

        //run frame diff with the frame dif output
        CHRONO( routine_fermeture3x3(Et, B, nrl, ncl, nrh, nch), numCycles);
        totalCycles = totalCycles + numCycles;
        
        sprintf(outputPath,"FrameDifference/hall000%03d.pgm",i-1);
        SavePGM_ui8matrix(B, nrl, nrh, ncl, nch, outputPath);        
    }

    // -------------- //
    // -- Results -- //
    // ------------- //
    BENCH(printf("Cycles Total fermeture3x3 = "));
    BENCH(printf("%6.2f\n", totalCycles));

    BENCH(printf("Cycles per image fermeture3x3 = "));
    BENCH(printf("%6.2f\n", totalCycles / NUMBER_IMAGES));

    BENCH(printf("Cycles per pixel fermeture3x3 = "));
    BENCH(printf("%6.2f\n", totalCycles / ((nch+1)*(nrh+1))));


    compare_with_ground_truth("FrameDifference");

    // ---------- //
    // -- free -- //
    // ---------- //
    free_ui8matrix(Itm1, nrl, nrh, ncl, nch );
    free_ui8matrix(It, nrl, nrh, ncl, nch );
    free_ui8matrix(Et, nrl-BORD, nrh-BORD, ncl-BORD, nch-BORD );
    free_ui8matrix(B, nrl-BORD, nrh-BORD, ncl-BORD, nch-BORD );

}
