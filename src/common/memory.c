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

void *get_freed_segment(size_t size);
int number_of_pages(size_t size);
size_t aligned_mem(size_t mem);

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

	metadata_t *metadata = (metadata_t *)((uint32_t)&__end);
	segment_t *segment = NULL;
	free_segment_t *free_allocation_list_head = get_freed_segment(size);

	if (free_allocation_list_head == NULL) {
		segment = metadata->last_allocation;
		size_t unaligned_memory = number_of_pages(size) * PAGESIZE + sizeof(segment_t);
		size_t aligned_memory = aligned_mem(unaligned_memory);
		metadata->last_allocation += aligned_memory;
		segment->size = number_of_pages(aligned_memory);
	} else {
		metadata->free_allocation_list_head = free_allocation_list_head->next;
		free_allocation_list_head->next = NULL;
		segment = (segment_t *)free_allocation_list_head;
	}

	// Move pointer forward sizeof(segment_t)
	if (segment) {
		segment += sizeof(segment_t);
	}

	return (void *)segment;
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
