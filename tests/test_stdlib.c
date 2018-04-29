#include <test/unit.h>
#include <common/stdlib.h>
#include <common/stdio.h>

int tests_run __attribute__((section (".data"))) = 0;

static char *test_strlen() {
  mu_assert("Test failed: strlen(\"Hello\") != 5", strlen("Hello") == 5);
  mu_assert("Test failed: strlen(\"\") != 0", strlen("") == 0);
  mu_assert("Test failed: strlen(\"foo\\0\") != 3", strlen("foo\0") == 3);

	return 0;
}

static char *test_strcmp() {
	mu_assert("Test failed: strcmp(\"ABC\", \"ABC\") != 0", strcmp("ABC", "ABC") == 0);
	mu_assert("Test failed: strcmp(\"ABC\", \"BBC\") !< 0", strcmp("ABC", "BBC") < 0);
	mu_assert("Test failed: strcmp(\"BBC\", \"ABC\") !> 0", strcmp("BBC", "ABC") > 0);

	return 0;
}

static char *all_tests() {
	mu_run_test(test_strlen);
	mu_run_test(test_strcmp);

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
