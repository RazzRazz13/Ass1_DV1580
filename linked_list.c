#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include "memory_manager.h"
#include "common_defs.h"

typedef struct Node {
  uint16_t data; // Stores the data as an unsigned 16-bit integer
  struct Node* next; // A pointer to the next node in the List
}Node;
  

static Node* firstnode;

void list_init(Node** head, size_t size){
  mem_init(size);
  *head = NULL;
}

void list_insert(Node** head, uint16_t data){

  Node* next_node = (Node*)mem_alloc(sizeof(Node));
  (*next_node).data = data;
  (*next_node).next = NULL;
  
  Node* current_node = *head;

  if (!current_node){
    *head = next_node;
    return;
  }

  while((*current_node).next){
    current_node = (*current_node).next;
  }

  (*current_node).next = next_node;
}

void list_insert_after(Node* prev_node, uint16_t data){

  Node* next_node = (Node*)mem_alloc(sizeof(Node));

  (*next_node).data = data;
  (*next_node).next = (*prev_node).next;

  (*prev_node).next = next_node;
}

void list_insert_before(Node** head, Node* next_node, uint16_t data){

  Node* prev_node = (Node*)mem_alloc(sizeof(Node));

  (*prev_node).data = data;
  (*prev_node).next = next_node;

  Node* current_node = *head;

  if (current_node == next_node){
    *head = prev_node;
    return;
  }

  while((*current_node).next != next_node){
    current_node = (*current_node).next;
  }
  (*current_node).next = prev_node;

  
}

void list_delete(Node** head, uint16_t data){
  Node* current_node = *head;
  Node* previous_node;

  if((*current_node).data == data){
    *head = (*current_node).next;
    mem_free((char*)current_node);
    return;
  }

  while((*current_node).data != data){
    previous_node = current_node;
    current_node = (*current_node).next;
  }

  (*previous_node).next = (*current_node).next;
  mem_free((char*)current_node);
}

Node* list_search(Node** head, uint16_t data){
  Node* current_node = *head;
  while(current_node){
    if((*current_node).data == data){
      return current_node;
    }
    current_node = (*current_node).next;
  }
}

void list_display(Node** head){
  Node* current_node = *head;
  int count = 0;
  int myNumbers[4];
  while(current_node){
    myNumbers[count] = (*current_node).data;
    current_node = (*current_node).next;
    count = ++count;
  }
}

void list_display_range(Node** head, Node* start_node, Node* end_node){
  Node* current_node = *head;
  int count = 0;
  int active;
  int myNumbers[4];
  while(current_node){
    if (current_node == start_node){
      active = 1;
    }
    if (active == 1){
      myNumbers[count] = (*current_node).data;
      count = ++count;
    }
    if (current_node == end_node){
      active = 0;
    }
  current_node = (*current_node).next;
  }
}

int list_count_nodes(Node** head){
  Node* current_node = *head;
  int count = 0;
  while(current_node){
      count = ++count;
      current_node = (*current_node).next;
  }
  return count;
}

void list_cleanup(Node** head){
  Node* current_node = *head;
  while(current_node){
    Node* next_node = (*current_node).next;
    mem_free((char*)current_node);
    current_node = next_node;
  }
  *head = NULL;
  mem_deinit();
}

int main(){
  printf_yellow(" Testing list_cleanup ---> ");
  Node *head = NULL;
  list_init(&head, sizeof(Node) * 3);
  list_insert(&head, 10);
  list_insert(&head, 20);
  list_insert(&head, 30);

  list_cleanup(&head);
  assert(head == NULL);
  printf_green("[PASS].\n");
}