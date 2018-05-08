#include <common/stdlib.h>
#include <common/memory.h>
#include <common/math.h>

int strlen(const char *str) {
	int count = 0;

	while (str[count]) {
		count += 1;
	}

	return count;
}

int strcmp(const char *str1, const char *str2) {
	while (*str1) {
		if (*str2 == '\0') return 1;
		if (*str2 > *str1) return -1;
		if (*str2 < *str1) return 1;

		str1++;
		str2++;
	}

	return (*str2 == '\0') ? 0 : -1;
}

char itoa(int n) {
  return (char)n + '0';
}

int length_of_number(int number) {
	int count = 0;

  while (number > 0) {
    number = number / 10;
    ++count;
  }

  return count;
}

char *number_to_char(int number) {
  if (number == 0) return "0";

  int size = length_of_number(number);
  char *array = malloc(sizeof(char) * size + 1);

  for (int i = 0; i < size; i++) {
    array[(size - 1) - i] = itoa(number % 10);
    number = number / 10;
  }

  array[size + 1] = '\0';

	return array;
}
