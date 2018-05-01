#include <munit/unit.h>
#include <test_memory.h>
#include <test_stdlib.h>

int tests_run __attribute__ ((section(".data"))) = 0;
int suite_run __attribute__ ((section(".data"))) = 0;

char *all_tests() {
	mu_run_suite(test_memory, "test_memory");
	mu_run_suite(test_stdlib, "test_stdlib");

	return 0;
}
