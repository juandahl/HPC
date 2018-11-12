#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "morpho.c"

int main(int argc, char *argv[])
{
    long nrl, nrh, ncl, nch;
    uint8 **A = LoadPGM_ui8matrix("./morpho.png", &nrl, &nrh, &ncl, &nch);
    uint8 **B = ui8matrix(nrl, nrh, ncl, nch);
    routine_erosion3x3(A, B, nrl, ncl, nrh, nch);
    return 0;
}
