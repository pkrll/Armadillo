/**
 * @file
 * @brief Memory manager
 */

#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stddef.h>
#include <common/stdint.h>
#include <common/stdlib.h>

/**
 * Initializes the memory manager.
 * @return 	This function does not return any value.
 */
void mem_init();
/**
 * Allocates the requested memory and returns a pointer to it.
 * @param  	size This is the size of the memory block, in bytes.
 * @return 	This function returns a pointer to the allocated memory, or NULL
 * 					if the request fails.
 */
void *malloc(size_t size);
/**
 * Deallocates the memory previously allocated by a call to malloc.
 *
 * @param ptr This is the pointer to a memory block previously allocated
 * 						with malloc to be deallocated. If a null pointer is passed
 * 						as argument, no action occurs.
 * @return This function does not return any value.
 */

void free(void *ptr);

#endif
