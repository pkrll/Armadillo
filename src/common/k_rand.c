#include <common/k_rand.h>
extern int _random_number();

int rand(int max) {
  int i = _random_number();
  i = i % (max + 1);

  return i;
}
