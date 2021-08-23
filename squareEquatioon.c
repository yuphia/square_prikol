#include <stdio.h>
#include <math.h>
#include <assert.h>



#ifndef MY_ASSERT
    #define MY_ASSERT(statement, message) \
        if (!(statement))\
            {\
            printf ("\v" #message "\n\n");\
            printf ("An error has occured in file:" __FILE__ "\n\nIn Line: %d \n\nWhile executing function: %s\n\n" , __LINE__, __PRETTY_FUNCTION__);\
            abort();\
            }
#else
    #undef MY_ASSERT
    #define MY_ASSERT(statement, message) \
        if (!(statement))\
            {\
            printf ("\v" #message "\n\n");\
            printf ("An error has occured in file:" __FILE__ "\n\nIn Line: %d \n\nWhile executing function: %s\n\n" , __LINE__, __PRETTY_FUNCTION__);\
            abort();\
            }
#endif


enum eqTypes {NO_SOLUTIONS, LINEAR,  SQR_ONE,
//                                   quadr. equation with 1 sol.
                    SQR_REAL,                         IDENTITY,                       ERROR_CODE};
//                  quadr. eq. with 2 real solutions  this equation is an identity    an error occurred while getting the equation type
//

const double g_stdError = 1e-10;

struct equation
    {
    double a;
    double b;
    double c;

    double solutions[2];
    };

enum eqTypes getEqType (struct equation *thisEq, double discriminant);
double getDiscriminant (struct equation *thisEq);
void getCoeffs (struct equation *thisEq);
void printSolutions (enum eqTypes eqType, struct equation *thisEq);

double absMy (double n);//returns an absolute value of number n
bool isEqualDouble (double n1, double n2, double allowedError); // compares values of n1 and n2 with an accuracy up to 10^-10 n1 and n2 are double types
bool isBiggerDouble (double n1, double n2, double allowedError); // checks if n1 is bigger than n2 by more than allowedError
bool liesBetween (double number, double leftBorder, double rightBorder); //checks if the number lies between leftBorder and rightBorder


void solveLinear (struct equation *thisEq);
enum eqTypes solveSquare (struct equation *thisEq);

int main ()
    {
    //printf ("%d", MY_ASSERT);
    struct equation thisEq  = {NAN, NAN, NAN, {NAN, NAN}}; //coefficients of an equation of this type: ax^2 + bx + c = 0 in the same order

    //MY_ASSERT (false, "bebra");

    getCoeffs (&thisEq);
    assert (thisEq.a != NAN && thisEq.b != NAN && thisEq.c != NAN);

    double discriminant = getDiscriminant (&thisEq);
    enum eqTypes eqType = solveSquare (&thisEq);

    printSolutions (eqType, &thisEq);

    return 0;
    }

double getDiscriminant (struct equation *thisEq)
    {
    MY_ASSERT (thisEq != NULL, "getDiscriminant recieved a NULL pointer to struct equation");
    return thisEq -> b * thisEq -> b - 4*thisEq -> a * thisEq -> c;
    }

enum eqTypes getEqType (struct equation *thisEq, double discriminant)
    {
    MY_ASSERT (thisEq != NULL, "getEqType recieved a NULL pointer to struct equation");
    MY_ASSERT (discriminant != NAN, "getEqType recieved a discriminant that is not a number");

    if (isEqualDouble (thisEq -> a, 0, g_stdError) && isEqualDouble (thisEq -> b, 0, g_stdError))
        {
        if (isEqualDouble (thisEq -> c, 0, g_stdError)) return IDENTITY;
        else return NO_SOLUTIONS;
        }

    if (isEqualDouble (thisEq -> a, 0, g_stdError)) return LINEAR;

    if (isEqualDouble (discriminant, 0, g_stdError)) return SQR_ONE;

    if (discriminant > 0) return SQR_REAL;

    if (discriminant < 0) return NO_SOLUTIONS;

    return ERROR_CODE;
    }

void getCoeffs (struct equation *thisEq)
    {
    MY_ASSERT (thisEq != NULL, "getCoeffs recieved a NULL pointer to struct thisEq");

    printf ("Enter coefficient a:");
    scanf  ("%lg", &(thisEq -> a));

    printf ("Enter coefficient b:");
    scanf  ("%lg", &(thisEq -> b));

    printf ("Enter coefficient c:");
    scanf  ("%lg", &(thisEq -> c));

    printf ("\n\nSolving this equation: %lg*x^2 + %lg*x + %lg = 0\n\n", thisEq -> a, thisEq -> b, thisEq -> c);
    }

void printSolutions (enum eqTypes eqType, struct equation *thisEq)
    {
    MY_ASSERT (thisEq != NULL, "printSolutions recieved a NULL pointer to struct thisEq");

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
            printf ("This is a linear equation with 1 solution: %lg\n", thisEq -> solutions[0]);
            break;
            }

        case SQR_ONE:
            {
            printf ("This is a quadratic equation with 1 solution: %lg\n", thisEq -> solutions[0]);
            break;
            }

        case SQR_REAL:
            {
            printf ("This is a quadratic equation with two real solutions: {%lg, %lg}\n", thisEq -> solutions[0], thisEq -> solutions[1]);
            break;
            }

        default: printf ("Wrong equation type\n");

        }
    }

void solveLinear (struct equation *thisEq)
    {
    MY_ASSERT (thisEq != NULL, "solveLinear recieved a NULL pointer to struct thisEq");

    if (!isEqualDouble (thisEq -> b, 0, g_stdError))
        {
        thisEq -> solutions[0] = -thisEq -> c / thisEq -> b;
        thisEq -> solutions[1] = NAN;
        }

    printf ("Error in function solveLinear, divising by 0\n");
    }

enum eqTypes solveSquare (struct equation *thisEq)
    {
    MY_ASSERT (thisEq != NULL, "solveSquare recieved a NULL pointer to struct thisEq");

    double discriminant = getDiscriminant (thisEq);; //заменить на функциб
    enum eqTypes eqType = getEqType (thisEq, discriminant);

    switch (eqType)
        {
        case ERROR_CODE:
        case NO_SOLUTIONS:
        case IDENTITY:
            {
            return eqType;
            }

        case LINEAR:
            {
            solveLinear (thisEq);
            return eqType;
            }

        case SQR_ONE:
            {
            double solutionSquare = -thisEq -> b/(2 * thisEq -> a);

            thisEq -> solutions[0] = solutionSquare;
            thisEq -> solutions[1] = NAN;
            return eqType;
            }

        case SQR_REAL:
            {
            double xApex = -thisEq -> b / (2 * thisEq -> a);
            double xDiscr = -sqrt (discriminant) / (2 * thisEq -> a);

            thisEq -> solutions[0] = xApex - xDiscr;
            thisEq -> solutions[1] = xApex + xDiscr;

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
    if (absMy (n1-n2) < allowedError)
        return true;
    return false;
    }

bool isBiggerDouble (double n1, double n2, double allowedError)
    {
    if (absMy (n1-n2) > allowedError)
        return true;
    return false;
    }

bool liesBetween (double number, double leftBorder, double rightBorder)
    {
    MY_ASSERT (isBiggerDouble (leftBorder, rightBorder, g_stdError), "leftBorder is bigger than rightBorder");
    return (number >= leftBorder && number <= rightBorder);
    }

