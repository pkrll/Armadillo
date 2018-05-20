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

char htoa(unsigned long n) {
	if (n > 9 && n < 17) {
		n = 39 + n;
	}

	return (char)n + '0';
}

int length_of_number(unsigned long number, int base) {
	int count = 0;

	while (number > 0) {
		number = number / base;
		++count;
	}

	return count;
}

char *number_to_char(int number) {
	if (number == 0) return "0";

	int size = length_of_number(number, 10);
	char *array = malloc(sizeof(char) * size + 1);

	for (int i = 0; i < size; i++) {
		array[(size - 1) - i] = itoa(number % 10);
		number = number / 10;
	}

	array[size + 1] = '\0';

	return array;
}

char *hexadecimal_to_char(unsigned long number) {
	if (number == 0) return "0";

	int size = length_of_number(number, 16) + 3;
	char *array = malloc(sizeof(char) * size);

	for (int i = 2; i < size; i++) {
		array[size - i] = htoa(number % 16);
		number = number / 16;
	}

	array[0] = '0';
	array[1] = 'x';
	array[size + 1] = '\0';

	return array;
}
