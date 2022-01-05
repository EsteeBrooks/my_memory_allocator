#include "header.h"

// *********** Create link lists for keeping track of used and free memory:
struct node *full_head = NULL;
struct node *free_head = NULL;

// *********** This routine is guaranteed to be called before any of the other routines,
// and can do whatever initialization is needed.  The memory to be managed
// is passed into this routine:
void mem_init(unsigned char *my_memory, unsigned int my_mem_size)
{
  // If the mem_init is called twice, it will initilize the header twice. To avoid this,
  // send error message:
  if (isEmpty(free_head) == false)
  {
    error_and_exit("Error: Init method already called");
  }
  // Set free head to point to new node, which is the entire memory size:
  free_head = insertFirst(full_head, my_memory, my_mem_size);
}

// *********** A function functionally equivalent to malloc() , but allocates it from
// the memory pool passed to mem_init()
void *my_malloc(unsigned size)
{
  // if size is zero, return null:
  if (size == 0)
  {
    printf("%s", "Error: size is 0. Returned a NULL pointer.\n");
    return NULL;
  }

  // Find the first aviable FREE node whose size is bigger or equal to size:
  struct node *result = find_by_size(free_head, size);

  // If there is no FREE nodes, this means the memory has been exhausted.
  // Return a NULL pointer:
  if (result == NULL)
  {
    printf("%s", "Error: Memory exhausted. Returned a NULL pointer.\n");
    return NULL;
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

  // If there is no node with this pointer, print an error and return:
  if (result == NULL)
  {
    printf("%s", "Error: No memory allocated under that pointer.\n");
    return;
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
