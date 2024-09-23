#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "memory_manager.h"

 typedef struct Node {
    uint16_t data; // Stores the data as an unsigned 16-bit integer
    struct Node* next; // A pointer to the next node in the List
  }Node;
  

static Node* firstnode;

void list_init(Node** head){
  mem_init(1024);
  *head = NULL;
}

void list_insert(Node** head, int data){

  Node* next_node = (Node*)mem_alloc(sizeof(Node));

  (*next_node).data = data;
  (*next_node).next = NULL;


  Node* current_node = *head;

  if (current_node == NULL){
    *head = next_node;
    return;
  }

  while((*current_node).next != NULL){
    current_node = (*current_node).next;
  }
  (*current_node).next = next_node;

}

void list_insert_after(Node* prev_node, int data){}

void list_insert_before(Node** head, Node* next_node, int data){}

void list_delete(Node** head, int data){}

Node* list_search(Node** head, int data){}

void list_display(Node** head){}

int list_count_nodes(Node** head){}

void list_cleanup(Node** head){}

int main() {
  printf("Testing list_insert...\n");
  Node *head = NULL;
  list_init(&head);
  list_insert(&head, 10);
  printf("Testing list_insert...\n");


}