#include <common/memory.h>

#define PAGESIZE 8
#define ALIGNMEM 8

extern uint8_t __end __attribute__((section (".data")));

typedef struct Metadata {
	void *last_allocation;
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
 * @param  mem Specified memory...
 * @return     ...
 */

void null_memory(void *ptr, size_t size);
/**
 * Null the memory segment size bytes with start at ptr.
 *
 * @param  ptr  the start of null segment.
 * @param  size The number of bytes nulled.
 * @return      ...
 *
 */

static size_t aligned_mem(size_t mem);

void do_nothing(void *ptr) { // NOTE: Is this needed?
	ptr = ptr + 0;
}

void mem_init() {
	metadata_t *metadata = (metadata_t *)((uint32_t)&__end);
	metadata->last_allocation = (segment_t *)((uint32_t)&__end + sizeof(metadata_t));
	metadata->free_allocation_list_head = NULL;
}

void *malloc(size_t size) {
	if (size == 0) return NULL;

	metadata_t *metadata 	= (metadata_t *)((uint32_t)&__end);
	segment_t *allocation = NULL;
	free_segment_t *freed_segment = get_freed_segment(size);

	if (freed_segment == NULL) {
		// TODO: Perhaps break this out into its own function
		size_t unaligned_memory = number_of_pages(size) * PAGESIZE + sizeof(segment_t);
		size_t aligned_memory = aligned_mem(unaligned_memory);

		allocation = metadata->last_allocation;
		metadata->last_allocation += aligned_memory;
		allocation->size = number_of_pages(aligned_memory);
	} else {
		metadata->free_allocation_list_head = freed_segment->next;
		freed_segment->next = NULL;
		allocation = (segment_t *)freed_segment;
	}

	// Move pointer forward sizeof(segment_t)
	if (allocation) {
		allocation += sizeof(segment_t);
	}
	null_memory(allocation, size);
	return (void *)allocation;
}

void free(void *ptr) {
	if (ptr == NULL) return;

	metadata_t *metadata = (metadata_t *)((uint32_t)&__end);
	free_segment_t *segment = (free_segment_t *)(ptr - sizeof(segment));

	segment->next = metadata->free_allocation_list_head;
	metadata->free_allocation_list_head = segment;
}

size_t aligned_mem(size_t mem) {
	// Already aligned
	if (mem % ALIGNMEM == 0) return mem;
	// Align memory with ALIGNMEM
	return mem + (ALIGNMEM - (mem % ALIGNMEM));
}

int number_of_pages(size_t size) {
	return size / PAGESIZE;
}

void null_memory(void *ptr, size_t size) {
	char *p = ptr;
	while(size > 0) {
		*p = 0;
		size -= 1;
	}
}

void *get_freed_segment(size_t size) {
	metadata_t *metadata = (metadata_t *)((uint32_t)&__end);
	free_segment_t *head = metadata->free_allocation_list_head;

	while (head) {
		// TODO: This just takes the first segment that fits, need to optimize.
		if ((head->size * PAGESIZE) >= size) {
			return head;
		}

		head = head->next;
	}

	return NULL;
}
