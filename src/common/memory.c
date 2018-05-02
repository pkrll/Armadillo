#include <common/memory.h>
#include <common/stdio.h>

#define PAGESIZE 4096
#define ALIGNMEM 8
#define HEADER 8

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
static size_t alloc(size_t size);


void mem_init() {
	metadata_t *metadata = (metadata_t *)((uint32_t)&__end);
	metadata->last_allocation = (segment_t *)((uint32_t)&__end + sizeof(metadata_t));
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
		metadata->free_allocation_list_head = freed_segment->next;
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
	segment_t *segment = (segment_t *)(ptr);
	segment = (segment_t *)((uint32_t)segment - HEADER);
	size_t size = segment->size;
	free_segment_t *free_segment = (free_segment_t *)segment;

	free_segment->size = size;
	free_segment->next = metadata->free_allocation_list_head;
	metadata->free_allocation_list_head = segment;
}

size_t alloc(size_t size) {
	size_t unaligned_memory = number_of_pages(size) * PAGESIZE;
	return aligned_mem(unaligned_memory);
}

size_t aligned_mem(size_t mem) {
	// Too small size left of the page to fit header.
	if (mem % PAGESIZE <= HEADER) {
		mem += HEADER;
	}
	// Already aligned.
	if (mem % ALIGNMEM == 0) return mem;
	// Align memory with ALIGNMEM.
	return mem + (ALIGNMEM - (mem % ALIGNMEM));
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
			if (prev != NULL) {
				prev->next = current->next;
			}
			return current;
		}
		prev = current;
		current = current->next;
	}
	return NULL;
}
