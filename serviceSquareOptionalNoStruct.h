/** \file
    \brief Header file with defenitions of functions that work with the square equation**/

/**\mainpage This is a small programm that Solves the quadratic equations*/

#pragma once

#include "doubleMath.h"
///An enum constant that is used to mark the number of solutions the equation has.
enum eqTypes {NO_SOLUTIONS///< - The equation has no solutions
            , ONE_SOLUTION///< - The equation has one solution
            , TWO_SOLUTIONS///< - The equation has two solutions
            , INF_SOLUTIONS///< - The equation has an infinite amount of solutions
            , ERROR_CODE///< - An error that indicates that the type couldn't be determined in the right way
            };

///Function that evaluates the discriminant of a square equation and returns it as a double value. Recieves coefficients of the equation a*x^2 + b*x + c = 0.
double evalDiscriminant (double a,/**< - The coefficient by the second power (a*x^2)*/
                         double b,/**< - The coefficient by the first power (b*x)*/
                         double c/**< - The coefficient by the zero power (c)*/);

///Function that recieves coefficients of an equation a*x^2 + b*x + c = 0 through user input. The coefficients are of the equation a*x^2 + b*x + c = 0.
void getCoeffs (double* a/**< - Pointer to the coefficient a*/,
                double* b/**< - Pointer to the coefficient b*/,
                double* c/**< - Pointer to the coefficient c*/);

///Function prints the solutions of the equation. The format of the output depends on the equation type that the function recieves through its parameters. Doesn't return any value.
void printSolutions (enum eqTypes eqType/**< - The equation type that is used to determine the format of output*/,
                     double root1/**< - The first root of the equaiton*/,
                     double root2/**< - The second root of the equation*/);

///Function solves a linear equation tha looks like this: kx + b = 0. Doesn't return any value. Puts the solution of the equation into the adress root.
void solveLinear (double k/**< - Coefficient by the first power*/,
                  double b/**< - Coefficient by the zero power*/,
                  double* root/**The pointer to root variable that stores the solution*/);

///Function that solves a square equation that looks like this: a*x^2 + b*x + c = 0. Returns the type of the equation that was solved. The types are listed in enum eqTypes.
enum eqTypes solveSquare (double a/**< - The coefficient by the second power (a*x^2)*/,
                          double b/**< - The coefficient by the first power (b*x)*/,
                          double c/**< - The coefficient by the first power (b*x)*/,
                          double* root1/**< - Pointer to the root1 value that stores one of the roots*/,
                          double* root2/**< - Pointer to the root2 value that stores one of the roots*/);

//Function that cleans the buffer until it meets the \n escape sequence. Is used to optimize the input in getCoeffs().
//Cannot be used in other files. To know how it works check the function body in serviceSquareOptionalNoStruct.c
static inline void cleanBuffer ();

