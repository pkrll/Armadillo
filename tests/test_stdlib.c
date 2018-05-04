#include <munit/unit.h>
#include <common/stdlib.h>
#include <test_stdlib.h>

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

char *test_stdlib() {
	mu_run_test(test_strlen);
	mu_run_test(test_strcmp);

	return 0;
}
