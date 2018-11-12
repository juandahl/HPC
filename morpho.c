//morphologie mathématique
#include <stdio.h>
#include <stdlib.h>

#include "include/nrdef.h"
#include "include/vnrutil.h"
#include "./include/nrutil.h"

void routine_dilatation3x3(uint8** X,uint8** B, int nrl, int ncl, int nrh, int nch)
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
		        for(int l=i-1; l<=i+1; k++)
		        	result = result | X[i][j];

            B[i][j] = result;
        }
}


//existe deux opérations de base : la dilatation de X notée  B(X) et l’érosion de X noté B(X).
void routine_erosion3x3(uint8** X,uint8** B, int nrl, int ncl, int nrh, int nch)
{
    uint8 result;
    for( int i = nrl; i <= nrh; i++ )
        for( int j = ncl; j <= nch; j++ )
        {
        	//it is inicialize with 1 because it is an And
        	result = 255;
    	    for( int k = i-1; k <= i+1; k++ )
		        for(int l = j-1; l <= j+1; k++)
		        	result = result & X[i][j];
		        
            B[i][j] = result;
        }
}

void routine_fermeture3x3(uint8** A,uint8** B, int nrl, int ncl, int nrh, int nch)
{
    routine_dilatation3x3(A, B, nrl, ncl, nrh, nch);
    routine_erosion3x3(A, B, nrl, ncl, nrh, nch);
}

void routine_ouverture3x3(uint8** A,uint8** B, int nrl, int ncl, int nrh, int nch)
{
    routine_erosion3x3(A, B, nrl, ncl, nrh, nch);
    routine_dilatation3x3(A, B, nrl, ncl, nrh, nch);
}

void routine_dilatation5x5(uint8** X,uint8** B, int nrl, int ncl, int nrh, int nch)
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
		        for(int l=i-1; l<=i+1; k++)
		        	result = result | X[i][j];

            B[i][j] = result;
        }
}


//existe deux opérations de base : la dilatation de X notée  B(X) et l’érosion de X noté B(X).
void routine_erosion5x5(uint8** X,uint8** B, int nrl, int ncl, int nrh, int nch)
{
    uint8 result;
    for( int i = nrl; i <= nrh; i++ )
        for( int j = ncl; j <= nch; j++ )
        {
        	//it is inicialize with 1 because it is an And
        	result = 255;
    	    for( int k = i-1; k <= i+1; k++ )
		        for(int l = j-1; l <= j+1; k++)
		        	result = result & X[i][j];
		        
            B[i][j] = result;
        }
}

void routine_fermeture5x5(uint8** A,uint8** B, int nrl, int ncl, int nrh, int nch)
{
    routine_dilatation5x5(A, B, nrl, ncl, nrh, nch);
    routine_erosion5x5(A, B, nrl, ncl, nrh, nch);
}

void routine_ouverture5x5(uint8** A,uint8** B, int nrl, int ncl, int nrh, int nch)
{
    routine_erosion5x5(A, B, nrl, ncl, nrh, nch);
    routine_dilatation5x5(A, B, nrl, ncl, nrh, nch);
}

