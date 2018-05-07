#include <common/dispatcher.h>
#include <common/stdlib.h>
#include <common/processes.h>

static queue_t *ready_queue __attribute__((section(".data")));
__attribute__((unused))static pcb_t *running_process __attribute__((section(".data")));
static pid_t pid __attribute__((section("data"))) = 0;


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
void forkish(void *process_function) {
  pcb_t *process = init_pcb(pid, process_function);
  pid++;

  if (list_size(ready_queue) == 0 && running_process == NULL) {
    set_running_process(process);
  } else {
  	enqueue(ready_queue, process);
	}
}*/


/*
*	@ brief	Initializes all processes by assigning PIDs,
*					starting functions and enqueing them into the ready queue.
* 				One process is assigned as the running process
*					and its starting function is called.
*/
void init_processes(){
  /*pcb_t *p0 = init_pcb(0, &process_0);
 	pcb_t *p1 = init_pcb(1, &process_1);
  pcb_t *p2 = init_pcb(2, &process_2);
	pcb_t *p3 = init_pcb(3, &process_3);
	pcb_t *p4 = init_pcb(4, &process_4);
	pcb_t *p5 = init_pcb(5, &process_5);

	enqueue(ready_queue, p1);
  enqueue(ready_queue, p2);
  enqueue(ready_queue, p3);
  enqueue(ready_queue, p4);
  enqueue(ready_queue, p5);
  set_running_process(p0);*/
	//process_0();
	spawn_process(process_0);
	spawn_process(process_1);
}

void dispatcher_init(){
  ready_queue = queue_new();
  init_processes();
}

/*
*	@brief	Enqueues the running process into the ready queue, pops another process
*					from the queue and assigns it as the running process.
*/
void process_switch(){
  enqueue(ready_queue, running_process);
  pcb_t *next = dequeue(ready_queue);
  set_pcb_state(next, running);
  running_process = next;
}

/*
*	@ brief	Returns the adress for the PCB Of the currently running process
*/
pcb_t *get_current_pcb(){
	return running_process;
}

/*
*	@brief	Returns the adress for the CPU context for the currently running process.
*/
context_t *get_current_context(){
	return get_context(running_process);
}

/*
*	@brief	Returns the PC for the currently running process
*/
addr_t get_running_pc(){
	return get_pc(running_process);
}
