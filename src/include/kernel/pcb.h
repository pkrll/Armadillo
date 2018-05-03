#ifndef __PCB_H_
#define __PCB_H_

#include <common/memory.h>

typedef int reg_t;
typedef int pid_t;
typedef void *addr_t;

/**
 * Enum representing the current state of a process
 */
typedef enum State{
  ready = 0,
  running = 1,
} state_t;

typedef struct Pcb pcb_t;
typedef struct Context context_t;
typedef struct Stack stack_t;

/**
 * Allocates space for and initializes the starting state of a process.
 *
 * @param  pid 						A process id
 * @param  start_function A function pointer to the starting function of the process
 *
 * @return Pointer to the resulting PCB
 */
pcb_t *init_pcb(pid_t pid, addr_t start_function);
/**
 * Allocates space for the CPU context of a PCB.
 *
 * @return Pointer to a CPU context.
 */
context_t *init_context();
/**
 * Allocates space for a process stack.
 *
 * @return Pointer to a stack space.
 */
stack_t init_stack();
/**
 * Sets the state of a process.
 *
 * @param pcb   Pointer to a PCB.
 * @param state New state of the process.
 */
void set_pcb_state(pcb_t *pcb, state_t state);
/**
 * Returns the PID of a process.
 *
 * @param  pcb A PCB.
 * @return The PID of the process.
 */
pid_t get_pid(pcb_t *pcb);
/**
 * Returns the CPU context of a process.
 * @param  pcb A PCB.
 * @return Pointer to a CPU context.
 */
context_t *get_context(pcb_t *pcb);
/**
 * Returns the PC of a process.
 * @param  pcb A PCB.
 * @return The current PC of the process
 */
addr_t get_pc(pcb_t *pcb);

#endif
