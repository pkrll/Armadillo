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

static char *test_number_to_char() {
	mu_assert("Test failed: number_to_char(\"0\") != '0'", strcmp(number_to_char(0), "0") == 0);
	mu_assert("Test failed: number_to_char(\"1234\")[2] != '1234'", strcmp(number_to_char(1234), "4321") != 0);
	mu_assert("Test failed: number_to_char(\"1234\")[2] != '1234'", strcmp(number_to_char(1234), "1234") == 0);
	mu_assert("Test failed: number_to_char(\"1204\")[3] != '1204'", strcmp(number_to_char(1204), "1204") == 0);
	mu_assert("Test failed: number_to_char(\"1230\") != '1230'", strcmp(number_to_char(1230), "1230") == 0);
	mu_assert("Test failed: number_to_char(\"1230\") != '200'", strcmp(number_to_char(200), "200") == 0);


	return 0;
}

char *test_stdlib() {
	mu_run_test(test_strlen);
	mu_run_test(test_strcmp);
	mu_run_test(test_number_to_char);
	return 0;
}
