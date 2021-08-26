/**\file squareEquatioon.c
   \brief This is the file that contains the main function and all calls*/

#include <stdio.h>
#include <math.h>
#include "testSquare.h"
#include "myAssert.h"
#include "serviceSquareOptionalNoStruct.h"


/// Main funciton
int main ()
{
    //struct equation thisEq  = {NAN, NAN, NAN, {NAN, NAN}}; //coefficients of an equation of this type: ax^2 + bx + c = 0 in the same order
    //MY_ASSERT(false, "123");

    //printf ("Running tests, there are: %d errors\n", testSquare());

    double a = 0, b = 0, c = 0;
    double root1 = 0, root2 = 0;

    getCoeffs (&a, &b, &c);
    MY_ASSERT (a != NAN && b != NAN && c != NAN, "couldn't get the coefficients'");

    enum eqTypes eqType = solveSquare (a, b, c, &root1, &root2);

    printSolutions (eqType, root1, root2);

    return 0;
}

