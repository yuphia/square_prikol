#include <stdio.h>
#include <math.h>

enum eqTypes {NO_SOLUTIONS, LINEAR,  SQR_ONE,
//                                   quadr. equation with 1 sol.
                    SQR_REAL,                         IDENTITY,                       ERROR_CODE};
//                  quadr. eq. with 2 real solutions  this equation is an identity    an error occurred while getting the equation type
//

const double g_stdError = 1e-10;

struct coefficients
    {
    double a;
    double b;
    double c;
    };

enum eqTypes getEqType (struct coefficients coeffs, double discriminant);
double getDiscriminant (struct coefficients coeffs);
void getCoeffs (struct coefficients *coeffs);
void printSolutions (enum eqTypes eqType, double *solutions);

double absMy (double n);//returns an absolute value of number n
bool isEqualDouble (double n1, double n2, double allowedError); // compares values of n1 and n2 with an accuracy up to 10^-10 n1 and n2 are double types

void solveLinear (struct coefficients coeffs, double *solutions);
enum eqTypes solveSquare (struct coefficients coeffs, double *solutions);

int main ()
    {
    struct coefficients coeffs  = {NAN, NAN, NAN}; //coefficients of an equation of this type: ax^2 + bx + c = 0 in the same order
    double solutions [2] = {NAN, NAN};

    getCoeffs (&coeffs);

    double discriminant = getDiscriminant (coeffs);
    enum eqTypes eqType = solveSquare (coeffs, solutions);

    printSolutions (eqType, solutions);

    return 0;
    }

double getDiscriminant (struct coefficients coeffs)
    {
    return coeffs.b*coeffs.b - 4*coeffs.a*coeffs.c;
    }

enum eqTypes getEqType (struct coefficients coeffs, double discriminant)
    {
    if (isEqualDouble (coeffs.a, 0, g_stdError) && isEqualDouble (coeffs.b, 0, g_stdError))
        {
        if (isEqualDouble (coeffs.c, 0, g_stdError)) return IDENTITY;
        else return NO_SOLUTIONS;
        }

    if (isEqualDouble (coeffs.a, 0, g_stdError)) return LINEAR;

    if (isEqualDouble (discriminant, 0, g_stdError)) return SQR_ONE;

    if (discriminant > 0) return SQR_REAL;

    if (discriminant < 0) return NO_SOLUTIONS;

    return ERROR_CODE;
    }

void getCoeffs (struct coefficients *coeffs)
    {
    printf ("Enter coefficient a:");
    scanf  ("%lg", &(coeffs -> a));

    printf ("Enter coefficient b:");
    scanf  ("%lg", &(coeffs -> b));

    printf ("Enter coefficient c:");
    scanf  ("%lg", &(coeffs -> c));

    printf ("\n\nSolving this equation: %lg*x^2 + %lg*x + %lg = 0\n\n", coeffs -> a, coeffs -> b, coeffs -> c);
    }

void printSolutions (enum eqTypes eqType, double *solutions)
    {
    switch (eqType)
        {
        case ERROR_CODE:
            {
            printf ("An error has occured, couldn't get the solutions\n");
            break;
            }

        case NO_SOLUTIONS:
            {
            printf ("This equation doesn't have any solutions\n");
            break;
            }

        case IDENTITY:
            {
            printf ("This equation has an infinite amount of solutions\n");
            break;
            }

        case LINEAR:
            {
            printf ("This is a linear equation with 1 solution: %lg\n", *solutions);
            break;
            }

        case SQR_ONE:
            {
            printf ("This is a quadratic equation with 1 solution: %lg\n", *solutions);
            break;
            }

        case SQR_REAL:
            {
            printf ("This is a quadratic equation with two real solutions: {%lg, %lg}\n", *solutions, *(solutions + 1));
            break;
            }

        default: printf ("Wrong equation type\n");

        }
    }

void solveLinear (struct coefficients coeffs, double *solutions)
    {
    if (!isEqualDouble (coeffs.b, 0, g_stdError))
        {
        *solutions = -coeffs.c/coeffs.b;
        *(solutions + 1) = NAN;
        }

    printf ("Error in function solveLinear, divising by 0\n");
    }

enum eqTypes solveSquare (struct coefficients coeffs, double *solutions)
    {
    double discriminant = getDiscriminant (coeffs);; //заменить на функциб
    enum eqTypes eqType = getEqType (coeffs, discriminant);

    switch (eqType)
        {
        case ERROR_CODE:
            {
            return eqType;
            }

        case NO_SOLUTIONS:
            {
            return eqType;
            }

        case IDENTITY:
            {
            return eqType;
            }

        case LINEAR:
            {
            solveLinear (coeffs, solutions);
            return eqType;
            }

        case SQR_ONE:
            {
            double solutionSquare = -coeffs.b/(2*coeffs.a);

            *solutions = solutionSquare;
            *(solutions + 1) = NAN;
            return eqType;
            }

        case SQR_REAL:
            {
            double xApex = -coeffs.b/(2*coeffs.a);
            double xDiscr = -sqrt (discriminant) / (2*coeffs.a);

            *solutions = xApex - xDiscr;
            *(solutions + 1) = xApex + xDiscr;

            return eqType;
            }

        default:
            {
            printf ("default is triggered in solveSquare\n");
            return eqType;
            }
        }
    }



double absMy (double n)
    {
    if (n >= 0) return n;
    else return -n;
    }

bool isEqualDouble (double n1, double n2, double allowedError)
    {
    if (absMy (n1-n2) < allowedError) return true;

    return false;
    }


