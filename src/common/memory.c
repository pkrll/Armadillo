#include <common/memory.h>
#include <common/stdio.h>
#include <stddef.h>

#define PAGESIZE 256
#define ALIGNMEM 8
#define HEADER 8

extern uint8_t __end __attribute__((section (".data")));

typedef struct Metadata {
	void *next_allocation;
	void *free_allocation_list_head;
} metadata_t;

typedef struct Segment {
	uint16_t size;
} segment_t;

typedef struct FreeSegment {
	uint16_t size;
	void *next;
} free_segment_t;

/**
 * Retrieves a free segment from the list of freed allocations
 * that fits the requested size.
 *
 * @param  size The number of bytes requested.
 * @return      A pointer to a freed segment of the requested
 * 							size, or NULL if none is found.
 */
static void *get_freed_segment(size_t size);
/**
 * Calculates the number of pages based on the size requested.
 *
 * @param  size The number of bytes requested.
 * @return      The number of pages needed for the reqeusted
 * 							size in bytes.
 */
static int number_of_pages(size_t size);
/**
 * Returns the specified memory size aligned.
 *
 * @param  user_alloc Memory size allocated by the user.
 * @param  real_alloc Actual memory allocated, header + pagealign.
 * @return     Returns the specified memory size aligned.
 *
 */
static size_t aligned_mem(size_t user_alloc, size_t real_alloc);
/**
 * Null the memory segment size bytes with start at ptr.
 *
 * @param  ptr  The start of null segment.
 * @param  size The number of bytes nulled.
 *
 */
static void null_memory(void *ptr, size_t size);
/**
 * Returns the real size of memory needed for the request of 'size'.
 *
 * @param  size Memory size allocated by the user.
 * @return     Returns the real size of memory needed for the request of 'size'.
 *
 */
static size_t alloc(size_t size);


void mem_init() {
	metadata_t *metadata = (metadata_t *)((uint32_t)&__end);
	metadata->next_allocation = (segment_t *)((uint32_t)&__end + sizeof(metadata_t));
	metadata->free_allocation_list_head = NULL;
}

void *malloc(size_t size) {
	if (size == 0) return NULL;

	metadata_t *metadata  = (metadata_t *)((uint32_t)&__end);
	segment_t *allocation = NULL;
	free_segment_t *freed_segment = get_freed_segment(size);

	if (freed_segment == NULL) {

		allocation = metadata->last_allocation;
		size_t allocation_size = alloc(size);
		metadata->last_allocation += allocation_size;
		allocation->size = allocation_size / PAGESIZE;
	} else {

		freed_segment->next = NULL;
		allocation = (segment_t *)freed_segment;
	}

	// Move pointer forward HEADER
	if (allocation) {
		allocation = (segment_t *)((uint32_t)allocation + HEADER);
	}
	null_memory(allocation, size);
	return (void *)allocation;
}

void free(void *ptr) {
	if (ptr == NULL) return;

	metadata_t *metadata = (metadata_t *)((uint32_t)&__end);
	free_segment_t *segment = (free_segment_t *)((uint32_t)ptr - HEADER);

	segment->next = metadata->free_allocation_list_head;
	metadata->free_allocation_list_head = segment;
}

size_t alloc(size_t size) {
	size_t memory_to_allocate = number_of_pages(size) * PAGESIZE;
	return aligned_mem(size, memory_to_allocate);
}

size_t aligned_mem(size_t user_alloc, size_t real_alloc) {
	// Too small size left of the page to fit header.
	if ((real_alloc-user_alloc) <= 8) {
		real_alloc += HEADER;
	}
	// Already aligned.
	if (real_alloc % ALIGNMEM == 0) return real_alloc;
	// Align memory with ALIGNMEM.
	return real_alloc + (ALIGNMEM - (real_alloc % ALIGNMEM));
}

int number_of_pages(size_t size) {
	return size / PAGESIZE + 1;
}

void null_memory(void *ptr, size_t size) {
	char *p = ptr;
	size_t incr = 0;
	while (incr < size) {
		*p = 0;
		p += 1;
		incr += sizeof(char);
	}
}

void *get_freed_segment(size_t size) {
	metadata_t *metadata = (metadata_t *)((uint32_t)&__end);
	free_segment_t *current = metadata->free_allocation_list_head;
	free_segment_t *prev = NULL;

	while (current) {
		// TODO: This just takes the first segment that fits, need to optimize.
		if ((current->size * PAGESIZE) >= size) {
			if (prev) {
				prev->next = current->next;
			} else {
				metadata->free_allocation_list_head = current->next;
			}
			return current;
		}
		prev = current;
		current = current->next;
	}
	return NULL;
}

// Test func.
int get_align_size() {
	return ALIGNMEM;
}
