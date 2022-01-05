#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// *********** Function declarations 
void mem_init(unsigned char *my_memory, unsigned int my_mem_size);
void *my_malloc(unsigned size);
void my_free(void *mem_pointer);
void print_stats(char *prefix);

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
  print_stats("init");

  unsigned char *ptr_array[10]; // create an array for storing pointers of size 10
  unsigned int sizes[] = {50, 20, 20, 20, 50, 0}; // Create an array of ints 

  for (int i = 0; sizes[i] != 0; i++) { // Loop through int sizes
    char buf[1024]; // Create a array 1024 size called buf for storing char's 
    ptr_array[i] = my_malloc(sizes[i]); // Get size from each amount from memory pool and st
                                        // store the pointer to the start of it in ptr_array
    sprintf(buf, "after iteration %d size %d", i, sizes[i]); // Print i and amount of memory requested 
    print_stats(buf); // Print stats
  }

  // int  var = 20;   /* actual variable declaration */
  // int  *ip;        /* pointer variable declaration */
  // ip = &var;  /* store address of var in pointer variable*/
  //my_free(ip);

  my_free(ptr_array[1]);
  print_stats("after free #1");

  my_free(ptr_array[3]);  
  print_stats("after free #3");

  my_free(ptr_array[2]);  
  print_stats("after free #2");

  my_free(ptr_array[0]);  
  print_stats("after free #0");

  my_free(ptr_array[4]);  
  print_stats("after free #4"); 
}
