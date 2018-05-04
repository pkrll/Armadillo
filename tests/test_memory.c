#include <munit/unit.h>
#include <common/memory.h>
#include <test_memory.h>

static char *test_malloc() {

  mem_init();
  
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


  return 0;
}

static char *test_memory_access() {

  mem_init();

  int N1 = 10000;
  size_t size = sizeof(char)*N1;
  char *array[7];
  array[0] = malloc(size);
  array[1] = malloc(size);
  array[2] = malloc(size);
  array[3] = malloc(size);
  array[4] = malloc(size);
  array[5] = malloc(size);
  array[6] = malloc(size);

  // Writing to memory
  for (int i = 0; i < 7; i++) {
    char C = 'A';
    char *start_block = array[i];
    for (i = 0; i < N1; i++) {
      *start_block = C;
    }
    C += 1;
  }

  // Reading memory
  for (int i = 0; i < 7; i++) {
    char C = 'A';
    char *start_block = array[i];
    for (i = 0; i < N1; i++) {
      mu_assert("Test failed: Invalid memory access.", *start_block == C);
    }
    C += 1;
  }
  


  return 0;
}

static char *test_memory_null() {

  mem_init();
  
  int N = 10000;
  
  char *array = malloc(sizeof(char)*N);
  char *incr = array;
  for (int i = 0; i < N; i++) {
    *incr = 'a';
    incr += 1;
  }

  free(array);
  
  char *array2 = malloc(sizeof(char)*N);
  incr = array2;
  for (int i = 0; i < N; i++) {
    mu_assert("Test failed: Memory allocated not null", *array2 == 0);
    incr += 1;
  }
  mu_assert("Test failed: adress of (array != array2).", array == array2);

 
  return 0;
}

static char *test_memory_align() {

  mem_init();

  char *array1 = malloc(sizeof(char)*47);
  char *array2 = malloc(sizeof(char)*97);
  size_t ptr1 = ((uint32_t)array1) % get_align_size();
  size_t ptr2 = ((uint32_t)array2) % get_align_size();
  mu_assert("Test failed: Memory not aligned.", ptr1 == 0);
  mu_assert("Test failed: Memory not aligned.", ptr2 == 0);
  mu_assert("Test failed: Memory not aligned.", ptr2-ptr1 == 0);
  
  int *array3 = malloc(sizeof(int)*11);
  int *array4 = malloc(sizeof(int)*23);
  size_t ptr3 = ((uint32_t)array3) % get_align_size();
  size_t ptr4 = ((uint32_t)array4) % get_align_size();
  mu_assert("Test failed: Memory not aligned.", ptr3 == 0);
  mu_assert("Test failed: Memory not aligned.", ptr4 == 0);
  mu_assert("Test failed: Memory not aligned.", ptr4-ptr3 == 0);

  uint32_t *array5 = malloc(sizeof(uint32_t)*7);
  uint32_t *array6 = malloc(sizeof(uint32_t)*17);
  size_t ptr5 = ((uint32_t)array5) % get_align_size();
  size_t ptr6 = ((uint32_t)array6) % get_align_size();
  mu_assert("Test failed: Memory not aligned.", ptr5 == 0);
  mu_assert("Test failed: Memory not aligned.", ptr6 == 0);
  mu_assert("Test failed: Memory not aligned.", ptr6-ptr5 == 0);
  
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

  char *a4 = malloc(sizeof(char)*10000);
  char *a5 = malloc(sizeof(char));
  char *a6 = malloc(sizeof(char));

  mu_assert("Test failed: a5 >= a4", a5 < a4);
  mu_assert("Test failed: a5 >= a4", a6 < a4);
  
  
  
  return 0;
}

static char *test_reallocate() {

  mem_init();

  int N = 1000;
  // OBS N > 6000 ger typ stack overflow ?!?
  char *array[N];
    
  for (int i = 0; i < N; i++) {
    array[i] = malloc(sizeof(char));
  }
  for (int i = 0; i < N; i++) {
    free(array[i]);
  }
  for (int i = 0; i < N; i++) {
    uint32_t reused_mem = (uint32_t)malloc(sizeof(char));
    mu_assert("Test failed: Free not reallocating properly.", reused_mem <= (uint32_t)array[N-1]);
  }

  mem_init();

  char *a1 = malloc(sizeof(char));
  char *a2 = malloc(sizeof(char));
  char *a3 = malloc(sizeof(char)*5000);  // Should be more than 1 page.
  char *a4 = malloc(sizeof(char));
  char *a5 = malloc(sizeof(char));
  free(a1);
  free(a2);
  free(a3);
  free(a4);
  free(a5);
  char *r1 = malloc(sizeof(char)*5000);
  char *r2 = malloc(sizeof(char));
  char *r3 = malloc(sizeof(char));
  char *r4 = malloc(sizeof(char));
  char *r5 = malloc(sizeof(char));
  mu_assert("Test failed: Free not reallocating properly.", r1 == a3);
  mu_assert("Test failed: Free not reallocating properly.", r1 < r2);
  mu_assert("Test failed: Free not reallocating properly.", r1 < r3);
  mu_assert("Test failed: Free not reallocating properly.", r1 > r4);
  mu_assert("Test failed: Free not reallocating properly.", r1 > r5);
  
  return 0;
}

char *test_memory() {

  mu_run_test(test_malloc);
  mu_run_test(test_memory_access);
  mu_run_test(test_memory_null);
  mu_run_test(test_memory_align);
  mu_run_test(test_free);
  mu_run_test(test_reallocate);

  return 0;
}
