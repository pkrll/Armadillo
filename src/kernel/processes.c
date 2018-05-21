#include <common/processes.h>
#include <common/stdlib.h>
#include <kernel/dispatcher.h>
#include <kernel/syscall.h>
#include <common/k_rand.h>
#include <kernel/pcb.h>

#define wait(x) for (int _i = 0; _i < x; _i++);

void *processes[4] = {
	process_1,
	triangle_numbers,
	square_numbers,
	fibonacci
};

void delay() {
	for (int i = 0; i < 250000000; i++);
}

void launch() {
	int random = 0;

	for (int i = 0; i < 4; i++) {
		random = krand(1000000);
		wait(random);

		printf("\n==================\nSpawning process %d\n==================\n", i);
		spawn_process(processes[i]);
		void (*func)() = processes[i];
		func();

	}

	printf("\n==================\nLaunch is done!\n==================\n");
}

void process_1() {
	printf("\n==================\nPrinting 1..10\n==================\n");
	for (int i = 0; i < 10; i++) {
		int random = krand(100000000);
		for (int i = 0; i < random; i++); //delay
		printf("%d, ", i+1);
	}

	make_io_request();

	printf("\n==================\nDone printing 1..10\n==================\n");

	exit();
}

void fibonacci() {
	int n = 47; // More than that we get overflow...
	unsigned long f1 = 0;
	unsigned long f2 = 1;
	unsigned long next = 0;

	printf("\n==================\nPrinting the first %d terms of the Fibonacci series...\n==================\n", n);
	for (int i = 0; i < n; i++) {
		printf("%d, ", f1);
		next = f1 + f2;
		f1 = f2;
		f2 = next;

		int random = krand(100000000);
		wait(random);
	}

	printf("\n==================\nDone printing the fibonacci series\n==================\n\n");

	// spawn_process(fibonacci);

	exit();
}

void square_numbers() {
	int n = 1000;
	int x = 0;
	int s = 1;
	printf("\n==================\nPrinting the square numbers\n==================\n");
	for (int i = 0; i < n; i++, x = 2 * i + 1) {
		s = s + x;
		printf("%d ", s);

		int random = krand(100000000);
		wait(random);
	}

	printf("\n==================\nDone printing the square numbers\n==================\n\n");
	exit();
}

void triangle_numbers() {
	int n = 1000;
	int last = 1;
	printf("\n==================\nPrinting the triangle numbers\n==================\n\n");
	for (int i = 0; i < n; i++) {
		last = last + i;
		printf("%d ", i + last);

		int random = krand(100000000);
		wait(random);
	}

	printf("\n==================\nDone printing the triangle numbers\n==================\n\n");

	exit();
}
