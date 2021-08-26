/** \file
    \brief Header file with defenitions of floatmath functions**/

#pragma once

#include "myAssert.h"

///Function that returns an absolute value of number val
double absMy (double val///< - The number which you get the absolute value of
            );

///This function is necessary in order to compare double value numbers that may differ by a certain error (The error is usually accumulated due to double numbers value). Returns a boolean value.
bool isEqualDouble (double n1 /**< - first number*/, double n2 /**< - second number*/, double allowedError /**< - accuracy*/);

///Function that determines if the number n1 is bigger than number n2 by a margin of a certain error (The error is usually accumulated due to double numbers value). Returns a boolean value.
bool isGreaterDouble (double n1 /**< - first number*/, double n2 /**< - second number*/, double allowedError /**< - accuracy*/);

///Function that checks if number lies in a certain range - [leftBorder, rightBorder]. Returns a boolean value. Returns false if leftBorder is bigger than rightBorder
bool liesBetween (double number ///< - The number
                , double leftBorder ///< - The left border of the range
                , double rightBorder ///< - The right border of the range
                );

///Standard error for double values
const double STD_ERROR = 1e-10;
