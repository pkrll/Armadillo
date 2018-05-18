#ifndef __K_RAND_H_
#define __K_RAND_H_

/**
 * Take the current number from the C0_COUNT register and then mod it with maximum
 *
 * @param  maximum    The maximum number rand will return
 *
 * @return A random number between 0 and maximum
 */
int rand(int maximum);

#endif
