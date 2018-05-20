#include <kernel/dispatcher.h>
#include <common/stdlib.h>
#include <common/processes.h>
#include <kernel/pcb.h>

// -------------------------------
// Declarations
// -------------------------------

static queue_t *ready_queue __attribute__((section(".data")));
__attribute__((unused))static pcb_t *running_process __attribute__((section(".data")));
static pid_t pid __attribute__((section("data"))) = 1;

/**
 * Sets the specified process as the running process, and changing
 * its state to running.
 *
 * @param process The PCB of the process to set to running.
 */
void set_running_process(pcb_t *process);
/**
 * Initializes all processes by assigning PIDs, starting functions
 * and adding them to the ready queue.
 *
 * One process is assigned as the running process and its starting
 * function is called.
 */
void init_processes();
/**
 * Sets the running process' state to terminated.
 */
void terminate_process();
/**
 * Returns the PC for the currently running process.
 *
 * @return The PC of the running process.
 */
addr_t get_running_pc();
/**
 * Returns the context of the currently running process.
 *
 * @return The context of the running process.
 */
context_t *get_current_context();

// -------------------------------
// Public functions
// -------------------------------

void spawn_process(void *process_function) {
	pcb_t *process = init_pcb(pid, process_function);
	pid++;

	if (list_size(ready_queue) == 0 && running_process == NULL) {
		set_running_process(process);
	} else {
		enqueue(ready_queue, process);
	}
}

void dispatcher_init() {
	ready_queue = queue_new();
	init_processes();
}

void process_switch() {
	if (get_pcb_state(running_process) != terminated) {
		enqueue(ready_queue, running_process);
	}
	pcb_t *next = dequeue(ready_queue);
	set_pcb_state(next, running);
	running_process = next;
}

pcb_t *get_current_pcb() {
	return running_process;
}

// -------------------------------
// Internal functions
// -------------------------------

void set_running_process(pcb_t *process) {
	running_process = process;
	set_pcb_state(process, 1);
}

void init_processes() {
	spawn_process(process_1);
	spawn_process(process_2);
	// spawn_process(process_3);
}

void terminate_process() {
	set_pcb_state(running_process, terminated); //Set state to terminated
}

addr_t get_running_pc() {
	return get_pc(running_process);
}

context_t *get_current_context() {
	return get_context(running_process);
}
