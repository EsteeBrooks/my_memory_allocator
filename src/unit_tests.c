#include "header.h"

int main(int argc, char **argv) // argc = argument count, argv = arguement vector
{
    unsigned int global_mem_size = 1024 * 1024;
    unsigned char *global_memory = malloc(global_mem_size); // Returns pointer to begining of memory
    mem_init(global_memory, global_mem_size);

    printf("%s", "*********** Check code with Prof. Shamash's Code: ***********\n");
    memtest();
    printf("%s", "****************************************************************\n\n");

    // *********** Unit Tests
    // *** mem_init(*my_memory, my_mem_size) Tests:
    // *** Check if mem_init is called mutliple times, error message is thrown:
    // mem_init(global_memory, global_mem_size);

    // *** my_malloc(size) and free(*mem_pointer) Tests:
    // Check if size == 0, no changes happen:
    printf("%s", "*********** Check if size == 0, no changes happen: ***********\n");
    print_stats("Before");
    unsigned char *p = my_malloc(0);
    print_stats("After");

    // Check if free() is used with a NULL pointer, no changes happen:
    printf("%s", "\n*********** Check if free() is used with a NULL pointer, no changes happen: ***********\n");
    print_stats("Before");
    my_free(p);
    print_stats("After");

    // Check if size == 100, correct changes happen:
    printf("%s", "\n***********Check if size == 100, changes happen correctly: ***********\n");
    print_stats("Before");
    my_malloc(100);
    print_stats("After");

    // Check in while loop that eventually it will fill up and give an error message
    printf("%s", "\n***********Check if that eventually memory cannot be allocated and is done correctly: ***********\n");
    print_stats("Before");
    do
    {
        print_stats("During:");
    } while (my_malloc(100000));
    print_stats("After");
    return 0;
}