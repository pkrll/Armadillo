#include <munit/unit.h>
#include <common/stdlib.h>
#include <common/stdio.h>
#include <test_memory.h>
#include <test_stdlib.h>

int tests_run __attribute__ ((section(".data"))) = 0;
int suite_run __attribute__ ((section(".data"))) = 0;

static char *all_tests() {
	mu_run_suite(test_memory, "test_memory");
	mu_run_suite(test_stdlib, "test_stdlib");

	return 0;
}

int main(void) {
	printk("\n================== Unit tests ==================\n");
	char *result = all_tests();

	if (result != 0) {
		printk(result);
	} else {
		printk("All tests passed!");
	}

	printk("\n===============================================\n");

	return 0;
}
