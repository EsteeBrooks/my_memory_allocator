#include <stdlib.h>
#include <string.h> 
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

// *********** Node, head and current structures:
struct node {
   unsigned char *pointer;
   int size;
   struct node *next;
};

// *********** Structure for storing currrent and previous nodes:
struct cur_and_prev {
   struct node *cur;
   struct node *prev;
};

// *********** Function declartions: 
void printList(struct node *ptr);
struct node *insertFirst(struct node *head, unsigned char *pointer, int size);
struct node *deleteFirst(struct node *head);
bool isEmpty(struct node *head);
int length(struct node *head);
struct node *find_by_pointer(struct node *head, unsigned char *pointer);
struct cur_and_prev *find_with_prev(struct node *head, unsigned char *pointer);
struct node *find_by_size(struct node *head, int size);
struct node *delete (struct node *head, unsigned char *pointer);

struct node *full_head = NULL;
struct node *free_head = NULL;

// Structure for storing the memory's stats:
typedef struct mem_stats_struct{
  int num_blocks_used;
  int num_blocks_free;
  int smallest_block_free;
  int smallest_block_used;
  int largest_block_free;
  int largest_block_used;
} mem_stats_struct, *mem_stats_ptr;

// this routine is guaranteed to be called before any of the other routines,
// and can do whatever initialization is needed.  The memory to be managed
// is passed into this routine.
void mem_init(unsigned char *my_memory, unsigned int my_mem_size){ 
  // Set free head to point to new node, which is the entire memory size:
  free_head = insertFirst(full_head, my_memory, my_mem_size);
  printf ("%s \n", "Free head");
  printList(free_head);
  printf ("%s \n", "Full head");
  printList(full_head);
}

// Function for reporting an error and exiting program:
void error_and_exit(){
    printf("Error: Memory exhausted\n");
    exit(EXIT_FAILURE);
}
// a function functionally equivalent to malloc() , but allocates it from
// the memory pool passed to mem_init()
void *my_malloc(unsigned size){
  // Find the first aviable FREE node whose size is bigger or equal to size:
  struct node *result = find_by_size(free_head, size);

  // If there is no FREE nodes, this means the memory has been exhausted:
  if(result == NULL) {
      error_and_exit();
  }
  // if(result != NULL) {
  //     printf("Element found: ");
  //     printf("(%p,%d) ",result->pointer,result->size);
  //     printf("\n");  
  // }

  // Save the node’s pointer in new_full_pointer to be used 
  // later on by the full linked list:
  unsigned char *new_full_pointer = result->pointer;
  // printf("new_full_pointer: %p", new_full_pointer);

  // Update the FREE result's size to the new size (result size - size)
  // If size is now 0, delete the result node:
  int updated_size = result->size - size;
  if (updated_size == 0){
    free_head = delete(free_head, result->pointer);
  }
  else{
    result->size = updated_size;

    // Update the FREE result‘s pointer to start of new FREE block (result pointer + size). 
    unsigned char *updated_pointer = result->pointer + size;
    result->pointer = updated_pointer;
  }

  
  // Find the first node in FULL list with a pointer that is later in memory than new_full_pointer. 
  // Remember the previous node:
  struct cur_and_prev *current_and_previous = find_with_prev(full_head, new_full_pointer);
  
  // If a previous node is found, update prev's next to point to the new node and 
  // update the new node's next to point to cur:
  if(current_and_previous->prev != NULL) {
    // Create a new node, set its pointer to new_full_pointer, and put in size
    //create a link
    struct node *new_full_node = (struct node*) malloc(sizeof(struct node));
    new_full_node->pointer = new_full_pointer;
    new_full_node->size = size;

    current_and_previous->prev->next = new_full_node;
    new_full_node->next = current_and_previous->cur;
  }
  else {
    full_head = insertFirst(full_head, new_full_pointer, size);
  }
  
  printf ("%s \n", "Free head");
  printList(free_head);
  printf ("%s \n", "Full head");
  printList(full_head);

  // On success, returns pointer to begining of memory

  // Current size cannot be found in heap. Return Null:
  return NULL;
}
// void stats_init(unsigned int my_mem_size){
//   // Create a varible for keeping track of how big the memory pool is.
//   // Since we need to allocate 8 bytes for this pointer, subtract 8 from the total
//   // pool size:
//   // unsigned long mem_size = my_mem_size - 8; // TODO Make this part of the memory
//   // my_mem_size[0] = 
//   // Create a mem_stats_struct:
//   mem_stats_struct stats;

//   // Update variables for a totally free pool:
//   stats.num_blocks_used = 0;
//   stats.num_blocks_free = 1;
//   stats.smallest_block_free = mem_size;
//   stats.smallest_block_used = 0;
//   stats.largest_block_free = mem_size;
//   stats.largest_block_used = 0;
// }


// a function equivalent to free() , but returns the memory to the pool
// passed to mem_init().
// void my_free(void *mem_pointer){}

// provides statistics about the current allocation of the memory pool.
// void mem_get_stats(mem_stats_ptr mem_stats_ptr){}

// int main(void){}


