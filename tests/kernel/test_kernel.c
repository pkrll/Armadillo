#include <minunit/unit.h>
#include <common/stdio.h>

int main(void) {
	printk("\n================== Unit tests ==================\n");
	char *result = all_tests();

	if (result != 0) {
		printk(result);
	} else {
		printk("All tests passed!");
	}

	printk("\n===============================================\n");

	return 0;
}
