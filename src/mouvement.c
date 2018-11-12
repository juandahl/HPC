//contiendra l’ensemble des algorithmes scalaires de détection de mouvement (ainsi que leur différentes implantations optimisées).
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#include "nrdef.h"
#include "nrutil.h"

#define VMIN 1
#define VMAX 254

#define Efond 0
#define Emouv 255

#define N 2 //N vaut 2 ou 3, éventuellement 4.

long nrl, nrh, ncl, nch;

void routine_FrameDifference(uint8** I1, uint8** I0, uint8** E0, long rawl, long rawh, long coll, long colh, int threshold)
{

    nrl = rawl;
    nrh = rawh;
    ncl = coll;
    nch = colh;
    //matrice de taille [nrl..nrh][ncl..nch]
    long nrl, nrh, ncl, nch;
    /*//chargement de 2 images
    uint8 **I0 =  LoadPGM_ui8matrix(image1, &nrl, &nrh, &ncl, &nch);
    uint8 **I1 =  LoadPGM_ui8matrix(image2, &nrl, &nrh, &ncl, &nch);*/


    //uint8 **E0 =  ui8matrix(nrl, nrh, ncl, nch);
    uint8 **O0 = ui8matrix(nrl, nrh, ncl, nch);
    for(int i = nrl; i < nrh; i++ )
    {
        for(int j = ncl; j < nch; j++)
        {
            O0[i][j] = abs(I1[i][j] - I0[i][j]);
	    if(O0[i][j] < threshold)
                E0[i][j] = Efond; //pas de mouvement
            else
                E0[i][j] = Emouv; //si mouvement

        }
    }
    
    /*for(int i = nrl; i < nrh; i++ )
    {
        for(int j = ncl; j < nch; j++)
        {
            if(O0[i][j] < threshold)
                E0[i][j] = Efond; //pas de mouvement
            else
                E0[i][j] = Emouv; //si mouvement

        }
    }*/

    //generation d'une nouvelle image
    /*SavePGM_ui8matrix(E0, nrl, nrh, ncl, nch, "frame_difference.pgm");
    free_ui8matrix(I0, nrl, nrh, ncl, nch);
    free_ui8matrix(I1, nrl, nrh, ncl, nch);
    free_ui8matrix(E0, nrl, nrh, ncl, nch);
    free_ui8matrix(O0, nrl, nrh, ncl, nch);*/
}

int maxmin(uint8 ** Vt)
{
    int result = Vt;
    if (Vt > VMAX)
        result = VMAX;
    if (result > VMIN)
        return result;
    else
        return VMIN;
}

void routine_SigmaDelta_step0_initialisation(uint8** It1, uint8 **M, uint8 **V, long rawl, long rawh, long coll, long colh )
{


    nrl = rawl;
    nrh = rawh;
    ncl = coll;
    nch = colh;    

    for(int i = nrl; i <= nrh; i++ )
        for(int j = ncl; j <= nch; j++)
        {
            M[i][j] = It1[i][j];
            V[i][j] = VMIN;

        }
}

//Mt = moyenne, vt= variance, Mt1 = Mt-1, Et = result  
void routine_SigmaDelta_step1(uint8** It, uint8** Mt1, uint8** Mt, uint8** Vt, uint8** Vt1, uint8** Et){
    //Verifier parameters et var locales
    uint8 Ot;
	//steps from 1 to 4 together to avoid repeat the loop
    for(int i = nrl; i <= nrh; i++ )
        for(int j = ncl; j <= nch; j++){
        	//step 1
        	if (Mt1[i][j] < It[i][j])
        		Mt[i][j] = Mt1[i][j] + 1;
        	else
	        	if (Mt1[i][j] > It[i][j])
	        		Mt[i][j] = Mt1[i][j] - 1;
	        	else
	        		Mt[i][j] = Mt1[i][j];
	        
	        //step 2
            Ot = abs(Mt - It);
         	
         	//step 3
         	if ( Vt1 < (int)N*Ot )
         		Vt = Vt1 + 1;
         	else
	         	if ( Vt1 > (int)N*Ot )
	         		Vt = Vt1 - 1;
	            else
	                Vt = Vt1;
            Vt = maxmin(Vt);

            //step 4
            if(Ot < Vt)
                Et[i][j] = Efond;
            else
                Et[i][j] = Emouv;
        }
}
