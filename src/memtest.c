#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void mem_init(unsigned char *my_memory, unsigned int my_mem_size);
void *my_malloc(unsigned size);
void my_free(void *mem_pointer);
// void mem_get_stats(mem_stats_ptr mem_stats_ptr);

// Prof. Shamash's function for printing status of memory pool:
// void print_stats(char *prefix) {
//   mem_stats_struct mem_stats;

//   mem_get_stats(&mem_stats);
//   printf("mem stats: %s: %d free blocks, %d used blocks, free blocks: smallest=%d largest=%d, used blocks: smallest=%d largest=%d\n",
// 	 prefix,
// 	 mem_stats.num_blocks_free,
// 	 mem_stats.num_blocks_used,
// 	 mem_stats.smallest_block_free,
// 	 mem_stats.largest_block_free,
// 	 mem_stats.smallest_block_used,
// 	 mem_stats.largest_block_used);
// }

/// Function for reporting an error and exiting program:
// void error_and_exit(){
//     printf("Error: Memory exhausted\n");
//     exit(EXIT_FAILURE);
// }

// Function to catch if my_malloc fails and returns NULL:
// void *x_my_malloc(size_t size){
//     void *result = my_malloc(size);
//     if (result == NULL) {
//         error_and_exit();
//     }
//     return result;
// }

// int main(void){
//     int *p = x_my_malloc(sizeof(p));
//     *p = 45;
//     printf("%d", *p);
// }

int main(int argc, char **argv) // argc = argument count, argv = arguement vector
{
  unsigned int global_mem_size = 1024 * 1024;
  unsigned char *global_memory = malloc(global_mem_size); // Returns pointer to begining of memory

  mem_init(global_memory, global_mem_size);
  // print_stats("init");

  unsigned char *ptr_array[10]; // create an array for storing pointers of size 10
  unsigned int sizes[] = {50, 20, 20, 20, 50, 0}; // Create an array of ints 

  for (int i = 0; sizes[i] != 0; i++) { // Loop through int sizes
    // char buf[1024]; // Create a array 1024 size called buf for storing char's 
    ptr_array[i] = my_malloc(sizes[i]); // Get size from each amount from memory pool and st
                                        // store the pointer to the start of it in ptr_array
    // sprintf(buf, "after iteration %d size %d", i, sizes[i]); // Print i and amount of memory requested 
    // print_stats(buf); // Print stats 
    break;
  }

  // my_free(ptr_array[1]);  print_stats("after free #1");

  // my_free(ptr_array[3]);  print_stats("after free #3");

  // my_free(ptr_array[2]);  print_stats("after free #2");

  // my_free(ptr_array[0]);  print_stats("after free #0");

  // my_free(ptr_array[4]);  print_stats("after free #4"); 
}
