/**
 * @file
 * @brief Math
 */

#ifndef __MATH_H__
#define __MATH_H__

/**
 * Returns the absolute value of the specified integer.
 *
 * @param  n The integer to convert.
 * @return   The absolut value of n.
 */
#define abs(n) 		__builtin_abs 	((n))
/**
 * Rounds a floating point number down.
 *
 * @param  f The floating point number to round down.
 * @return   f rounded down to its largest integral value.
 */
#define floor(f) 	__builtin_floor ((f))
/**
 * Returns the smallest integer value greater than or equal to x.
 *
 * @param  f The floating point number to round up.
 * @return   The smallest integer value greater than or equal to x.
 */
#define ceil(f)		__builtin_ceil	((f))
/**
 * Calculates the value of e raised to the power of x.
 *
 * @param  x The value to raise e by.
 * @return   The value of e rasied to the power of x.
 */
#define exp(x)		__builtin_exp		((x))
/**
 * Returns the common logarithm (base-10 logarithm) of x.
 *
 * @param  x Value whose logarithm is calculated.
 * @return   The common logarithm of x.
 */
#define log10(x)	__builtin_log10		((x))

#endif
