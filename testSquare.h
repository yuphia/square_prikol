/**\file testSquare.h
   \brief This file coontains simple functions that are used to test solveEquation()*/

#include "serviceSquareOptionalNoStruct.h"
#include <errno.h>

///An enum constant that represents different error codes that are used throughout the test file
enum errorCodes
{
    SUCCESS/**< - No errors occured*/,
    WRONG_SOLUTION/**< - A test has captured wrong solutions to the equation evaluated by solveSquare()*/,
    WRONG_EQTYPE/**< - A test has captured wrong eqType returned by solveSquare()*/
};
///Functions that calls minor test functions. Returns the number of errors.
int testSquare();

///Function that recieves coefficients of the equation a*x^2 + b*x + c = 0. It calls solveSquare() and compares its outputs to other parameters.
enum errorCodes testPrototype (double a/**< - Coefficient of the second power (a*x^2)*/,
                               double b/**< - Coefficient of the first power (b*x)*/,
                               double c/**< - Coefficients of the zero power (c)*/,
                               double wantedRoot1/**< - The root that is expected to be returned by solveSquare()*/,
                               double wantedRoot2/**< - The root that is expected to be returned by solveSquare()*/,
                               enum eqTypes wantedEqType/**< - The eqType that is expected to be returned by solveSquare()*/);

/// Function that tests a special case of an equation with one solution
enum errorCodes testOneSolution ();

/// Function that tests a special case of an equation with infinite solutions
enum errorCodes testInfinite ();

/// Function that tests a special case of an equation with no solutions
enum errorCodes testNoSolutions ();

/// Function that tests a special case of an equation with two solutions
enum errorCodes testTwoSolutions ();


int testSquare()
{
    int errorCount = 0;

    if (testInfinite() != SUCCESS)
        errorCount++;

    if (testNoSolutions() != SUCCESS)
        errorCount++;

    if (testTwoSolutions () != SUCCESS)
        errorCount++;

    if (testOneSolution () != SUCCESS)
        errorCount++;

    return errorCount;
}

enum errorCodes testPrototype (double a, double b, double c, double wantedRoot1, double wantedRoot2, enum eqTypes wantedEqType)
{
    double testRoot1 = 0, testRoot2 = 0;

    enum eqTypes eqType = solveSquare (a, b, c, &testRoot1, &testRoot2);

    if (!isEqualDouble (testRoot1, wantedRoot1, STD_ERROR) || !isEqualDouble (testRoot2, wantedRoot2, STD_ERROR))
    {
        printf ("\n\n\nWrong solutions while testing for roots:\ngot %lg, %lg but wanted %lg, %lg\n", testRoot1, testRoot2, wantedRoot1, wantedRoot2);
        return WRONG_SOLUTION;
    }

    if (eqType != wantedEqType)
    {
        printf ("\n\n\nWrong eqType while testing for type,\ngot type %d but wanted %d\n", eqType, wantedEqType);
        return WRONG_EQTYPE;
    }
    return SUCCESS;
}

enum errorCodes testInfinite ()
{
    enum errorCodes errorCode = testPrototype (0, 0, 0, 0, 0, INF_SOLUTIONS);

    if (errorCode != SUCCESS)
        printf ("This test got caught while testing in function %s\n\n\n", __PRETTY_FUNCTION__);

    return errorCode;
}

enum errorCodes testNoSolutions ()
{
    enum errorCodes errorCode = testPrototype (0, 0, 1, 0, 0, NO_SOLUTIONS);

    if (errorCode != SUCCESS)
    {
        printf ("This test got caught while testing in function %s\n\n\n", __PRETTY_FUNCTION__);
        return errorCode;
    }

    errorCode = testPrototype (1, -1, 1, 0, 0, NO_SOLUTIONS);

    return errorCode;
}

enum errorCodes testOneSolution ()
{
    enum errorCodes errorCode = testPrototype (1, 2, 1, -1, -1, ONE_SOLUTION);

    if (errorCode != SUCCESS)
    {
        printf ("This test got caught while testing in function %s\n\n\n", __PRETTY_FUNCTION__);
        return errorCode;
    }
    /////////////////////
    errorCode = testPrototype (0, 1, 2, -2, -2, ONE_SOLUTION);

    return errorCode;
}

enum errorCodes testTwoSolutions ()
{
    enum errorCodes errorCode = testPrototype (1, 5, 6, -3, -2, TWO_SOLUTIONS);

    return errorCode;
}

