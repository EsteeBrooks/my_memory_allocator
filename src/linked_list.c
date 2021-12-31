// Based on https://www.tutorialspoint.com/cprogramming/c_pointers.htm implementation of Linked List 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

// struct node *full_head = NULL;
// struct node *free_head = NULL;


// *********** Funcion for displaying the list: 
void printList(struct node *ptr) {
   //struct node *ptr = head;
   printf("[ ");
	
   //start from the beginning
   while(ptr != NULL) {
      printf("(%p,%d) ",ptr->pointer,ptr->size);

      ptr = ptr->next;
   }
	
   printf(" ]\n");
}

// *********** Insert link at the first location:
struct node* insertFirst(struct node *head, unsigned char *pointer, int size) {
   //create a link
   struct node *link = (struct node*) malloc(sizeof(struct node));
	
   link->pointer = pointer;
   link->size = size;
	
   //point it to old first node
   link->next = head;
	
   //point first to new first node
   head = link;

   return head;
}

// *********** delete first item
struct node* deleteFirst(struct node *head) {

   //save reference to first link
   // struct node *tempLink = head;
	
   //mark next to first link as first 
   head = head->next;
	
   //return the deleted link
   return head;
}

// // *********** is list empty
bool isEmpty(struct node *head) {
   return head == NULL;
}

// *********** Length of list 
int length(struct node *head) {
   int length = 0;
   //save reference to first link
   struct node *current = head;
	
   for(current = head; current != NULL; current = current->next) {
      length++;
   }
	
   return length;
}

// *********** Find a link with given pointer
struct node* find_by_pointer(struct node *head, unsigned char *pointer) {
   //if list is empty
   if(head == NULL) {
      return NULL;
   }
   struct node *current = head;
   //navigate through list
   while(current->pointer != pointer) {
	
      //if it is last node
      if(current->next == NULL) {
         return NULL;
      } else {
         //go to next link
         current = current->next;
      }
   }      
	
   //if data found, return the current Link
   return current;
}

// *********** Find a link that is bigger or equal to pointer and prev: 
struct cur_and_prev* find_with_prev(struct node *head, unsigned char *pointer) {

   //start from the first link
   struct node *current = head;
   struct node *previous = NULL;
   
   //if list is empty
   if(head == NULL) {
      return NULL;
   }

   //navigate through list
   while(current->pointer < pointer) {

      //if it is last node
      if(current->next == NULL) {
         return NULL;
      } else {
         //store reference to current link
         previous = current;
         //move to next link
         current = current->next;
      }
   }

   //found a match, return current and previous nodes:
   struct cur_and_prev *current_and_previous;
   

   // If the current is head, there is no previous match:
   if(current == head) {
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
struct node* find_by_size(struct node *head, int size) {
   //if list is empty
   if(head == NULL) {
      return NULL;
   }
   struct node *current = head;
   //navigate through list
   while(current->size < size) {
	
      //if it is last node
      if(current->next == NULL) {
         return NULL;
      } else {
         //go to next link
         current = current->next;
      }
   }      
	
   //if data found, return the current Link
   return current;
}

// *********** delete a link with given pointer
struct node* delete(struct node *head, unsigned char *pointer) {

   //start from the first link
   struct node *current = head;
   struct node* previous = NULL;
   
   //if list is empty
   if(head == NULL) {
      return NULL;
   }

   //navigate through list
   while(current->pointer != pointer) {

      //if it is last node
      if(current->next == NULL) {
         return NULL;
      } else {
         //store reference to current link
         previous = current;
         //move to next link
         current = current->next;
      }
   }

   //found a match, update the link
   if(current == head) {
      //change first to point to next link
      head = head->next;
   } else {
      //bypass the current link
      previous->next = current->next;
   }    
	
   return head;
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