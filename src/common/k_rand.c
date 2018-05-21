#include <common/k_rand.h>

extern int __rand();
static int seed __attribute__((section (".data")));

int rand(int max) {
	int i = __rand();
	i = i % (max + 1);

	return i;
}

void rand_init() {
	seed = __rand();
}

int krand(int max) {
	unsigned int next = seed;
	int result;
  next *= 1103515245;
  next += 12345;
  result = (unsigned int) (next / 65536) % 2048;

  next *= 1103515245;
  next += 12345;
  result <<= 10;
  result ^= (unsigned int) (next / 65536) % 1024;

  next *= 1103515245;
  next += 12345;
  result <<= 10;
  result ^= (unsigned int) (next / 65536) % 1024;

  seed = next;

  return result % max;
}
