// Based on https://www.tutorialspoint.com/cprogramming/c_pointers.htm implementation of Linked List
#include "header.h"

// *********** Funcion for displaying the list:
void printList(struct node *ptr)
{
   //struct node *ptr = head;
   printf("[ ");

   //start from the beginning
   while (ptr != NULL)
   {
      printf("(%p,%d) ", ptr->pointer, ptr->size);

      ptr = ptr->next;
   }

   printf(" ]\n");
}

// *********** Insert link at the first location:
struct node *insertFirst(struct node *head, unsigned char *pointer, int size)
{
   //create a link
   struct node *link = (struct node *)malloc(sizeof(struct node));

   link->pointer = pointer;
   link->size = size;

   //point it to old first node
   link->next = head;

   //point first to new first node
   head = link;

   return head;
}

// *********** delete first item
struct node *deleteFirst(struct node *head)
{

   //save reference to first link
   // struct node *tempLink = head;

   //mark next to first link as first
   head = head->next;

   //return the deleted link
   return head;
}

// // *********** is list empty
bool isEmpty(struct node *head)
{
   return head == NULL;
}

// *********** Length of list
int length(struct node *head)
{
   int length = 0;
   //save reference to first link
   struct node *current = head;

   for (current = head; current != NULL; current = current->next)
   {
      length++;
   }

   return length;
}

// *********** Find a link with given pointer
struct node *find_by_pointer(struct node *head, unsigned char *pointer)
{
   //if list is empty
   if (head == NULL)
   {
      return NULL;
   }
   struct node *current = head;
   //navigate through list
   while (current->pointer != pointer)
   {

      //if it is last node
      if (current->next == NULL)
      {
         return NULL;
      }
      else
      {
         //go to next link
         current = current->next;
      }
   }
   //if data found, return the current Link
   return current;
}

// *********** Find a link that is bigger or equal to pointer and prev:
struct cur_and_prev *find_with_prev(struct node *head, unsigned char *pointer)
{

   // Start from the first node:
   struct node *current = head;
   struct node *previous = NULL;

   // Create structure for returning cur and prev nodes:
   struct cur_and_prev *current_and_previous = (struct cur_and_prev *)malloc(sizeof(struct cur_and_prev));

   //if list is empty, return NULL:
   if (head == NULL)
   {
      return NULL;
   }

   // Loop through list:
   while (current->pointer < pointer)
   {

      //if it is last node, set prev to current node and cur to NULL and return:
      if (current->next == NULL)
      {
         current_and_previous->prev = current;
         current_and_previous->cur = NULL;
         return current_and_previous;
      }
      else
      {
         //store reference to current link
         previous = current;
         //move to next link
         current = current->next;
      }
   }

   //found a match, return current and previous nodes:
   // If the current is head, there is no previous match:
   if (current == head)
   {
      current_and_previous->cur = current;
      current_and_previous->prev = NULL;
   }
   else
   {
      current_and_previous->cur = current;
      current_and_previous->prev = previous;
   }

   return current_and_previous;
}

// *********** Find a link that is bigger than or equal to size
struct node *find_by_size(struct node *head, int size)
{
   //if list is empty
   if (head == NULL)
   {
      return NULL;
   }
   struct node *current = head;
   //navigate through list
   while (current->size < size)
   {

      //if it is last node
      if (current->next == NULL)
      {
         return NULL;
      }
      else
      {
         //go to next link
         current = current->next;
      }
   }

   //if data found, return the current Link
   return current;
}

// *********** delete a link with given pointer
struct node *delete (struct node *head, unsigned char *pointer)
{

   //start from the first link
   struct node *current = head;
   struct node *previous = NULL;

   //if list is empty
   if (head == NULL)
   {
      return NULL;
   }

   //navigate through list
   while (current->pointer != pointer)
   {

      //if it is last node
      if (current->next == NULL)
      {
         return NULL;
      }
      else
      {
         //store reference to current link
         previous = current;
         //move to next link
         current = current->next;
      }
   }

   //found a match, update the link
   if (current == head)
   {
      //change first to point to next link
      head = head->next;
   }
   else
   {
      //bypass the current link
      previous->next = current->next;
   }

   return head;
}

// ******* Specialized Functions:

// **** Function called in my_malloc() and my_free() that find the point to insert a new node in
// the full or free linked list and inserts it accordingly:
struct node *create_new_node(struct node *head, unsigned char *new_pointer, int size, bool check_link_list)
{
   // Find the first node in FULL list with a pointer that is later in memory than new_pointer.
   // Remember the previous node:
   struct cur_and_prev *current_and_previous = find_with_prev(head, new_pointer);

   // If the list is empty, insert at head
   if (current_and_previous == NULL)
   {
      head = insertFirst(head, new_pointer, size);
   }

   // If current is the head and there is no prev, insert new node as head:
   else if (current_and_previous->prev == NULL)
   {
      head = insertFirst(head, new_pointer, size);
      // If function is called with free linked list, make sure that
      // the inserted node isn't right next to prev or next in memory.
      // If it, replace the two nodes with a single node:
      if ((check_link_list == true) && (head->next != NULL))
      {
         // Check head and head's next if its not null:
         unsigned char *head_end_pointer = head->pointer + head->size;
         if (head_end_pointer == head->next->pointer)
         {
            // If new_nodes end where new_node's next starts, update new_nodes's size
            // and delete new_node's next:
            head->size += head->next->size;
            head->next = head->next->next;
            head->next->next = NULL;
         }
      }
   }

   // If a previous node is found, update prev's next to point to the new node and
   // update the new node's next to point to cur:
   else if (current_and_previous->prev != NULL)
   {
      // Create a new node, set its pointer to new_pointer, and put in size
      //create a link
      struct node *new_node = (struct node *)malloc(sizeof(struct node));
      new_node->pointer = new_pointer;
      new_node->size = size;

      current_and_previous->prev->next = new_node;

      // If cur is NULL, this is just setting new_node->next to Null as well:
      new_node->next = current_and_previous->cur;

      // If function is called with free linked list, make sure that
      // the inserted node isn't right next to prev or next in memory.
      // If it, replace the two nodes with a single node:
      if (check_link_list == true)
      {
         // Check prev and new_node:
         unsigned char *prev_end_pointer = current_and_previous->prev->pointer +
                                           current_and_previous->prev->size;

         if (prev_end_pointer == new_node->pointer)
         {
            // If prev ends where new_node starts, update prev's size
            // and delete new_node:
            current_and_previous->prev->size += size;
            current_and_previous->prev->next = new_node->next;
            new_node->next = NULL;

            // Since we need to use new_node again to check it against it's next, update new_node:
            new_node = current_and_previous->prev;
         }

         // Check new_node and new_node's next if its not null:
         if (new_node->next != NULL)
         {
            unsigned char *new_node_end_pointer = new_node->pointer + new_node->size;

            if (new_node_end_pointer == new_node->next->pointer)
            {
               // If new_nodes end where new_node's next starts, update new_nodes's size
               // and delete new_node's next by storing it in temp and then deleting it:
               new_node->size += new_node->next->size;
               struct node *temp = new_node->next;
               new_node->next = new_node->next->next;
               temp->next = NULL;
            }
         }
      }
   }
   return head;
}

// *********** Print the linked lists for testing:
int print_linked_lists(struct node *free_head, struct node *full_head)
{
   printf("%s\n", "*******");
   printf("%s \n", "Free:");
   printList(free_head);
   printf("%s \n", "Full:");
   printList(full_head);
   printf("%s\n", "*******");
   return 0;
}

// *********** Find a smallest or biggest link:
int find_stats(struct node *head, bool biggest)
{
   //if list is empty
   if (head == NULL)
   {
      return 0;
   }
   struct node *to_return = head;
   struct node *current = head;

   if (biggest == true)
   {
      // Keep looping through list until reach end:
      while (current != NULL)
      {
         // If current node is larger than to_return, update to_return
         if (current->size > to_return->size)
         {
            to_return = current;
         }

         //go to next link
         current = current->next;
      }
   }
   else
   {
      // Keep looping through list until reach end:
      while (current != NULL)
      {
         // If current node is larger than to_return, update to_return
         if (current->size < to_return->size)
         {
            to_return = current;
         }

         //go to next link
         current = current->next;
      }
   }
   return to_return->size;
}

// int main(void) {
//    printf("Original List: ");
//    printList(full_head);
//    printf("\n");

//    int var = 20;    /* actual variable declaration */
//    int  *ip;        /* pointer variable declaration */
//    ip = &var;

//    full_head = insertFirst(full_head, ip, 10);

//    printf("After 1 insert: ");
//    printList(full_head);
//    printf("\n");

//    int var2 = 10;    /* actual variable declaration */
//    int  *ip2;        /* pointer variable declaration */
//    ip2 = &var2;

//    full_head = insertFirst(full_head, ip2,20);

//    printf("After 2 insert: ");
//    printList(full_head);
//    printf("\n");
//    printf("is empty: %s\n", isEmpty(full_head)? "true" : "false");
//    printf("length: %d\n", length(full_head));

//    struct node *foundLink = find(full_head, ip2);

//    if(foundLink != NULL) {
//       printf("Element found: ");
//       printf("(%p,%d) ",foundLink->pointer,foundLink->size);
//       printf("\n");
//    } else {
//       printf("Element not found.");
//    }
//    full_head = deleteFirst(full_head);

//    printf("After delete: ");
//    printList(full_head);
//    printf("\n");

//    full_head = delete(full_head, ip2);
//    printf("List after deleting an item: ");
//    printList(full_head);
//    printf("\n");

//    printf("is empty: %s\n", isEmpty(full_head)? "true" : "false");
//    printf("length: %d\n", length(full_head));
//    return 0;
// }