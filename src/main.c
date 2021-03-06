#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"
#include "mymacro.h"
#include "vnrutil.h"
#include "vnrdef.h"

#include "bench_morpho.h"
#include "bench_mouvement.h"
#include "bench_mouvement_SSE2.h"
#include "bench_morpho.h"
#include "bench_morpho_SSE2.h"


#define ENABLE_BENCHMARK 1

// ============
void info(void)
// ============
{

#ifdef ENABLE_BENCHMARK
    puts("#############################");
    puts("mode Benchmark ON & DEBUG OFF");
    puts("#############################");
#else
    puts("#############################");
    puts("mode Benchmark OFF & DEBUG ON");
    puts("#############################");
#endif
}

// -----------
int main(void)
// -----------
{
    info();
//TEST PERFORMANCE FRAME DIFFERENCE
/*
    test_routine_FrameDifference(10);
    test_routine_FrameDifference(20);
    test_routine_FrameDifference(30);
    test_routine_FrameDifference(40);
    test_routine_FrameDifference(50);
    test_routine_FrameDifference(60);
    test_routine_FrameDifference(70);
*/
//TEST PERFORMANCE FRAME DIFFERENCE
/*
    test_routine_FrameDifference(60);
    test_routine_FrameDifference_SSE2(60);
*/

//TEST PERFORMANCE SIGMA DELTA
/*
    test_routine_sigmaDelta();
    test_routine_SigmaDelta_SSE2();
*/

//TEST THREADS
/*
    test_routine_FrameDifference(60);
    test_routine_FrameDifference_thread(60);
    test_routine_sigmaDelta();
*/
//TEST SOLUTION ROC 
/*
    test_routine_FrameDifference(60);
    test_routine_sigmaDelta();
    test_routine_FrameDif_fermeture3x3(60);
    test_routine_FrameDif_ouverture3x3(60);
    test_routine_FrameDif_fermeture5x5(60);
    test_routine_FrameDif_ouverture5x5(60);
    test_routine_SD_fermeture3x3();  
    test_routine_SD_fermeture5x5();
    test_routine_SD_ouverture3x3();
    test_routine_SD_ouverture5x5();
*/

//TEST SSE2
/*
   test_routine_FrameDifference_SSE2(60);
   test_routine_SigmaDelta_SSE2();

   test_routine_FrameDif_fermeture3x3_SSE2(60);
   test_routine_FrameDif_ouverture3x3_SSE2(60);

   test_routine_SD_fermeture3x3_SSE2();  
   test_routine_SD_ouverture3x3_SSE2();
*/
    return 0;    
}
  
  
