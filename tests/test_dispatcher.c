#include <minunit/unit.h>
#include <kernel/dispatcher.h>
#include <common/processes.h>
#include <common/queue.h>
#include <kernel/pcb.h>
#include <test_dispatcher.h>
#include <dispatcher.c>

static char *test_dispatcher_init() {
	mem_init();
	dispatcher_init();

	//Assuming we are creating at least three processes p0, p1 and p2
	mu_assert("Test failed: ready_queue doesn't exist", ready_queue != NULL);

	//dispatcher_init() sets the first initialized process (p0 in this case) to running_process
	pcb_t *p0_test = running_process;

	mu_assert("Test failed: We don't have a running process after dispatcher_init", running_process != NULL);
	mu_assert("Test failed: p0 pid isn't correct", get_pid(p0_test) == 1);

	mu_assert("Test failed: p0 starting pc isn't correct", get_pc(p0_test) == process_1);
	mu_assert("Test failed: p0 process_state isn't 1 (running)", get_pcb_state(p0_test) == 1);

	mu_assert("Test failed: p0 doesn't have an address to its cpu_context", get_context(p0_test) != NULL);

	mu_assert("Test failed: ready_queue is empty", queue_front(ready_queue) != NULL);
	return 0;
}

char *test_dispatcher() {
	mu_run_test(test_dispatcher_init);

	return 0;
}
