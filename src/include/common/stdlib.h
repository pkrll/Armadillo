
char itoa(int n);
/**
 * Compares the string pointed to by str1 with the string
 * pointed to by str2.
 *
 * @param  str1 The first string to be compared.
 * @param  str2 The second string to be compared.
 *
 * @return      If the return value is below 0, then str1
 * 							is less than str2; if the return value is
 * 							above 0 then str1 is larger than str2. If
 * 							the return value is 0, then str1 is equal
 * 							to str2.
 */
int strcmp(const char *str1, const char *str2);
/**
 * Returns the length of the string. Does not include \0.
 *
 * @param  str The string to count.
 * @return     The length of the string.
 */
int strlen(const char *str);
