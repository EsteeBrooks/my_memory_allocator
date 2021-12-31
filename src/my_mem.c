#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

// *********** Node, head and current structures:
struct node
{
  unsigned char *pointer;
  int size;
  struct node *next;
};

// *********** Structure for storing currrent and previous nodes:
struct cur_and_prev
{
  struct node *cur;
  struct node *prev;
};

// *********** Structure for storing the memory's stats:
typedef struct
{
  int num_blocks_used;
  int num_blocks_free;
  int smallest_block_free;
  int smallest_block_used;
  int largest_block_free;
  int largest_block_used;
} mem_stats_struct, *mem_stats_ptr;

// *********** Function declartions for link list operations:
void printList(struct node *ptr);
int print_linked_lists(struct node *free_head, struct node *full_head);
struct node *insertFirst(struct node *head, unsigned char *pointer, int size);
struct node *deleteFirst(struct node *head);
bool isEmpty(struct node *head);
int length(struct node *head);
struct node *find_by_pointer(struct node *head, unsigned char *pointer);
struct cur_and_prev *find_with_prev(struct node *head, unsigned char *pointer);
struct node *find_by_size(struct node *head, int size);
int find_stats(struct node *head, bool biggest);
struct node *delete (struct node *head, unsigned char *pointer);
struct node *create_new_node(struct node *head, unsigned char *new_pointer, int size, bool check_link_list);

// *********** Function declartions for error functions:
void error_and_exit();

// *********** Create link lists for keeping track of used and free memory:
struct node *full_head = NULL;
struct node *free_head = NULL;

// *********** This routine is guaranteed to be called before any of the other routines,
// and can do whatever initialization is needed.  The memory to be managed
// is passed into this routine:
void mem_init(unsigned char *my_memory, unsigned int my_mem_size)
{
  // Set free head to point to new node, which is the entire memory size:
  free_head = insertFirst(full_head, my_memory, my_mem_size);

}

// *********** A function functionally equivalent to malloc() , but allocates it from
// the memory pool passed to mem_init()
void *my_malloc(unsigned size)
{
  // Find the first aviable FREE node whose size is bigger or equal to size:
  struct node *result = find_by_size(free_head, size);

  // If there is no FREE nodes, this means the memory has been exhausted:
  if (result == NULL)
  {
    error_and_exit("Error: Memory exhausted");
  }

  // Save the result’s pointer in new_full_pointer to be used
  // later on by the FULL linked list:
  unsigned char *new_full_pointer = result->pointer;

  // Update the FREE result's size to the new size (result size - size)
  // If size is now 0, delete the result node:
  int updated_size = result->size - size;
  if (updated_size == 0)
  {
    free_head = delete (free_head, result->pointer);
  }
  else
  {
    result->size = updated_size;

    // Update the FREE result‘s pointer to start of new FREE block (result pointer + size).
    unsigned char *updated_pointer = result->pointer + size;
    result->pointer = updated_pointer;
  }

  // Find the first node in FULL linked list with a pointer that is later in memory than
  // new_full_pointer. Create a new node for new_full_pointer.
  // Insert the new node properly into full linked list before the first node (or as head):
  full_head = create_new_node(full_head, new_full_pointer, size, false);

  // On success, returns pointer to begining of memory
  return new_full_pointer;
}

// *********** A function equivalent to free() , but returns the memory to the pool
// passed to mem_init().
void my_free(void *mem_pointer)
{
  // Find the node in FULL that has mem_pointer:
  struct node *result = find_by_pointer(full_head, mem_pointer);

  // If there is no node with this pointer, return an error:
  if (result == NULL)
  {
    error_and_exit("Error: No memory allocated under pointer");
  }

  // Save the result’s pointer in new_free_pointer and its size in new_free_size
  // to be used later on by the FREE linked list:
  unsigned char *new_free_pointer = result->pointer;
  int new_free_size = result->size;

  // Delete the node from FULL linked list:
  full_head = delete (full_head, result->pointer);

  // Find the first node with a pointer that is later in memory than new_free_pointer.
  // Remember the previous node. Create a new node for new_free_pointer.
  // Insert the new node properly into full linked list before the first node (or as head):
  free_head = create_new_node(free_head, new_free_pointer, new_free_size, true);

}

// *********** provides statistics about the current allocation of the memory pool.
void mem_get_stats(mem_stats_ptr mem_stats_ptr)
{
  // Set each num_blocks_free and num_blocks_used based on lenth of each linked list:
  mem_stats_ptr->num_blocks_used = length(full_head);
  mem_stats_ptr->num_blocks_free = length(free_head);

  // For each linked list find smallest used and smallest free:
  mem_stats_ptr->smallest_block_free = find_stats(free_head, false);
  mem_stats_ptr->smallest_block_used = find_stats(full_head, false);

  // For each linked list find largest used and largest free:
  mem_stats_ptr->largest_block_free = find_stats(free_head, true);
  mem_stats_ptr->largest_block_used = find_stats(full_head, true);
}

// *********** Print statistics:
void print_stats(char *prefix)
{
  mem_stats_struct mem_stats;

  mem_get_stats(&mem_stats);
  printf("mem stats: %s: %d free blocks, %d used blocks, free blocks: smallest=%d largest=%d, used blocks: smallest=%d largest=%d\n",
         prefix,
         mem_stats.num_blocks_free,
         mem_stats.num_blocks_used,
         mem_stats.smallest_block_free,
         mem_stats.largest_block_free,
         mem_stats.smallest_block_used,
         mem_stats.largest_block_used);
}
