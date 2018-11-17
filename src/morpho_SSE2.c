////morphologie mathématique
//SoX X l'ensemble des pixels de l'image associés à l'élément structurant B

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#include "nrdef.h"
#include "vnrutil.h"

#include "morpho_SSE2.h"

//////////////////////
//Dilatation3x3_SSE2//
//////////////////////

void dilatation3x3_SSE2(vuint8 **X, vuint8 **B, long nrl, long ncl, long nrh, long nch)
{
	vuint8 l1;
	vuint8 l2;
	vuint8 l3;

	vuint8 result1,result2,result3;

	vuint8 temp;
	vuint8 left,right;

	int j = nrh;
	int i = nrl;

	l1 = (&X[i+0][j]);
	l2 = _mm_load_si128(&X[i+1][j]);

	result1 =  _mm_or_si128(l1,l2);

	left = _mm_slli_si128(result1,1);

	j++;
	for(j; j <= nch; j++)
	{
		l1 = _mm_load_si128(&X[i+0][j]);
		l2 = _mm_load_si128(&X[i+1][j]);

		result2 = _mm_or_si128(l1,l2);

		right = _mm_srli_si128(result1,1);
		right = _mm_or_si128(right,_mm_slli_si128(result2,15));

		result3 = _mm_or_si128(left,_mm_or_si128(right,result1)); //Valeur finale de B[i][j-1]

		left = _mm_slli_si128(result2,1);
		left = _mm_or_si128(left,_mm_srli_si128(result1,15));

		result1 = result2;

		_mm_store_si128(&B[i][j-1], result3);
	}

	right = _mm_srli_si128(result1,1);

	result3 = _mm_or_si128(left,_mm_or_si128(right,result1));

	_mm_store_si128(&B[i][j-1],result3);

	j = nrh;
	i++;
	// corps de boucle
	for(i ; i < ncl; i++)
	{
		l1 = _mm_load_si128(&X[i-1][j]);
		l2 = _mm_load_si128(&X[i+0][j]);
		l3 = _mm_load_si128(&X[i+1][j]);

		temp =  _mm_or_si128(l1,l2);
		result1 = _mm_or_si128(temp,l3);

		left = _mm_slli_si128(result1,1);

		j++;
		for(j; j <= nch; j++)
		{
			l1 = _mm_load_si128(&X[i-1][j]);
			l2 = _mm_load_si128(&X[i+0][j]);
			l3 = _mm_load_si128(&X[i+1][j]);

			temp =  _mm_or_si128(l1,l2);
			result2 = _mm_or_si128(temp,l3);

			right = _mm_srli_si128(result1,1);
			right = _mm_or_si128(right,_mm_slli_si128(result2,15));

			result3 = _mm_or_si128(left,_mm_or_si128(right,result1));

			left = _mm_slli_si128(result2,1);
			left = _mm_or_si128(left,_mm_srli_si128(result1,15));

			result1 = result2;

			_mm_store_si128(&B[i][j-1], result3);
		}

		right = _mm_srli_si128(result1,1);

		result3 = _mm_or_si128(left,_mm_or_si128(right,result1)); //Valeur finale de B[i][j-1]
		_mm_store_si128(&B[i][j-1],result3);

		j= nrh;
	}

	l1 = _mm_load_si128(&X[i-1][j]);
	l2 = _mm_load_si128(&X[i+0][j]);

	result1 = _mm_or_si128(l1,l2);

	left = _mm_slli_si128(result1,1);

	j++;
	for(j; j <= nch; j++)
	{
		l1 = _mm_load_si128(&X[i-1][j]);
		l2 = _mm_load_si128(&X[i+0][j]);

		result2 = _mm_or_si128(l1,l2);

		right = _mm_srli_si128(result1,1);
		right = _mm_or_si128(right,_mm_slli_si128(result2,15));

		result3 = _mm_or_si128(left,_mm_or_si128(right,result1)); //Valeur finale de B[i][j-1]

		left = _mm_slli_si128(result2,1);
		left = _mm_or_si128(left,_mm_srli_si128(result1,15));

		result1 = result2;

		_mm_store_si128(&B[i][j-1], result3);
	}

	right = _mm_srli_si128(result1,1);

	result3 = _mm_or_si128(left,_mm_or_si128(right,result1)); //Valeur finale de B[i][j-1]

	_mm_store_si128(&B[i][j-1],result3);
}



///////////////////
//Erosion3x3_SSE2//
///////////////////

void erosion3x3_SSE2(vuint8 **X, vuint8 **B, long nrl,long ncl,long nrh,long nch)
{
	vuint8 l1;
	vuint8 l2;
	vuint8 l3;

	vuint8 result1,result2,result3;

	vuint8 temp;
	vuint8 left,right;

	int j = nrh;
	int i = nrl;

	l1 = _mm_load_si128(&X[i+0][j]);
	l2 = _mm_load_si128(&X[i+1][j]);

	result1 = _mm_and_si128(l1,l2);

	left = _mm_slli_si128(result1,1);

	j++;
	for(j;j<=nch;j++)
	{
		l1 = _mm_load_si128(&X[i+0][j]);
		l2 = _mm_load_si128(&X[i+1][j]);

		result2 = _mm_and_si128(l1,l2);

		right = _mm_srli_si128(result1,1);
		right = _mm_or_si128(right,_mm_slli_si128(result2,15));

		result3 = _mm_and_si128(left,_mm_and_si128(right,result1)); //Valeur finale de B[i][j-1]

		left = _mm_slli_si128(result2,1);
		left = _mm_or_si128(left,_mm_srli_si128(result1,15));

		result1 = result2;

		_mm_store_si128(&B[i][j-1], result3);
	}

	right = _mm_srli_si128(result1,1);

	result3 = _mm_and_si128(left,_mm_and_si128(right,result1)); //Valeur finale de B[i][j-1]

	_mm_store_si128(&B[i][j-1],result3);

	j= nrh;
	i++;
	// corps de boucle
	for(i;i<ncl;i++)
	{
		l1 = _mm_load_si128(&X[i-1][j]);
		l2 = _mm_load_si128(&X[i+0][j]);
		l3 = _mm_load_si128(&X[i+1][j]);

		temp =  _mm_and_si128(l1,l2);
		result1 = _mm_and_si128(temp,l3);

		left = _mm_slli_si128(result1,1);

		j++;
		for(j;j<=nch;j++)
		{
			l1 = _mm_load_si128(&X[i-1][j]);
			l2 = _mm_load_si128(&X[i+0][j]);
			l3 = _mm_load_si128(&X[i+1][j]);

			temp =  _mm_and_si128(l1,l2);
			result2 = _mm_and_si128(temp,l3);

			right = _mm_srli_si128(result1,1);
			right = _mm_or_si128(right,_mm_slli_si128(result2,15));

			result3 = _mm_and_si128(left,_mm_and_si128(right,result1));

			left = _mm_slli_si128(result2,1);
			left = _mm_or_si128(left,_mm_srli_si128(result1,15));

			result1 = result2;

			_mm_store_si128(&B[i][j-1], result3);
		}

		right = _mm_srli_si128(result1,1);

		result3 = _mm_and_si128(left,_mm_and_si128(right,result1)); // Valeur finale de B[i][j-1]

		_mm_store_si128(&B[i][j-1],result3);

		j= nrh;
	}

	l1 = _mm_load_si128(&X[i-1][j]);
	l2 = _mm_load_si128(&X[i+0][j]);

	result1 = _mm_and_si128(l1,l2);

	left = _mm_slli_si128(result1,1);

	j++;
	for(j;j<=nch;j++)
	{
		l1 = _mm_load_si128(&X[i-1][j]);
		l2 = _mm_load_si128(&X[i+0][j]);

		result2 = _mm_and_si128(l1,l2);

		right = _mm_srli_si128(result1,1);
		right = _mm_or_si128(right,_mm_slli_si128(result2,15));

		result3 = _mm_and_si128(left,_mm_and_si128(right,result1)); // Valeur finale de B[i][j-1]

		left = _mm_slli_si128(result2,1);
		left = _mm_or_si128(left,_mm_srli_si128(result1,15));

		result1 = result2;

		_mm_store_si128(&B[i][j-1], result3);
	}

	right = _mm_srli_si128(result1,1);

	result3 = _mm_and_si128(left,_mm_and_si128(right,result1)); // Valeur finale de B[i][j-1]

	_mm_store_si128(&B[i][j-1],result3);
}


/////////////////////
//Fermeture3x3_SSE2//
/////////////////////

void fermeture3x3_SSE2(vuint8 **A,vuint8 **B,long nrl,long ncl,long nrh,long nch)
{
	vuint8 ** X = vui8matrix(nrl, ncl, nrh, nch);
	dilatation3x3_SIMD(A,X,nrl,ncl,nrh,nch);
	erosion3x3_SIMD(X,B,nrl,ncl,nrh,nch);
	free_vui8matrix(X,nrl, ncl, nrh, nch);
}


/////////////////////
//Ouverture3x3_SSE2//
/////////////////////

void ouverture3x3_SSE2(vuint8 **A,vuint8 **B,long nrl,long ncl,long nrh,long nch)
{
	vuint8 ** X = vui8matrix(nrl, ncl, nrh, nch);
	erosion3x3_SIMD(X,B,nrl,ncl,nrh,nch);
	dilatation3x3_SIMD(A,X,nrl,ncl,nrh,nch);
	free_vui8matrix(X,nrl, ncl, nrh, nch);
}


















