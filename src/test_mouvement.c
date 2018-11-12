#define NUMBER_IMAGES 299
#define BORD 2
#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"
#include "mymacro.h"
#include "mouvement.h"
#include "test_mouvement.h"



void test_routine_FrameDifference(int threshold)
{
    puts("----------------------------------");
    puts("-- test_routine_FrameDifference --");
    puts("----------------------------------");

    //initialisation des variables
    char imagePath[50];
    char outputPath[50];
    char initialImagePath[50] = "hall/hall000000.pgm";
    double numcycles, totalCycle;
    char *format = "%6.2f \n";
    int iter, niter = 2;
    int run, nrun = 5;
    double t0, t1, dt, tmin, t;
    long nrl, nrh, ncl, nch; // variables needed to load images


    // ------------ //
    // -- calcul -- //
    // ------------ //
    uint8 **Itm1 =  LoadPGM_ui8matrix(initialImagePath, &nrl, &nrh, &ncl, &nch);
    uint8 **It = ui8matrix(nrl, nrh, ncl, nch);
    uint8 **Et = ui8matrix(nrl-BORD, nrh+BORD, ncl-BORD, nch+BORD);

    for(int i = 1; i <= NUMBER_IMAGES; i++)
    {
        sprintf(imagePath, "hall/hall000%03d.pgm.pgm", i);
        MLoadPGM_ui8matrix(imagePath, nrl, nrh, ncl, nch, It);
        CHRONO(routine_FrameDifference(It, Itm1, Et, nrl, nrh, ncl, nch, threshold), numcycles);
        totalCycle+=numcycles;

        
        sprintf(outputPath, "FrameDifference/hall000%03d.pgm.pgm", i);
        SavePGM_ui8matrix(Et, nrl, nrh, ncl, nch, outputPath);
        copy_ui8matrix_ui8matrix(It, nrl, nrh, ncl, nch, Itm1);
    }


    // -------------- //
    // -- Results -- //
    // ------------- //
    totalCycle /= NUMBER_IMAGES;
    totalCycle /= ((nch+1)*(nrh+1));
    BENCH(printf("Cycles FD = "));
    BENCH(printf(format, totalCycle));


    // ---------- //
    // -- free -- //
    // ---------- //
    free_ui8matrix(It, nrl, nrh, ncl, nch );
    free_ui8matrix(Itm1, nrl, nrh, ncl, nch );
    free_ui8matrix(Et, nrl-BORD, nrh+BORD, ncl-BORD, nch+BORD );
}



/*void test_routine_sigmaDelta()
{
    puts("-----------------------------");
    puts("-- test_routine_sigmaDelta --");
    puts("-----------------------------");

    //Inicialization variables
    char imagePath[50];
    char outputPath[50];
    long nrl, nrh, ncl, nch; // variables needed to load images
    long numCycles, totalCycles; //cycles counters 
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

    // ------------ //
    // -- calcul -- //
    // ------------ //

    routine_SigmaDelta_step0_initialisation(It1, Mt1, Vt1, nrl, nrh, ncl, nch );
    printf("%s%s\n","valor: ", imagePath);

    for(int i = 1; i <= NUMBER_IMAGES; i++)
    {

        sprintf(imagePath, "hall/hall000%03d.pgm", i );

        It = LoadPGM_ui8matrix(imagePath, &nrl, &nrh, &ncl, &nch);

//        MLoadPGM_ui8matrix(imagePath, nrl, nrh, ncl, nch, It); //Load the new image

        
        CHRONO(routine_SigmaDelta_step1(It, Mt1, Mt, Vt, Vt1, Et), numCycles);
        totalCycles = totalCycles + numCycles;
        
        sprintf(outputPath,"SigmaDelta/hall000%03d.pgm",i);
        SavePGM_ui8matrix(Et, nrl, nrh, ncl, nch, outputPath);
        
        //update state of matrix
        copy_ui8matrix_ui8matrix(Mt, nrl, nrh, ncl, nch, Mt1);
        copy_ui8matrix_ui8matrix(Vt, nrl, nrh, ncl, nch, Vt1);
        copy_ui8matrix_ui8matrix(It, nrl, nrh, ncl, nch, It1);
    }

    // -------------- //
    // -- Results -- //
    // ------------- //
    
    BENCH(printf("Cycles Total Sigma Delta = "));
    BENCH(printf("%6.2f\n", totalCycles));

    totalCycles = totalCycles / NUMBER_IMAGES;
    BENCH(printf("Cycles per image Sigma Delta = "));
    BENCH(printf("%6.2f\n", totalCycles));

    totalCycles = totalCycles / ((nch+1)*(nrh+1));
    BENCH(printf("Cycles per pixel Sigma Delta = "));
    BENCH(printf("%6.2f\n", totalCycles));


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

}*/

