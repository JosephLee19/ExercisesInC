/* Example code for Exercises in C.

Based on an example from http://www.learn-c.org/en/Linked_lists

Copyright 2016 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node *next;
} Node;


/* Makes a new node structure.
 * 
 * val: value to store in the node.
 * next: pointer to the next node
 *
 * returns: pointer to a new node
 */
Node *make_node(int val, Node *next) {
    Node *node = malloc(sizeof(Node));
    node->val = val;
    node->next = next;
    return node;
}


/* Prints the values in a list.
 * 
 * list: pointer to pointer to Node
 */
void print_list(Node **list) {
    Node *current = *list;

    printf("[ ");
    while (current != NULL) {
        printf("%d ", current->val);
        current = current->next;
    }
    printf("]\n");
}


/* Removes and returns the first element of a list.
 * 
 * list: pointer to pointer to Node
 *
 * returns: int or -1 if the list is empty
 */
int pop(Node **list) {
    Node* head = *list; //dereference list so that we have a node pointer
    if (head==NULL){    //if the list is empty, return -1
	return -1;
    }
    *list = head->next;  //otherwise, make the list node pointer point to the second element of the list
    return head->val;    //and return first element of original list
}


/* Adds a new element to the beginning of the list.
 * 
 * list: pointer to pointer to Node
 * val: value to add
 */
void push(Node** list, int val) {
    Node* head = *list;  //head is pointer to first node in list
    Node* newElement = make_node(val, head);   //make a node called newElement with val, next points to head
    *list = newElement;	//make list's first element now be newElement
}


/* Removes the first element with the given value
 * 
 * Frees the removed node.
 *
 * list: pointer to pointer to Node
 * val: value to remove
 *
 * returns: number of nodes removed
 */
int remove_by_value(Node **list, int val) {

    Node* current = *list;	//node pointer to store the 'current' position in list
    Node* previous = NULL;	//node pointer to store the previous position in the list


    while (current != NULL) {	//index through list until the end
        if (current->val == val){	//each time checking if current val is the val we are looking for
          if (previous == NULL){	//if so and if first element, remove the first element - we can use pop() for that
            pop(&current);
          } else {
 //if not first element then prepare to index by setting previous to current, freeing current, and setting current to previous->next
            previous->next = current->next;
            free(current);
          }
        }
        previous = current;
        current = current->next;
    }
return 0;    
}


/* Reverses the elements of the list.
 *
 * Does not allocate or free nodes.
 * 
 * list: pointer to pointer to Node
 */
void reverse(Node **list) {
    Node* current = *list;
    Node* previous = NULL;

    while (current != NULL) {		//index through list until the end	
	Node* index=current->next;	//save current->next as temporary Node* so we can change current->next to something new, but still index through original list
        current->next = previous;	//change next to point to previous item in list, or NULL for the first element
        previous = current;		//set previous to be current, in preparation for indexing
        current = index;		//index through original list
    }
    *list = previous;		//after everything has been flipped, the last item in original list is now the beginning of reversed list
}


int main() {
    Node *head = make_node(1, NULL);
    head->next = make_node(2, NULL);
    head->next->next = make_node(3, NULL);
    head->next->next->next = make_node(4, NULL);

    Node **list = &head;
    print_list(list);

    int retval = pop(list);
    print_list(list);

    push(list, retval+10);
    print_list(list);

    remove_by_value(list, 3);
    print_list(list);

    remove_by_value(list, 7);
    print_list(list);

    reverse(list);
    print_list(list);
}
