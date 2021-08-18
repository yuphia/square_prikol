#include <stdio.h>
#include <math.h>

enum eqTypes {NO_SOLUTIONS, LINEAR,  SQR_ONE,
//                  нет решений   линейное квадр с 1 действ решениями
                    SQR_REAL,                 SQR_COMPLEX,
//                  кв с 2 действ реш         квадр с комплексными реш
                    IDENTITY,  ERROR_CODE};
//                  тождество  код ошибки
enum eqTypes getEqType (double coeffSecPow, double coeffFirstPow, double coeffZeroPow, double discriminant);
double getDiscriminant (double coeffSecPow, double coeffFirstPow, double coeffZeroPow);
void getCoeffs (double *coeffSecPow, double *coeffFirstPow, double *coeffZeroPow);
void evaluateAndPrintSolutions (enum eqTypes eqType, double coeffSecPow, double coeffFirstPow, double coeffZeroPow, double discriminant);

int main ()
    {
    double coeffSecPow = 0, coeffFirstPow = 0, coeffZeroPow = 0; //коэффициенты уравнения вида coeffSecPowx^2 + coeffFirstPowx + coeffZeroPow = 0

    getCoeffs (&coeffSecPow, &coeffFirstPow, &coeffZeroPow);

    double discriminant = getDiscriminant (coeffSecPow, coeffFirstPow, coeffZeroPow);
    enum eqTypes eqType = getEqType (coeffSecPow, coeffFirstPow, coeffZeroPow, discriminant);

    evaluateAndPrintSolutions (eqType, coeffSecPow, coeffFirstPow, coeffZeroPow, discriminant);

    return 0;
    }

double getDiscriminant (double coeffSecPow, double coeffFirstPow, double coeffZeroPow)
    {
    return coeffFirstPow*coeffFirstPow - 4*coeffSecPow*coeffZeroPow;
    }

enum eqTypes getEqType (double coeffSecPow, double coeffFirstPow, double coeffZeroPow, double discriminant)
    {
    if (coeffSecPow == 0 && coeffFirstPow == 0)
        {
        if (coeffZeroPow == 0) return IDENTITY;
        else return NO_SOLUTIONS;
        }

    if (coeffSecPow == 0) return LINEAR;

    if (discriminant == 0) return SQR_ONE;

    if (discriminant > 0) return SQR_REAL;

    if (discriminant < 0) return SQR_COMPLEX;

    return ERROR_CODE;
    }

void getCoeffs (double *coeffSecPow, double *coeffFirstPow, double *coeffZeroPow)
    {
    printf ("Enter coefficient a:");
    scanf  ("%lg", &(*coeffSecPow));

    printf ("\nEnter coefficient b:");
    scanf  ("%lg", &(*coeffFirstPow));

    printf ("\nEnter coefficient c:");
    scanf  ("%lg", &(*coeffZeroPow));

    printf ("\n");
    }

void evaluateAndPrintSolutions (enum eqTypes eqType, double coeffSecPow, double coeffFirstPow, double coeffZeroPow, double discriminant)
    {
    switch (eqType)
        {
        case ERROR_CODE:
            {
            printf ("An error has occured, couldn't get the solutions");
            break;
            }

        case NO_SOLUTIONS:
            {
            printf ("This equation doesn't have any solutions");
            break;
            }

        case IDENTITY:
            {
            printf ("This equation has an infinite amount of solutions");
            break;
            }

        case LINEAR:
            {
            double solutionLinear = -coeffZeroPow/coeffFirstPow;
            printf ("This is a linear equation with 1 solution: %lg", solutionLinear);
            break;
            }

        case SQR_ONE:
            {
            double solutionSquare = -coeffFirstPow/(2*coeffSecPow);
            printf ("This is a quadratic equation with 1 solution: %lg", solutionSquare);
            break;
            }

        case SQR_REAL:
            {
            double solutions [2] = { (-coeffFirstPow - sqrt (discriminant)) / (2*coeffSecPow), (-coeffFirstPow + sqrt (discriminant))/(2*coeffSecPow) };
            printf ("This is a quadratic equation with two real solutions: {%lg, %lg}", solutions[0], solutions[1]);
            break;
            }

        case SQR_COMPLEX:
            {
            double realPart = -coeffFirstPow/(2*coeffSecPow);
            double imaginaryMultiplier = sqrt (-discriminant);
            printf ("This is a quadratic equation with two real solutions: {%lg - %lg*i, %lg + %lg*i}", realPart, imaginaryMultiplier, realPart, imaginaryMultiplier);
            break;
            }

        default: printf ("Wrong equation type");

        }
    }




/**/


