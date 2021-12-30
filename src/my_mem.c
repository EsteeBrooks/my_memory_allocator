#include <stdlib.h>
#include <string.h> 
#include <unistd.h>
#include <stdio.h>
// Structure for storing the memory's stats:
typedef struct mem_stats_struct{
  int num_blocks_used;
  int num_blocks_free;
  int smallest_block_free;
  int smallest_block_used;
  int largest_block_free;
  int largest_block_used;
} mem_stats_struct, *mem_stats_ptr;


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
// this routine is guaranteed to be called before any of the other routines,
// and can do whatever initialization is needed.  The memory to be managed
// is passed into this routine.
void mem_init(unsigned char *my_memory, unsigned int my_mem_size){
  printf("hello");
}

// a function functionally equivalent to malloc() , but allocates it from
// the memory pool passed to mem_init()
// void *my_malloc(unsigned size){
//   // On success, returns pointer to begining of memory

//   // Current size cannot be found in heap. Return Null:
//   return NULL;
// }

// a function equivalent to free() , but returns the memory to the pool
// passed to mem_init().
// void my_free(void *mem_pointer){}

// provides statistics about the current allocation of the memory pool.
// void mem_get_stats(mem_stats_ptr mem_stats_ptr){}

// int main(void){}


