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

void list_delete(Node** head, int data){}

Node* list_search(Node** head, int data){
  int pointer = 0;
  Node* current_node = *head;
  while(current_node){
    if((*current_node).data == data){
      return current_node;
    }
    current_node = (*current_node).next;
  }
}

void list_display(Node** head){}

int list_count_nodes(Node** head){}

void list_cleanup(Node** head){}


void assert_node_value(Node *node, uint16_t expected_value, const char *test_name)
{
    if (node == NULL || node->data != expected_value)
    {
        printf("FAIL [%s]: Expected %hu, got %hu\n", test_name, expected_value, node ? node->data : 0);
    }
    else
    {
        printf("PASS [%s]: Expected %hu\n", test_name, expected_value);
    }
}

int main() {
  printf("Testing list_search...\n");
  Node *head = NULL;
  list_init(&head);
  list_insert(&head, 10);
  list_insert(&head, 20);
  Node *found = list_search(&head, 10);
  assert_node_value(found, 10, "test_search");

  list_cleanup(&head);

  //list_cleanup(&head);  
}