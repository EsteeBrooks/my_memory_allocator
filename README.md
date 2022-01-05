Final project for Computer Systems taught by Professor Ari Shamash

Assignment: Create a your own implementation of malloc() and free(). Implement function for printing statistics as well.

My approach: Create two linked list that track the locations of free memory and allocated memory in the memory pool respectively. 

To run the project: type "make release" in terminal. Alternatively, run the following commands:
1. make clean
2. make 
3. bin/main

Folder system breakdown:
- The source code is stored in src
    - header.h stores all the libraries that must be imported and all function names
    - linked_list.c has basic functions for implementing the linked list and specific functions needed for my_malloc() and my_free()
    - my_mem.c is where my_malloc(), my_free(), mem_get_stats(), print_stats(), and mem_init() are defined
    - shamash_test.c is used for testing each function created with code written by Professor Shamash
    - unit_tests.c has some tests for making sure the functions 
    - error_functions.c stores error functions for when functions are called improperly
- The output of running gcc for each source file is stored in obj
- The final output file is store in bin and called "main"

Resources I found most useful:
- https://www.tutorialspoint.com/cprogramming/index.htm
- Jacob Sorber on YouTube (https://www.youtube.com/watch?v=LfIPVIsH4ZU, https://www.youtube.com/watch?v=CRlqU9XzVr4, https://www.youtube.com/watch?v=dpjt_D8xcPU)



