#include "serviceSquareOptionalNoStruct.h"

void getCoeffs (double* a, double* b, double* c)
{
    MY_ASSERT (a != NULL, "getCoeffs recieved a NULL pointer to a"); //!
    MY_ASSERT (b != NULL, "getCoeffs recieved a NULL pointer to b"); //!
    MY_ASSERT (c != NULL, "getCoeffs recieved a NULL pointer to c");

    printf ("Enter coefficient a:");
    while (scanf  ("%lg", a) == 0)
    {
        cleanBuffer();
    }

    printf ("Enter coefficient b:");
    while (scanf  ("%lg", b) == 0)
    {
        cleanBuffer();
    }

    printf ("Enter coefficient c:");
    while (scanf  ("%lg", c) == 0)
    {
        cleanBuffer();
    }

    printf ("\n\nSolving this equation: %lg*x^2 + %lg*x + %lg = 0\n\n", *a, *b, *c);
}

void printSolutions (enum eqTypes eqType, double root1, double root2)
{
    MY_ASSERT (root1 != NAN, "Root1 is not a number");
    MY_ASSERT (root2 != NAN, "Root2 is not a number");

    switch (eqType)
    {
        case ERROR_CODE:
            printf ("An error has occured, couldn't get the solutions in print solutions\n");
            break;

        case NO_SOLUTIONS:
            printf ("This equation doesn't have any solutions\n");
            break;

        case INF_SOLUTIONS:
            printf ("This equation has an infinite amount of solutions\n");
            break;

        case ONE_SOLUTION:
            printf ("This is an equation with 1 solution: %.4lg\n", root1);
            break;

        case TWO_SOLUTIONS:
            printf ("This is a quadratic equation with two real solutions: {%.4lg, %.4lg}\n", root1, root2);
            break;

        default:
            printf ("Wrong equation type\n");
            break;
    }
}

void solveLinear (double k, double b, double* root)
{
    MY_ASSERT (root != NULL, "solveLinear recieved a NULL pointer to root parameter");
    MY_ASSERT (isfinite (b), "solveLinear recieved a NAN value in b coefficient"); //!
    MY_ASSERT (isfinite (k), "solveLinear recieved a NAN value in k coefficient"); //!

    if (!isEqualDouble (k, 0, STD_ERROR))
    {
        *root = -b / k;
    }
}

enum eqTypes solveSquare (double a, double b, double c, double* root1, double* root2)
{
    MY_ASSERT (root1 != NULL, "solveSquare recieved a NULL pointer to root1");
    MY_ASSERT (root2 != NULL, "solveSquare recieved a NULL pointer to root2");
    MY_ASSERT (isfinite (a), "solveSquare recieved a NAN value in a coefficient"); //!
    MY_ASSERT (isfinite (b), "solveSquare recieved a NAN value in b coefficient"); //!
    MY_ASSERT (isfinite (c), "solveSquare recieved a NAN value in a coefficient");

    double discriminant = evalDiscriminant (a, b, c); //заменить на функци

    if (isEqualDouble (a, 0, STD_ERROR) && isEqualDouble (b, 0, STD_ERROR))
    {
        if (!isEqualDouble (c, 0, STD_ERROR))
            return NO_SOLUTIONS;
        else
        {
            *root1 = *root2 = 0;
            return INF_SOLUTIONS;
        }
    }

    if (isEqualDouble (a, 0, STD_ERROR))
    {
        solveLinear (b, c, root1);
        *root2 = *root1;
        return ONE_SOLUTION;
    }

    if (isEqualDouble (discriminant, 0, STD_ERROR))
    {
        double solutionSquare = -b/(2 * a);

        //printf ("solutionSquare = %lg", solutionSquare);

        *root1 = solutionSquare;
        *root2 = solutionSquare;
        return ONE_SOLUTION;
    }

    if (isGreaterDouble (discriminant, 0, STD_ERROR))
    {
        double xApex = -b / (2 * a);
        double sqrtDiscr = sqrt (discriminant) / (2 * a);

        //printf("test %lg, %lg, discriminant = %lg\n", xApex, sqrtDiscr, discriminant);

        *root1 = xApex - sqrtDiscr;
        *root2 = xApex + sqrtDiscr;

        return TWO_SOLUTIONS;
    }

    if (discriminant < 0)
    {
        return NO_SOLUTIONS;
    }

    printf ("an error has occured in solveSquare\n");
    return ERROR_CODE;
}

double evalDiscriminant (double a, double b, double c)
{
    MY_ASSERT (isfinite (a), "evalDiscriminant recieved a NAN value in a coefficient"); //!
    MY_ASSERT (isfinite (b), "evalDiscriminant recieved a NAN value in b coefficient"); //!
    MY_ASSERT (isfinite (c), "evalDiscriminant recieved a NAN value in a coefficient");

    return (b *  b - 4 * a *  c);
}


static inline void  cleanBuffer ()
{
    while (getchar() != '\n')
        ;
}

