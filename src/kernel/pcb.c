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

pcb_t *init_pcb(pid_t pid, addr_t start_function){
  pcb_t *pcb = malloc(sizeof(pcb_t));
  pcb->pid =      pid;
  pcb->pc =       start_function;
  pcb->process_state =    0;
  pcb->cpu_context =  init_context();
  pcb->stack =    init_stack();
//  pcb->text =     text;
//  pcb->data =     data;
//  pcb->sched =    sched;
  running_process = pcb; // DUmmy initializer
  return pcb;
};

context_t *init_context(){
  context_t *context = malloc(sizeof(context_t));
  return context;
}

addr_t init_stack(){
  addr_t stack = malloc(sizeof(stack_t));
  return stack;
}

void set_pcb_state(pcb_t *pcb, state_t state){
  pcb->process_state = state;
}
