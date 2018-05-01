#include <common/pcb.h>

/**
* Struct containing all registers to be saved for a given process
*/
struct Context{
  reg_t sp;
  reg_t ra;
  reg_t t0;
  reg_t t1;
  reg_t t2;
  reg_t t3;
  reg_t t4;
  reg_t t5;
  reg_t t6;
  reg_t t7;
  reg_t t8;
  reg_t t9;
  reg_t v1;
  reg_t v0;
  reg_t a0;
  reg_t a1;
  reg_t a2;
  reg_t a3;
  reg_t s0;
  reg_t s1;
  reg_t s2;
  reg_t s3;
  reg_t s4;
  reg_t s5;
  reg_t s6;
  reg_t s7;
  reg_t gp;
  reg_t fp;
};

/**
* The entire PCB of a process
*/
struct Pcb{
  pid_t pid;
  addr_t pc;
  state_t process_state;
  context_t *cpu_context;
  addr_t stack;
  addr_t text_seg;
  addr_t data_seg;
  addr_t schedule_info;
};

/*
*	Allocates space for and initializes the starting state of a process
* @param [in] pid A process id
* @param [in] start_function A function pointer to the starting function of the process
* @param [out] Pointer to the resulting PCB
*/
pcb_t *init_pcb(pid_t pid, addr_t start_function){
  pcb_t *pcb = malloc(sizeof(pcb_t));
  pcb->pid = pid;
  pcb->pc = start_function;
  pcb->process_state = 0;
  pcb->cpu_context = init_context();
  pcb->stack = init_stack();
//  pcb->text =     text;
//  pcb->data =     data;
//  pcb->sched =    sched;
  pcb->cpu_context->sp = (reg_t)pcb->stack;
  return pcb;
};

/*
*	Allocates space for the CPU context of a PCB
* @param [out] Pointer to a CPU context
*/
context_t *init_context(){
  context_t *context = malloc(sizeof(context_t));
  return context;
}

/*
*	Allocates space for a process stack
* @param [out] Pointer to a stack space
*/
addr_t init_stack(){
  addr_t stack = malloc(sizeof(stack_t));
  return stack;
}

/*
*	Sets the state of a process
* @param [in] pcb Pointer to a PCB
* @param [in] state New state of the process
*/
void set_pcb_state(pcb_t *pcb, state_t state){
  pcb->process_state = state;
}

/*
*	Returns the PID of a process
* @param [in] pcb A PCB
* @param [out] The PID of the process
*/
pid_t get_pid(pcb_t *pcb){
  return pcb->pid;
}

/*
*	Returns the CPU context of a process
* @param [in] pcb A PCB
* @param [out] Pointer to a CPU context
*/
context_t *get_context(pcb_t *pcb){
  return pcb->cpu_context;
}

/*
*	Returns the PC of a process
* @param [in] pcb A PCB
* @param [out] The current PC of the process
*/
addr_t get_pc(pcb_t *pcb){
  return pcb->pc;
}
