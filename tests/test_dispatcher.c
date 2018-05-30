#include <minunit/unit.h>
#include <kernel/dispatcher.h>
#include <test_dispatcher.h>
#include <dispatcher.c>
#include <pcb.c>
#include <queue.c>

static char *test_dispatcher_init() {
	mem_init();
	dispatcher_init();

	//Assuming we are creating at least three processes p0, p1 and p2
	mu_assert("Test failed: ready_queue doesn't exist", ready_queue != NULL);

	//dispatcher_init() sets the first initialized process (p0 in this case) to running_process
	pcb_t *p0_test = running_process;

	mu_assert("Test failed: We don't have a running process after dispatcher_init", running_process != NULL);
	mu_assert("Test failed: p0 pid isn't correct", p0_test->pid == 0);
	mu_assert("Test failed: p0 starting pc isn't correct", p0_test->pc == process_0);
	mu_assert("Test failed: p0 process_state isn't 1 (running)", p0_test->process_state == 1);

	mu_assert("Test failed: p0 doesn't have an address to its cpu_context", p0_test->cpu_context != NULL);
	mu_assert("Test failed: p0 doesn't have a stack", p0_test->stack != NULL);

	mu_assert("Test failed: p0 sp isn't correct", p0_test->cpu_context->sp == (reg_t)(p0_test->stack + PROCESS_STACKSIZE));

	mu_assert("Test failed: ready_queue is empty", ready_queue->first != NULL);
	return 0;
}

char *test_dispatcher() {
	mu_run_test(test_dispatcher_init);

	return 0;
}
