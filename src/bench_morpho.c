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

void test_routine_FrameDif_ouverture3x3(int threshold)
{
    puts("----------------------------------------");
    puts("-- test_routine_FrameDif_ouverture3x3 --");
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
        CHRONO( routine_ouverture3x3(Et, B, nrl, ncl, nrh, nch), numCycles);
        totalCycles = totalCycles + numCycles;
        
        sprintf(outputPath,"FrameDifference/hall000%03d.pgm",i-1);
        SavePGM_ui8matrix(B, nrl, nrh, ncl, nch, outputPath);        
    }

    // -------------- //
    // -- Results -- //
    // ------------- //
    BENCH(printf("Cycles Total ouverture3x3 = "));
    BENCH(printf("%6.2f\n", totalCycles));

    BENCH(printf("Cycles per image ouverture3x3 = "));
    BENCH(printf("%6.2f\n", totalCycles / NUMBER_IMAGES));

    BENCH(printf("Cycles per pixel ouverture3x3 = "));
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

void test_routine_FrameDif_fermeture5x5(int threshold)
{
    puts("----------------------------------------");
    puts("-- test_routine_FrameDif_fermeture5x5 --");
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
        CHRONO( routine_fermeture5x5(Et, B, nrl, ncl, nrh, nch), numCycles);
        totalCycles = totalCycles + numCycles;
        
        sprintf(outputPath,"FrameDifference/hall000%03d.pgm",i-1);
        SavePGM_ui8matrix(B, nrl, nrh, ncl, nch, outputPath);        
    }

    // -------------- //
    // -- Results -- //
    // ------------- //
    BENCH(printf("Cycles Total fermeture5x5 = "));
    BENCH(printf("%6.2f\n", totalCycles));

    BENCH(printf("Cycles per image fermeture5x5 = "));
    BENCH(printf("%6.2f\n", totalCycles / NUMBER_IMAGES));

    BENCH(printf("Cycles per pixel fermeture5x5 = "));
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


void test_routine_FrameDif_ouverture5x5(int threshold)
{
    puts("----------------------------------------");
    puts("-- test_routine_FrameDif_ouverture5x5 --");
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
        CHRONO( routine_ouverture5x5(Et, B, nrl, ncl, nrh, nch), numCycles);
        totalCycles = totalCycles + numCycles;
        
        sprintf(outputPath,"FrameDifference/hall000%03d.pgm",i-1);
        SavePGM_ui8matrix(B, nrl, nrh, ncl, nch, outputPath);        
    }

    // -------------- //
    // -- Results -- //
    // ------------- //
    BENCH(printf("Cycles Total ouverture5x5 = "));
    BENCH(printf("%6.2f\n", totalCycles));

    BENCH(printf("Cycles per image ouverture5x5 = "));
    BENCH(printf("%6.2f\n", totalCycles / NUMBER_IMAGES));

    BENCH(printf("Cycles per pixel ouverture5x5 = "));
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


void test_routine_SD_fermeture3x3()
{
    puts("----------------------------------");
    puts("-- test_routine_SD_fermeture3x3 --");
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
    double numCycles, totalCycles; //cycles counters 
    char initialImagePath[50] = "hall/hall000000.pgm";
    totalCycles = 0;

    //inicial matrix(step 0)
    uint8** It1 = LoadPGM_ui8matrix(initialImagePath, &nrl, &nrh, &ncl, &nch);

    uint8 **Mt1 =  ui8matrix(nrl, nrh, ncl, nch);
    uint8 **Vt1 =  ui8matrix(nrl, nrh, ncl, nch);

    //initial matrix (step1)
    uint8 **It = ui8matrix(nrl, nrh, ncl, nch);
    uint8 **Mt = ui8matrix(nrl, nrh, ncl, nch);
    uint8 **Vt = ui8matrix(nrl, nrh, ncl, nch);
    uint8 **Et = ui8matrix(nrl-BORD, nrh+BORD, ncl-BORD, nch+BORD); //output SD
    uint8 **B = ui8matrix(nrl-BORD, nrh+BORD, ncl-BORD, nch+BORD); //output fermeture


    // ------------ //
    // -- calcul -- //
    // ------------ //

    CHRONO(routine_SigmaDelta_step0_initialisation(It1, Mt1, Vt1, nrl, nrh, ncl, nch ), cycles);
    cycleTotal = cycleTotal + cycles;


    for(int i = 1; i <= NUMBER_IMAGES; i++)
    {
        sprintf(imagePath, "hall/hall000%03d.pgm", i );

        It = LoadPGM_ui8matrix(imagePath, &nrl, &nrh, &ncl, &nch);
        
        CHRONO(routine_SigmaDelta_step1(It, Mt1, Mt, Vt, Vt1, Et), cycles);
        cycleTotal = cycleTotal + cycles;

        CHRONO( routine_fermeture3x3(Et, B, nrl, ncl, nrh, nch), cycles);
        cycleTotal = cycleTotal + cycles;

        sprintf(outputPath,"SigmaDelta/hall000%03d.pgm",i-1);
        SavePGM_ui8matrix(B, nrl, nrh, ncl, nch, outputPath);
        
        //update state of matrix
        copy_ui8matrix_ui8matrix(Mt, nrl, nrh, ncl, nch, Mt1);
        copy_ui8matrix_ui8matrix(Vt, nrl, nrh, ncl, nch, Vt1);
        copy_ui8matrix_ui8matrix(It, nrl, nrh, ncl, nch, It1);
    }

    // -------------- //
    // -- Results -- //
    // ------------- //
    BENCH(printf("Cycles Total Sigma Delta = "));
    BENCH(printf("%6.2f\n", cycleTotal));

    BENCH(printf("Cycles per image Sigma Delta = "));
    BENCH(printf("%6.2f\n", cycleTotal / NUMBER_IMAGES));

    BENCH(printf("Cycles per pixel Sigma Delta = "));
    BENCH(printf("%6.2f\n", cycleTotal / ((nch+1)*(nrh+1))));

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
    free_ui8matrix(Et, nrl-BORD, nrh-BORD, ncl-BORD, nch-BORD );
    free_ui8matrix(B, nrl-BORD, nrh-BORD, ncl-BORD, nch-BORD );
 
 
}


void test_routine_SD_fermeture5x5()
{
    puts("----------------------------------");
    puts("-- test_routine_SD_fermeture5x5 --");
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
    char initialImagePath[50] = "hall/hall000000.pgm";

    //inicial matrix(step 0)
    uint8** It1 = LoadPGM_ui8matrix(initialImagePath, &nrl, &nrh, &ncl, &nch);

    uint8 **Mt1 =  ui8matrix(nrl, nrh, ncl, nch);
    uint8 **Vt1 =  ui8matrix(nrl, nrh, ncl, nch);

    //initial matrix (step1)
    uint8 **It = ui8matrix(nrl, nrh, ncl, nch);
    uint8 **Mt = ui8matrix(nrl, nrh, ncl, nch);
    uint8 **Vt = ui8matrix(nrl, nrh, ncl, nch);
    uint8 **Et = ui8matrix(nrl-BORD, nrh+BORD, ncl-BORD, nch+BORD); //output SD
    uint8 **B = ui8matrix(nrl-BORD, nrh+BORD, ncl-BORD, nch+BORD); //output fermeture


    // ------------ //
    // -- calcul -- //
    // ------------ //

    CHRONO(routine_SigmaDelta_step0_initialisation(It1, Mt1, Vt1, nrl, nrh, ncl, nch ), cycles);
    cycleTotal = cycleTotal + cycles;


    for(int i = 1; i <= NUMBER_IMAGES; i++)
    {
        sprintf(imagePath, "hall/hall000%03d.pgm", i );

        It = LoadPGM_ui8matrix(imagePath, &nrl, &nrh, &ncl, &nch);
        
        CHRONO(routine_SigmaDelta_step1(It, Mt1, Mt, Vt, Vt1, Et), cycles);
        cycleTotal = cycleTotal + cycles;

        CHRONO( routine_fermeture5x5(Et, B, nrl, ncl, nrh, nch), cycles);
        cycleTotal = cycleTotal + cycles;

        sprintf(outputPath,"SigmaDelta/hall000%03d.pgm",i-1);
        SavePGM_ui8matrix(B, nrl, nrh, ncl, nch, outputPath);
        
        //update state of matrix
        copy_ui8matrix_ui8matrix(Mt, nrl, nrh, ncl, nch, Mt1);
        copy_ui8matrix_ui8matrix(Vt, nrl, nrh, ncl, nch, Vt1);
        copy_ui8matrix_ui8matrix(It, nrl, nrh, ncl, nch, It1);
    }

    // -------------- //
    // -- Results -- //
    // ------------- //
    BENCH(printf("Cycles Total Sigma Delta = "));
    BENCH(printf("%6.2f\n", cycleTotal));

    BENCH(printf("Cycles per image Sigma Delta = "));
    BENCH(printf("%6.2f\n", cycleTotal / NUMBER_IMAGES));

    BENCH(printf("Cycles per pixel Sigma Delta = "));
    BENCH(printf("%6.2f\n", cycleTotal / ((nch+1)*(nrh+1))));

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
    free_ui8matrix(Et, nrl-BORD, nrh-BORD, ncl-BORD, nch-BORD );
    free_ui8matrix(B, nrl-BORD, nrh-BORD, ncl-BORD, nch-BORD );
 
 
}

void test_routine_SD_ouverture3x3()
{
    puts("----------------------------------");
    puts("-- test_routine_SD_ouverture3x3 --");
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
    char initialImagePath[50] = "hall/hall000000.pgm";

    //inicial matrix(step 0)
    uint8** It1 = LoadPGM_ui8matrix(initialImagePath, &nrl, &nrh, &ncl, &nch);

    uint8 **Mt1 =  ui8matrix(nrl, nrh, ncl, nch);
    uint8 **Vt1 =  ui8matrix(nrl, nrh, ncl, nch);

    //initial matrix (step1)
    uint8 **It = ui8matrix(nrl, nrh, ncl, nch);
    uint8 **Mt = ui8matrix(nrl, nrh, ncl, nch);
    uint8 **Vt = ui8matrix(nrl, nrh, ncl, nch);
    uint8 **Et = ui8matrix(nrl-BORD, nrh+BORD, ncl-BORD, nch+BORD); //output SD
    uint8 **B = ui8matrix(nrl-BORD, nrh+BORD, ncl-BORD, nch+BORD); //output fermeture


    // ------------ //
    // -- calcul -- //
    // ------------ //

    CHRONO(routine_SigmaDelta_step0_initialisation(It1, Mt1, Vt1, nrl, nrh, ncl, nch ), cycles);
    cycleTotal = cycleTotal + cycles;


    for(int i = 1; i <= NUMBER_IMAGES; i++)
    {
        sprintf(imagePath, "hall/hall000%03d.pgm", i );

        It = LoadPGM_ui8matrix(imagePath, &nrl, &nrh, &ncl, &nch);
        
        CHRONO(routine_SigmaDelta_step1(It, Mt1, Mt, Vt, Vt1, Et), cycles);
        cycleTotal = cycleTotal + cycles;

        CHRONO( routine_ouverture3x3(Et, B, nrl, ncl, nrh, nch), cycles);
        cycleTotal = cycleTotal + cycles;

        sprintf(outputPath,"SigmaDelta/hall000%03d.pgm",i-1);
        SavePGM_ui8matrix(B, nrl, nrh, ncl, nch, outputPath);
        
        //update state of matrix
        copy_ui8matrix_ui8matrix(Mt, nrl, nrh, ncl, nch, Mt1);
        copy_ui8matrix_ui8matrix(Vt, nrl, nrh, ncl, nch, Vt1);
        copy_ui8matrix_ui8matrix(It, nrl, nrh, ncl, nch, It1);
    }

    // -------------- //
    // -- Results -- //
    // ------------- //
    BENCH(printf("Cycles Total Sigma Delta = "));
    BENCH(printf("%6.2f\n", cycleTotal));

    BENCH(printf("Cycles per image Sigma Delta = "));
    BENCH(printf("%6.2f\n", cycleTotal / NUMBER_IMAGES));

    BENCH(printf("Cycles per pixel Sigma Delta = "));
    BENCH(printf("%6.2f\n", cycleTotal / ((nch+1)*(nrh+1))));

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
    free_ui8matrix(Et, nrl-BORD, nrh-BORD, ncl-BORD, nch-BORD );
    free_ui8matrix(B, nrl-BORD, nrh-BORD, ncl-BORD, nch-BORD );
 
 
}

void test_routine_SD_ouverture5x5();
{
    puts("----------------------------------");
    puts("-- test_routine_SD_ouverture5x5 --");
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
    char initialImagePath[50] = "hall/hall000000.pgm";

    //inicial matrix(step 0)
    uint8** It1 = LoadPGM_ui8matrix(initialImagePath, &nrl, &nrh, &ncl, &nch);

    uint8 **Mt1 =  ui8matrix(nrl, nrh, ncl, nch);
    uint8 **Vt1 =  ui8matrix(nrl, nrh, ncl, nch);

    //initial matrix (step1)
    uint8 **It = ui8matrix(nrl, nrh, ncl, nch);
    uint8 **Mt = ui8matrix(nrl, nrh, ncl, nch);
    uint8 **Vt = ui8matrix(nrl, nrh, ncl, nch);
    uint8 **Et = ui8matrix(nrl-BORD, nrh+BORD, ncl-BORD, nch+BORD); //output SD
    uint8 **B = ui8matrix(nrl-BORD, nrh+BORD, ncl-BORD, nch+BORD); //output fermeture


    // ------------ //
    // -- calcul -- //
    // ------------ //

    CHRONO(routine_SigmaDelta_step0_initialisation(It1, Mt1, Vt1, nrl, nrh, ncl, nch ), cycles);
    cycleTotal = cycleTotal + cycles;


    for(int i = 1; i <= NUMBER_IMAGES; i++)
    {
        sprintf(imagePath, "hall/hall000%03d.pgm", i );

        It = LoadPGM_ui8matrix(imagePath, &nrl, &nrh, &ncl, &nch);
        
        CHRONO(routine_SigmaDelta_step1(It, Mt1, Mt, Vt, Vt1, Et), cycles);
        cycleTotal = cycleTotal + cycles;

        CHRONO( routine_ouverture5x5(Et, B, nrl, ncl, nrh, nch), cycles);
        cycleTotal = cycleTotal + cycles;

        sprintf(outputPath,"SigmaDelta/hall000%03d.pgm",i-1);
        SavePGM_ui8matrix(B, nrl, nrh, ncl, nch, outputPath);
        
        //update state of matrix
        copy_ui8matrix_ui8matrix(Mt, nrl, nrh, ncl, nch, Mt1);
        copy_ui8matrix_ui8matrix(Vt, nrl, nrh, ncl, nch, Vt1);
        copy_ui8matrix_ui8matrix(It, nrl, nrh, ncl, nch, It1);
    }

    // -------------- //
    // -- Results -- //
    // ------------- //
    BENCH(printf("Cycles Total Sigma Delta = "));
    BENCH(printf("%6.2f\n", cycleTotal));

    BENCH(printf("Cycles per image Sigma Delta = "));
    BENCH(printf("%6.2f\n", cycleTotal / NUMBER_IMAGES));

    BENCH(printf("Cycles per pixel Sigma Delta = "));
    BENCH(printf("%6.2f\n", cycleTotal / ((nch+1)*(nrh+1))));

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
    free_ui8matrix(Et, nrl-BORD, nrh-BORD, ncl-BORD, nch-BORD );
    free_ui8matrix(B, nrl-BORD, nrh-BORD, ncl-BORD, nch-BORD );
 

}
