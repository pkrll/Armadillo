#include <common/memory.h>

#define PAGESIZE 4096

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


void *find_first_free(size_t size);
int number_of_pages(size_t size);

void mem_init() {
	metadata_t *metadata = (metadata_t *)((uint32_t)&__end);
	metadata->last_allocation = (segment_t *)((uint32_t)&__end + sizeof(metadata_t));
	metadata->free_allocation_list_head = NULL;
}

void *malloc(size_t size) {
	if (size == 0) return NULL;

	metadata_t *metadata = (metadata_t *)((uint32_t)&__end);
	segment_t *last = NULL;
	free_segment_t *free_allocation_list_head = find_first_free(size);

	if (free_allocation_list_head == NULL) {
		last = metadata->last_allocation;
		metadata->last_allocation += number_of_pages(size) * PAGESIZE + sizeof(segment_t);
	} else {
		metadata->free_allocation_list_head = free_allocation_list_head->next;
		free_allocation_list_head->next = NULL;
		last = (segment_t *)free_allocation_list_head;
	}

	// Move pointer forward sizeof(segment_t)
	if (last) {
		last->size = number_of_pages(size);
		last += sizeof(segment_t);
	}

	return (void *)last;
}

void free(void *ptr) {
	if (ptr == NULL) return;

	metadata_t *metadata = (metadata_t *)((uint32_t)&__end);
	free_segment_t *segment = (free_segment_t *)ptr;

	segment->next = metadata->free_allocation_list_head;
	metadata->free_allocation_list_head = segment;
}

void *find_first_free(size_t size) {
	metadata_t *metadata = (metadata_t *)((uint32_t)&__end);
	free_segment_t *head = metadata->free_allocation_list_head;

	while (head) {
		// TODO: This just takes the first segment that fits, need to optimize.
		if (head->size > size) {
			return head;
		}

		head = head->next;
	}

	return NULL;
}

int number_of_pages(size_t size) {
	return size / PAGESIZE + 1;
}
