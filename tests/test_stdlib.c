#include <test/unit.h>
#include <common/stdlib.h>
#include <common/stdio.h>

int tests_run __attribute__((section (".data"))) = 0;

static char *test_strlen() {
  mu_assert("error, strlen(\"Hello\") != 5", strlen("Hello") == 5);
  mu_assert("error, strlen(\"\") != 0", strlen("") == 0);

	return 0;
}

static char *all_tests() {
	mu_run_test(test_strlen);

	return 0;
}

int main() {
	char *result = all_tests();

	if (result != 0) {
		printk(result);
	} else {
		printk("All tests passed!\n");
	}

	return 0;
}
