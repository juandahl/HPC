//morphologie mathématique
#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"
#include "mymacro.h"

void routine_dilatation3x3(uint8** X,uint8** B, long nrl, long ncl, long nrh, long nch)
{
    //Pour des images binaires, la dilatation consiste à calculer un OR sur le voisinage B dans l’image source
    // et à l’écrire dans l’image destination. Inversement l’érosion consiste à calculer un AND sur le voisinage.
    uint8 result;
    for(int i=nrl; i<=nrh; i++)
        for(int j=ncl; j<=nch; j++)
        {
        	//it is inicialize in 0 because it is an Or
        	result = 0;
    	    for(int k=j-1; k<=j+1; k++)
		        for(int l=i-1; l<=i+1; l++)
		        	result = result | X[i][j];

            B[i][j] = result;
        }
}


//existe deux opérations de base : la dilatation de X notée  B(X) et l’érosion de X noté B(X).
void routine_erosion3x3(uint8** X,uint8** B, long nrl, long ncl, long nrh, long nch)
{
    uint8 result;
    for( int i = nrl; i <= nrh; i++ )
        for( int j = ncl; j <= nch; j++ )
        {
        	//it is inicialize with 1 because it is an And
        	result = 255;
    	    for( int k = i-1; k <= i+1; k++ )
		        for(int l = j-1; l <= j+1; l++)
		        	result = result & X[i][j];
		        
            B[i][j] = result;
        }
}

void routine_fermeture3x3(uint8** A,uint8** B, long nrl, long ncl, long nrh, long nch)
{
    uint8 ** X = ui8matrix(nrl-2, nrh+2, ncl-2, nch+2);
    routine_dilatation3x3(A, X, nrl, ncl, nrh, nch);
    routine_erosion3x3(X, B, nrl, ncl, nrh, nch);
}

void routine_ouverture3x3(uint8** A,uint8** B, long nrl, long ncl, long nrh, long nch)
{
    uint8 ** X = ui8matrix(nrl-2, nrh+2, ncl-2, nch+2);
    routine_erosion3x3(A, X, nrl, ncl, nrh, nch);
    routine_dilatation3x3(X, B, nrl, ncl, nrh, nch);

}

void routine_dilatation5x5(uint8** X,uint8** B, long nrl, long ncl, long nrh, long nch)
{
	//Pour des images binaires, la dilatation consiste à calculer un OR sur le voisinage B dans l’image source
	// et à l’écrire dans l’image destination. Inversement l’érosion consiste à calculer un AND sur le voisinage.
    uint8 result;
    for(int i=nrl; i<=nrh; i++)
        for(int j=ncl; j<=nch; j++)
        {
        	//it is inicialize in 0 because it is an Or
            result = 0;
    	    for(int k=j-2; k<=j+2; k++)
		        for(int l=i-2; l<=i+2; l++)
		        	result = result | X[i][j];

            B[i][j] = result;
        }
}


//existe deux opérations de base : la dilatation de X notée  B(X) et l’érosion de X noté B(X).
void routine_erosion5x5(uint8** X,uint8** B, long nrl, long ncl, long nrh, long nch)
{
    uint8 result;
    for( int i = nrl; i <= nrh; i++ )
        for( int j = ncl; j <= nch; j++ )
        {
        	//it is inicialize with 1 because it is an And
        	result = 255;
    	    for( int k = i-2; k <= i+2; k++ )
		        for(int l = j-2; l <= j+2; l++)
		        	result = result & X[i][j];
		        
            B[i][j] = result;
        }
}

void routine_fermeture5x5(uint8** A,uint8** B, long nrl, long ncl, long nrh, long nch)
{
    uint8 ** X = ui8matrix(nrl-2, nrh+2, ncl-2, nch+2);
    routine_dilatation5x5(A, X, nrl, ncl, nrh, nch);
    routine_erosion5x5(X, B, nrl, ncl, nrh, nch);
}

void routine_ouverture5x5(uint8** A, uint8** B, long nrl, long ncl, long nrh, long nch)
{
    uint8 ** X = ui8matrix(nrl-2, nrh+2, ncl-2, nch+2);
    routine_erosion5x5(A, X, nrl, ncl, nrh, nch);
    routine_dilatation5x5(X, B, nrl, ncl, nrh, nch);
}

