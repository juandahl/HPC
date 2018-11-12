<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

=======
#define NUMBER_IMAGES 300
>>>>>>> 839c898635d44d5674d759ae2968f254c1dee978
#include "nrdef.h"
#include "nrutil.h"
#include "mymacro.h"

<<<<<<< HEAD
#include "mouvement.h"
#include "test_mouvement.h"

#define NUMBER_IMAGES 300

=======
>>>>>>> 839c898635d44d5674d759ae2968f254c1dee978
void test_routine_sigmaDelta()
{
    puts("-----------------------------");
    puts("-- test_routine_sigmaDelta --");
    puts("-----------------------------");

    //Inicialization variables
    char imagePath[40];
    char outputPath[40];
    int nrl, nrh, ncl, nch; // variables needed to load images
    long numCycles, totalCycles; //cycles counters 
    char initialImagePath[40]; // first image It-1
    sprintf(initialImagePath,"hall/hall000000.pgm");
    
    printf("%s\n", initialImagePath);
    //inicial matrix(step 0)
    uint8 **It1 = ui8matrix(nrl, nrh, ncl, nch);

    MLoadPGM_ui8matrix(initialImagePath, nrl, nrh, ncl, nch, It1);

    uint8 **Mt1 =  ui8matrix(&nrl, &nrh, &ncl, &nch);
    uint8 **Vt1 =  ui8matrix(&nrl, &nrh, &ncl, &nch);
    printf("%s\n", "pasa");

    //initial matrix (step1)
    uint8 **It = ui8matrix(nrl, nrh, ncl, nch);
    uint8 **Et = ui8matrix(nrl, nrh, ncl, nch);
    uint8 **Mt =  ui8matrix(nrl, nrh, ncl, nch);
    uint8 **Vt =  ui8matrix(nrl, nrh, ncl, nch);


    // ------------ //
    // -- calcul -- //
    // ------------ //
void routine_SigmaDelta_step0_inicialisation(It1, Mt1, Vt1, nrl, nrh, ncl, nch );

    for(int i = 1; i <= NUMBER_IMAGES; i++)
    {
        sprintf(imagePath, "hall/hall000%03d%s.pgm", i );
        MLoadPGM_ui8matrix(imagePath, nrl, nrh, ncl, nch, It); //Load the new image

        
        CHRONO(routine_SigmaDelta_step1(It, Mt1, Mt, Vt, Vt1, Et), numCycles);
        totalCycles = totalCycles + numCycles;
        
        sprintf(outputPath,"SigmaDelta/hall000%03d.pgm",i);
        SavePGM_ui8matrix(Et, nrl, nrh, ncl, nch, outputPath);
        //update state of matrix
        copy_ui8matrix_ui8matrix(Mt, nrl, nrh, ncl, nch, Mt1);
        copy_ui8matrix_ui8matrix(Vt, nrl, nrh, ncl, nch, Vt1);
        copy_ui8matrix_ui8matrix(It, nrl, nrh, ncl, nch, It1);

        /*memcpy(Mtm1[nrl], Mt[nrl], sizeof(uint8)*(nrow*ncol));
        memcpy(Vtm1[nrl], Vt[nrl], sizeof(uint8)*(nrow*ncol));
        memcpy(Itm1[nrl], It[nrl], sizeof(uint8)*(nrow*ncol));*/
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

}

