#include "doubleMath.h"

double absMy (double val)
{
    MY_ASSERT (isfinite (val), "absMy recieved a NAN value in val");

    return (val > 0) ? val : -val;
}

bool isEqualDouble (double n1, double n2, double allowedError)
{
    MY_ASSERT (isfinite (n1), "absMy recieved a NAN value in n1");
    MY_ASSERT (isfinite (n2), "absMy recieved a NAN value in n2");

    return (absMy (n1-n2) < allowedError);
}

bool isGreaterDouble (double n1, double n2, double allowedError)
{
    MY_ASSERT (isfinite (n1), "absMy recieved a NAN value in n1");
    MY_ASSERT (isfinite (n2), "absMy recieved a NAN value in n2");

    return (n1-n2 > allowedError);
}

bool liesBetween (double number, double leftBorder, double rightBorder)
{
    MY_ASSERT (isfinite (number), "absMy recieved a NAN value in number");
    MY_ASSERT (isfinite (leftBorder), "absMy recieved a NAN value in leftBorder");
    MY_ASSERT (isfinite (leftBorder), "absMy recieved a NAN value in rightBorder");

    if (isGreaterDouble (leftBorder, rightBorder, STD_ERROR))
    {
        printf ("\nleftborder = %lg is greater than rightborder = %lg\n\n", leftBorder, rightBorder);
        return false;
    }

    return (number >= leftBorder && number <= rightBorder);
}
