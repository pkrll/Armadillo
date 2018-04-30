/**
 * @file
 * @brief MinUnit -- a minimal unit testing framework for C.
 * 				Adapted from http://www.jera.com/techinfo/jtns/jtn002.html
 */
#ifndef __UNIT_H__
#define __UNIT_H__

#include <common/stdio.h>

extern int tests_run __attribute__ ((section(".data")));
extern int suite_run __attribute__ ((section(".data")));

char *all_tests();

#define mu_assert(message, test) do { \
	if (!(test)) return message; \
} while (0)

#define mu_run_test(test) do { \
	char *message = test(); \
	tests_run++; \
	if (message) return message; \
} while (0)

#define mu_run_suite(suite, suite_name) do { \
	char *message = suite(); \
	suite_run++; \
	if (message) { \
		printk("Test suite "); \
		printk(suite_name); \
		printk(" FAILED!\n"); \
		return message; \
	} \
	printk("Test suite "); \
	printk(suite_name); \
	printk(" passed!\n"); \
} while (0)

#endif
