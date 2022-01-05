#include "header.h"

// *************** Professor Shamash's Code for testing:
int memtest()
{
  print_stats("init");

  unsigned char *ptr_array[10];                   // create an array for storing pointers of size 10
  unsigned int sizes[] = {50, 20, 20, 20, 50, 0}; // Create an array of ints

  for (int i = 0; sizes[i] != 0; i++)
  {                                                          // Loop through int sizes
    char buf[1024];                                          // Create a array 1024 size called buf for storing char's
    ptr_array[i] = my_malloc(sizes[i]);                      // Get size from each amount from memory pool and st
                                                             // store the pointer to the start of it in ptr_array
    sprintf(buf, "after iteration %d size %d", i, sizes[i]); // Print i and amount of memory requested
    print_stats(buf);                                        // Print stats
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
  return 0;
}
