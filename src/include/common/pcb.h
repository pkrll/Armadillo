#ifndef __PCB_H_
#define __PCB_H_

#include <common/memory.h>

typedef int reg_t;
typedef int pid_t;
typedef void *addr_t;
typedef void *stack_t;
/**
* Enum representing the current state of a process
*/
typedef enum State{
  ready = 0,
  running = 1,
} state_t;

typedef struct Pcb pcb_t;
typedef struct Context context_t;

pcb_t *init_pcb(pid_t pid, addr_t start_function);
context_t *init_context();
addr_t init_stack();
void set_pcb_state(pcb_t *pcb, state_t state);
pid_t get_pid(pcb_t *pcb);
context_t *get_context(pcb_t *pcb);
addr_t get_pc(pcb_t *pcb);
#endif
