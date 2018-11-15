/*
#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"
#include "mymacro.h"
#include "test_mouvement.h"

int main(int argc, char *argv[])
{
    test_routine_FrameDifference(21);
    test_routine_sigmaDelta();
    return 0;
}
*/
/* -------------- */
/* --- main.c --- */
/* -------------- */

#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"
#include "mymacro.h"


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
    test_routine_FrameDifference(48);
    test_routine_FrameDifference(50);
    test_routine_FrameDifference(52);
    test_routine_FrameDifference(54);
    test_routine_FrameDifference(56);
    test_routine_FrameDifference(58);


/*
    test_routine_FrameDifference(20);
    test_routine_sigmaDelta();
    test_routine_FrameDif_fermeture3x3(20);
    test_routine_FrameDif_ouverture3x3(20);
    test_routine_FrameDif_fermeture5x5(20);
    test_routine_FrameDif_ouverture5x5(20);
    test_routine_SD_fermeture3x3();  
    test_routine_SD_fermeture5x5();
    test_routine_SD_ouverture3x3();
    test_routine_SD_ouverture5x5();
*/
    return 0;    
}