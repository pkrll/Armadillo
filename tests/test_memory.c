#include <munit/unit.h>
#include <common/memory.h>
#include <test_memory.h>

static char *test_malloc() {
  char *a = malloc(sizeof(char));
	char *b = malloc(sizeof(char));
	mu_assert("Test failed: adress of (a == b)", a != b);

  free(a);
  char *e = malloc(sizeof(char));
  mu_assert("Test failed: adress of (a != e)", a == e);

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

char *test_memory() {
	mem_init();

	mu_run_test(test_malloc);
	mu_run_test(test_free);

	return 0;
}
