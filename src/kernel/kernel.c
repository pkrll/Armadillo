#include <common/stdlib.h>
#include <common/stdio.h>

void start_counter() {
	while (1) {
		for (int i = 1; i < 10; i++) {
			for (int i = 0; i < 100000000; i++) { /* Pause... */ }

			if (i == 9) {
				asm volatile("li $a0, 0x1;" "syscall");
			} else {
				print_to_led(i);
			}

		}
	}
}

int main(void) {
	// printk("Hello world!\n");
	// print_to_ascii("UphillOS");
	// start_counter();
	mem_init();
	char *array = malloc(sizeof(char)*3);
	array[0] = 'a';
	array[1] = '\n';
	array[2] = '\0';
	printk(array);

	char *array2 = malloc(sizeof(char)*3);
	array2[0] = 'b';
	array2[1] = '\n';
	array2[2] = '\0';
	printk(array2);

	char *array3 = malloc(sizeof(char)*3);
	array3[0] = 'c';
	array3[1] = '\n';
	array3[2] = '\0';
	printk(array3);

	free(array3);

	char *array4 = malloc(sizeof(char)*3);
	array4[0] = 'X';
	array4[1] = '\n';
	array4[2] = '\0';

	printk(array3);
	// Should print 'X', which has been written at the adress of array2 ('c').

	free(array2);
	free(array);

	char *nothing = malloc(sizeof(char)*20);
	nothing += 1;
	// Should use 'new' memory since 20 > 8, which is the size of the freed blocks 'array' and 'array2'.

	char *array5 = malloc(sizeof(char)*3);
	array5[0] = 'A';
	array5[1] = '\n';
	array5[2] = '\0';

	char *array6 = malloc(sizeof(char)*3);
	array6[0] = 'B';
	array6[1] = '\n';
	array6[2] = '\0';

	printk(array);
	// Should print 'A', which has been written at adress of array ('a').
	printk(array2);
	// Should print 'B', which has been written at adress of array ('b').

	return 0;
}

void exception_handler() {
	printk("Nope");
}
