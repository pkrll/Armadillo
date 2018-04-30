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

#endif
