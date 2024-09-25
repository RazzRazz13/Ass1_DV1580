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
  mem_init(4048);
  *head = NULL;
}

void list_insert(Node** head, int data){

  Node* next_node = (Node*)mem_alloc(sizeof(Node));
  (*next_node).data = data;
  (*next_node).next = *head;
  *head = next_node;

}

void list_insert_after(Node* prev_node, int data){

  Node* next_node = (Node*)mem_alloc(sizeof(Node));

  (*next_node).data = data;
  (*next_node).next = (*prev_node).next;

  (*prev_node).next = next_node;
}

void list_insert_before(Node** head, Node* next_node, int data){

  Node* prev_node = (Node*)mem_alloc(sizeof(Node));

  (*prev_node).data = data;
  (*prev_node).next = next_node;

  Node* current_node = *head;

  while((*current_node).next != next_node){
    current_node = (*current_node).next;
  }
  (*current_node).next = prev_node;

  
}

void list_delete(Node** head, int data){
  Node* current_node = *head;
  Node* previous_node;

  while(current_node){
    if((*current_node).data == data){
      (*previous_node).next = (*current_node).next;
      mem_free((char*)current_node);
      return;
    }
    previous_node = current_node;
    current_node = (*current_node).next;
  }

}

Node* list_search(Node** head, int data){
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
  mem_deinit();
}