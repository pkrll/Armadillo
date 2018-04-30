#include <test/unit.h>
#include <common/stdlib.h>
#include <common/stdio.h>
#include <common/memory.h>

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

static char *test_malloc() {

  mem_init();
  
  char *a = malloc(sizeof(char));
  free(a);
  char *b = malloc(sizeof(char));
  mu_assert("Test failed: adress of (a != b)", a == b);

  int *c = malloc(sizeof(int));
  *c = 42;
  free(c);
  int *d = malloc(sizeof(int));
  mu_assert("Test failed: adress of (c != d)", c == d);
  mu_assert("Test failed: *d != '\0'", *d == '\0');
  
  int N = 100000;
  char *array = malloc(sizeof(char)*N);
  for (int i = 0; i < N; i++) {
    mu_assert("Test failed: Memory allocated not null", *array == '\0');
    array += 1;
  }
  
  return 0;
}

static char *test_free() {

  mem_init();
  
  char *a1 = malloc(sizeof(char));
  char *a2 = malloc(sizeof(char));
  free(a1);
  char *a3 = malloc(sizeof(char));
 
  mu_assert("Test failed: adress of (a1 != a3)", a1 == a3);

  free(a2);
  free(a3);
  char *a4 = malloc(sizeof(char)*100);          
  char *a5 = malloc(sizeof(char));
  char *a6 = malloc(sizeof(char));

  mu_assert("Test failed: a5 >= a4", a5 < a4);
  mu_assert("Test failed: a5 >= a4", a6 < a4);

  return 0;
}

static char *all_tests() {
	mu_run_test(test_strlen);
	mu_run_test(test_strcmp);
        mu_run_test(test_malloc);
        mu_run_test(test_free);

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
