// *********** Header for every file to make sure functions are always imported:

#ifndef HEADER /* This is an "include guard" */
#define HEADER

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

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

// *********** Function declarations
void mem_init(unsigned char *my_memory, unsigned int my_mem_size);
void *my_malloc(unsigned size);
void my_free(void *mem_pointer);
void print_stats(char *prefix);

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

// *********** Function for using Professor Shamash's test code:
int memtest();

#endif