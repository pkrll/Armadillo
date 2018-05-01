#include <common/stdlib.h>

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
