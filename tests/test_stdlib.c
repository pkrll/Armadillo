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
	mu_assert("Test failed: number_to_char(\"0\") != '0'", *number_to_char(0) == '0');
	mu_assert("Test failed: number_to_char(\"1234\")[2] != '1234'", number_to_char(1234)[2] == '3');
	mu_assert("Test failed: number_to_char(\"1034\")[1] != '1034'", number_to_char(1034)[1] == '0');
	mu_assert("Test failed: number_to_char(\"1204\")[3] != '1204'", number_to_char(1204)[3] == '4');
	mu_assert("Test failed: number_to_char(\"1230\")[0] != '1230'", number_to_char(1230)[0] == '1');

	return 0;
}

char *test_stdlib() {
	mu_run_test(test_strlen);
	mu_run_test(test_strcmp);
	mu_run_test(test_number_to_char);
	return 0;
}
