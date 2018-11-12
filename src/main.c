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
