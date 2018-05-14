#include <common/processes.h>
#include <common/stdlib.h>
#include <common/dispatcher.h>

void delay() {
  for (int i = 1; i < 100000000; i++);
}

void process_5(){
	while (1) {
		delay();
		printk("5");
		asm volatile("syscall");
	}
}

void process_4(){
	while (1) {
		delay();
		printk("4");
		asm volatile("syscall");
	}
}

void process_3(){
	while (1) {
		delay();
		printk("3");
		asm volatile("syscall");
	}
}

/*
*	Workspace for process 2
*/
void process_2(){
	while (1) {
    for (int i = 1; i < 100000000; i++); //delay();
    printk("PROCESS_2\n");
	}
}

/*
*	Workspace for process 1
*/
void process_1(){
	while (1) {
		for (int i = 1; i < 100000000; i++); //delay();
		printk("#Initializing process 1, counting up to 5...\n");
    for (int i = 1; i < 100000000; i++); //delay();
    printk("1\n");
    for (int i = 1; i < 100000000; i++); //delay();
    printk("2\n");
    for (int i = 1; i < 100000000; i++); //delay();
    printk("3\n");
    for (int i = 1; i < 100000000; i++); //delay();
    printk("error...\n");
    //asm volatile("syscall");
	}
}

/*
*	Workspace for process 0
*/
void process_0(){
  spawn_process(process_2);
  while (1) {
    for (int i = 1; i < 100000000; i++); //delay(); funkar ej, blir något exception
    printk("#Initializes process 0, calculating 1 + 1...");
    for (int i = 1; i < 100000000; i++); //delay();
    printk(" = 2 \n");
		//asm volatile("syscall");
	}
}
