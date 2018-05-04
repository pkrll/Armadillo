#include <common/memory.h>
#include <common/stdio.h>
#include <stddef.h>

#define PAGESIZE 512
#define ALIGNMEM 4

extern uint8_t __end __attribute__((section (".data")));

// -------------------------------
// Structs
// -------------------------------

typedef struct Metadata {
	void *next_allocation;
	void *free_allocation_list_head;
} metadata_t;

typedef struct Segment {
	uint32_t size;
} segment_t;

typedef struct FreeSegment {
	uint32_t size;
	void *next;
} free_segment_t;

// -------------------------------
// Declarations
// -------------------------------

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
 * Null the memory segment size bytes with start at ptr.
 *
 * @param  ptr  the start of null segment.
 * @param  size The number of bytes nulled.
 *
 */
static void null_memory(void *ptr, size_t size);
/**
 * Converts a void pointer to a segment_t pointer, and
 * pushes the pointer back with sizeof(segment_t).
 *
 * @param  ptr A pointer.
 * @return     The pointer converted to segment_t.
 */
static segment_t *convert_to_segment(void *ptr);

// -------------------------------
// Public functions
// -------------------------------


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

		size_t total_size = size + sizeof(segment_t);
		size_t pages = number_of_pages(total_size);
		size_t page_size = pages * PAGESIZE;

		allocation = metadata->next_allocation;
		metadata->next_allocation += page_size;
		allocation->size = pages;

	} else {

		freed_segment->next = NULL;
		allocation = (segment_t *)freed_segment;
	}

	// Move pointer forward
	if (allocation) {
		allocation++;
	}

	null_memory(allocation, size);
	return (void *)allocation;
}

void free(void *ptr) {
	if (ptr == NULL) return;

	metadata_t *metadata = (metadata_t *)((uint32_t)&__end);
	free_segment_t *segment = (free_segment_t *)convert_to_segment(ptr);

	segment->next = metadata->free_allocation_list_head;
	metadata->free_allocation_list_head = segment;
}

// -------------------------------
// Internal functions
// -------------------------------

static int number_of_pages(size_t size) {
	return size / PAGESIZE + 1;
}

static void null_memory(void *ptr, size_t size) {
	char *p = ptr;
	size_t incr = 0;
	while (incr < size) {
		*p = 0;
		p += 1;
		incr += sizeof(char);
	}
}

static void *get_freed_segment(size_t size) {
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

static segment_t *convert_to_segment(void *ptr) {
	segment_t *segment = (segment_t *)ptr;
	segment--;

	return segment;
}
