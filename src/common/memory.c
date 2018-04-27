#include <common/memory.h>

#define PAGESIZE 4096

extern uint8_t __end __attribute__((section (".data")));

typedef struct Metadata {
	void *last_allocation;
	void *first_free_allocation;
} metadata_t;

typedef struct Header {
	uint16_t size;
} header_t;

typedef struct FreeHeader {
	uint16_t size;
	void *next;
} free_header_t;


void *find_first_free(size_t size);
int number_of_pages(size_t size);

void mem_init() {
	metadata_t *metadata = (metadata_t *)((uint32_t)&__end);
	metadata->last_allocation = (header_t *)((uint32_t)&__end + sizeof(metadata_t));
	metadata->first_free_allocation = NULL;
}

void *malloc(size_t size) {
	if (size == 0) return NULL;

	metadata_t *metadata = (metadata_t *)((uint32_t)&__end);
	header_t *last = NULL;
	free_header_t *first_free_allocation = find_first_free(size);

	if (first_free_allocation == NULL) {
		last = metadata->last_allocation;
		metadata->last_allocation += number_of_pages(size) * PAGESIZE;

	} else {
		metadata->first_free_allocation = first_free_allocation->next;
		first_free_allocation->next = NULL;
		last = (header_t *)first_free_allocation;
	}

	// Move pointer forward sizeof(header_t)
	if (last) {
		last->size = number_of_pages(size);
		last += sizeof(header_t);
	}

	return (void *)last;
}

void free(void *ptr) {
        metadata_t *metadata = (metadata_t *)((uint32_t)&__end);
	if (ptr != NULL) {
          metadata->first_free_allocation = ptr;
	} else {
          ((free_header_t *)ptr)->next = (metadata->first_free_allocation);
          metadata->first_free_allocation = ptr;
        }
}

void *find_first_free(size_t size) {
	metadata_t *metadata = (metadata_t *)((uint32_t)&__end);
	free_header_t *head = metadata->first_free_allocation;

	while (head) {
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
