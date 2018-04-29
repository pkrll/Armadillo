#ifndef __UNIT_H__
#define __UNIT_H__

/**
 * MinUnit -- a minimal unit testing framework for C
 * http://www.jera.com/techinfo/jtns/jtn002.html
 */
#define mu_assert(message, test) do { \
	if (!(test)) return message; \
} while (0)
#define mu_run_test(test) do { \
	char *message = test(); \
	tests_run++; \
	if (message) return message; \
} while (0)

extern int tests_run;

#endif
