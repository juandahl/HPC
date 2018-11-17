//contiendra l’ensemble des algorithmes scalaires de détection de mouvement (ainsi que leur différentes implantations optimisées).
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#include "nrdef.h"
#include "nrutil.h"

#include <pthread.h> 

#include "bench_mouvement.h"

#define VMIN 25
#define VMAX 255

#define Efond 0
#define Emouv 255

#define N 2 //N vaut 2 ou 3, éventuellement 4.

long nrl, nrh, ncl, nch;

// Value depend on System core 
#define CORE 4 

#define NUMBER_IMAGES 299
#define BORD 2  
  
// Maximum threads is equal to total core of system 
uint8 **I1;// = LoadPGM_ui8matrix("hall/hall000%03d.pgm", &nrl, &nrh, &ncl, &nch);
uint8 **I0;// = ui8matrix(nrl, nrh, ncl, nch);
uint8 **E0;// = ui8matrix(nrl-BORD, nrh+BORD, ncl-BORD, nch+BORD);

pthread_t thread[CORE]; 

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
        sprintf(imagePath, "hall/hall000%03d.pgm", i);
	    It = LoadPGM_ui8matrix(imagePath, &nrl, &nrh, &ncl, &nch);
        CHRONO(routine_FrameDifference(It, Itm1, Et, nrl, nrh, ncl, nch, threshold), numcycles);
        
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



void test_routine_sigmaDelta()
{
    puts("-----------------------------");
    puts("-- test_routine_sigmaDelta --");
    puts("-----------------------------");

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

    // ------------ //
    // -- calcul -- //
    // ------------ //
    CHRONO( routine_SigmaDelta_step0_initialisation(It1, Mt1, Vt1, nrl, nrh, ncl, nch), cycles);
    totalCycles = totalCycles + cycles;

    for(int i = 1; i <= NUMBER_IMAGES; i++)
    {

        sprintf(imagePath, "hall/hall000%03d.pgm", i );

        It = LoadPGM_ui8matrix(imagePath, &nrl, &nrh, &ncl, &nch);
    
        CHRONO(routine_SigmaDelta_step1(It, Mt1, Mt, Vt, Vt1, Et), cycles);

        totalCycles = totalCycles + cycles;
        
        sprintf(outputPath,"SigmaDelta/hall000%03d.pgm",i-1);
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



//BORRRAR DESPUEST
/*
void test_routine_FrameDifference_thread(int threshold)
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
    double time_spent = 0;
 

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
        clock_t begin1 = clock();
        CHRONO(routine_FrameDifference_thread(It, Itm1, Et, nrl, nrh, ncl, nch, threshold), numcycles);
        clock_t end1 = clock();
        time_spent += (double)(end1 - begin1) / CLOCKS_PER_SEC;    
        totalCycle+=numcycles;

        sprintf(outputPath, "FrameDifference/hall000%03d.pgm", i-1);
        SavePGM_ui8matrix(Et, nrl, nrh, ncl, nch, outputPath);
        copy_ui8matrix_ui8matrix(It, nrl, nrh, ncl, nch, Itm1);
    }

    // -------------- //
    // -- Results -- //
    // ------------- //
    BENCH(printf("Cycles Total Sigma Delta = "));
    BENCH(printf("%6.2f\n", totalCycle));

    BENCH(printf("Cycles per image Sigma Delta = "));
    BENCH(printf("%6.2f\n", totalCycle / NUMBER_IMAGES));

    BENCH(printf("Cycles per pixel Sigma Delta = "));
    BENCH(printf("%6.2f\n", totalCycle / ((nch+1)*(nrh+1))));

    BENCH(printf("Time = %6.2f seg\n\n", time_spent));

    compare_with_ground_truth("FrameDifference");

    // ---------- //
    // -- free -- //
    // ---------- //
    free_ui8matrix(It, nrl, nrh, ncl, nch );
    free_ui8matrix(Itm1, nrl, nrh, ncl, nch );
    free_ui8matrix(Et, nrl-BORD, nrh+BORD, ncl-BORD, nch+BORD );
}
*/