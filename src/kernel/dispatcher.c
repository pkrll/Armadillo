#include <kernel/dispatcher.h>
#include <common/stdlib.h>
#include <common/processes.h>
#include <kernel/pcb.h>

static queue_t *ready_queue __attribute__((section(".data")));
__attribute__((unused))static pcb_t *running_process __attribute__((section(".data")));
static pid_t pid __attribute__((section("data"))) = 1;


/*
*	@brief Set the process as the running_process and changing the processes state to 1 (running)
*
*/
void set_running_process(pcb_t *process) {
	running_process = process;
	set_pcb_state(process, 1);
}

void spawn_process(void *process_function) {
  pcb_t *process = init_pcb(pid, process_function);
  pid++;

  if (list_size(ready_queue) == 0 && running_process == NULL) {
    set_running_process(process);
  } else {
  	enqueue(ready_queue, process);
	}
}

/*
*	@ brief	Initializes all processes by assigning PIDs,
*					starting functions and enqueing them into the ready queue.
* 				One process is assigned as the running process
*					and its starting function is called.
*/
void init_processes(){
  spawn_process(process_1);
	spawn_process(process_2);
	spawn_process(process_3);
}

/*
* @brief  Initialize the dispatcher by creating a ready_queue and spawning processes
*/
void dispatcher_init(){
  ready_queue = queue_new();
  init_processes();
}

/*
*	@brief	Enqueues the running process into the ready queue, pops another process
*					from the queue and assigns it as the running process.
*/
void process_switch(){
	if (get_pcb_state(running_process) != terminated) {
  	enqueue(ready_queue, running_process);
	}
	pcb_t *next = dequeue(ready_queue);
	set_pcb_state(next, running);
	running_process = next;
}

void terminate_process() {
	set_pcb_state(running_process, terminated); //Set state to terminated
}

/*
*	@ brief	Returns the adress for the PCB of the currently running process
*/
pcb_t *get_current_pcb(){
	return running_process;
}

context_t *get_current_context() {
	return get_context(running_process);
}

/*
*	@brief	Returns the PC for the currently running process
*/
addr_t get_running_pc(){
	return get_pc(running_process);
}
