
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include "memory_manager.h"
#include "common_defs.h"
#include "gitdata.h"

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
    printf("Hej");
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


// ********* Test basic linked list operations *********

void test_list_init()
{
    printf_yellow(" Testing list_init ---> ");
    Node *head = NULL;
    list_init(&head, sizeof(Node));
    my_assert(head == NULL);
    list_cleanup(&head);
    printf_green("[PASS].\n");
}

void test_list_insert()
{
    printf_yellow(" Testing list_insert ---> ");
    Node *head = NULL;
    list_init(&head, sizeof(Node) * 2);
    list_insert(&head, 10);
    list_insert(&head, 20);
    my_assert(head->data == 10);
    my_assert(head->next->data == 20);
    list_cleanup(&head);
    printf_green("[PASS].\n");
}

void test_list_insert_after()
{
    printf_yellow(" Testing list_insert_after ---> ");
    Node *head = NULL;
    list_init(&head, sizeof(Node) * 3);
    list_insert(&head, 10);
    Node *node = head;
    list_insert_after(node, 20);
    my_assert(node->next->data == 20);

    list_cleanup(&head);
    printf_green("[PASS].\n");
}

void test_list_insert_before()
{
    printf_yellow(" Testing list_insert_before ---> ");
    Node *head = NULL;
    list_init(&head, sizeof(Node) * 3);
    list_insert(&head, 10);
    list_insert(&head, 30);
    Node *node = head->next; // Node with data 30
    list_insert_before(&head, node, 20);
    my_assert(head->next->data == 20);

    list_cleanup(&head);
    printf_green("[PASS].\n");
}

void test_list_delete()
{
    printf_yellow(" Testing list_delete ---> ");
    Node *head = NULL;
    list_init(&head, sizeof(Node) * 2);
    list_insert(&head, 10);
    list_insert(&head, 20);
    list_delete(&head, 10);
    my_assert(head->data == 20);
    list_delete(&head, 20);
    my_assert(head == NULL);

    list_cleanup(&head);
    printf_green("[PASS].\n");
}

void test_list_search()
{
    printf_yellow(" Testing list_search ---> ");
    Node *head = NULL;
    list_init(&head, sizeof(Node) * 2);
    list_insert(&head, 10);
    list_insert(&head, 20);
    Node *found = list_search(&head, 10);
    my_assert(found->data == 10);

    Node *not_found = list_search(&head, 30);
    my_assert(not_found == NULL);

    list_cleanup(&head);
    printf_green("[PASS].\n");
}

void test_list_count_nodes()
{
    printf_yellow(" Testing list_count_nodes ---> ");
    Node *head = NULL;
    list_init(&head, sizeof(Node) * 3);
    list_insert(&head, 10);
    list_insert(&head, 20);
    list_insert(&head, 30);

    int count = list_count_nodes(&head);
    my_assert(count == 3);

    list_cleanup(&head);
    printf_green("[PASS].\n");
}

void test_list_cleanup()
{
    printf_yellow(" Testing list_cleanup ---> ");
    Node *head = NULL;
    list_init(&head, sizeof(Node) * 3);
    list_insert(&head, 10);
    list_insert(&head, 20);
    list_insert(&head, 30);

    list_cleanup(&head);
    my_assert(head == NULL);
    printf_green("[PASS].\n");
}

// ********* Stress and edge cases *********

void test_list_insert_loop(int count)
{
    printf_yellow(" Testing list_insert loop ---> ");
    Node *head = NULL;
    list_init(&head, sizeof(Node) * count);
    for (int i = 0; i < count; i++)
    {
        list_insert(&head, i);
    }

    Node *current = head;
    for (int i = 0; i < count; i++)
    {
        my_assert(current->data == i);
        current = current->next;
    }

    list_cleanup(&head);
    printf_green("[PASS].\n");
}

void test_list_insert_after_loop(int count)
{
    printf_yellow(" Testing list_insert_after loop ---> ");
    Node *head = NULL;
    list_init(&head, sizeof(Node) * (count + 1));
    list_insert(&head, 12345);

    Node *node = list_search(&head, 12345);
    for (int i = 0; i < count; i++)
    {
        list_insert_after(node, i);
    }

    Node *current = head;
    my_assert(current->data == 12345);
    current = current->next;

    for (int i = count - 1; i >= 0; i--)
    {
        my_assert(current->data == i);
        current = current->next;
    }

    list_cleanup(&head);
    printf_green("[PASS].\n");
}

void test_list_delete_loop(int count)
{
    printf_yellow(" Testing list_delete loop ---> ");
    Node *head = NULL;
    list_init(&head, sizeof(Node) * count);
    for (int i = 0; i < count; i++)
    {
        list_insert(&head, i);
    }

    for (int i = 0; i < count; i++)
    {
        list_delete(&head, i);
    }

    my_assert(head == NULL);

    list_cleanup(&head);
    printf_green("[PASS].\n");
}

void test_list_search_loop(int count)
{
    printf_yellow(" Testing list_search loop ---> ");
    Node *head = NULL;
    list_init(&head, sizeof(Node) * count);
    for (int i = 0; i < count; i++)
    {
        list_insert(&head, i);
    }

    for (int i = 0; i < count; i++)
    {
        Node *found = list_search(&head, i);
        my_assert(found->data == i);
    }

    list_cleanup(&head);
    printf_green("[PASS].\n");
}

void test_list_edge_cases()
{
    printf_yellow(" Testing list edge cases ---> ");
    Node *head = NULL;
    list_init(&head, sizeof(Node) * 3);

    // Insert at head
    list_insert(&head, 10);
    my_assert(head->data == 10);

    // Insert after
    Node *node = list_search(&head, 10);
    list_insert_after(node, 20);
    my_assert(node->next->data == 20);

    // Insert before
    list_insert_before(&head, node, 15);

    my_assert(head->data == 15);
    my_assert(head->next->data == 10);
    my_assert(head->next->next->data == 20);

    // Delete
    list_delete(&head, 15);
    my_assert(node->next->data == 20);

    // Search
    Node *found = list_search(&head, 20);
    my_assert(found->data == 20);

    list_cleanup(&head);
    printf_green("[PASS].\n");
}

// Main function to run all tests
int main(int argc, char *argv[])
{

  srand(time(NULL));
#ifdef VERSION
  printf("Build Version; %s \n", VERSION);
#endif
  printf("Git Version; %s/%s \n", git_date, git_sha);
    if (argc < 2)
    {
        printf("Usage: %s <test function>\n", argv[0]);
        printf("Available test functions:\n");
        printf("Basic Operations:\n");
        printf(" 1. test_list_init - Initialize the linked list\n");
        printf(" 2. test_list_insert - Test basic list insert operations");
        printf(" 3. test_list_insert_after - Test list insert after a given node\n");
        printf(" 4. test_list_insert_before - Test list insert before a given node\n");
        printf(" 5. test_list_delete - Test delete operation\n");
        printf(" 6. test_list_search - Test search for a particular node\n");
        printf(" 7. test_list_display - Test the display functionality. Requires subjective validation\n");
        printf(" 8. test_list_count_nodes - Test nodes count function\n");
        printf(" 9. test_list_cleanup - Test clean up\n");

        printf("\nStress and Edge Cases:\n");
        printf(" 10. test_list_insert_loop - Test multiple insertions\n");
        printf(" 11. test_list_insert_after_loop - Test multiple insertions after a given node\n");
        printf(" 12. test_list_delete_loop - Test multiple detelions\n");
        printf(" 13. test_list_search_loop - Test multiple search\n");
        printf(" 14. test_list_edge_cases - Test edge cases\n");
        printf(" 0. Run all tests\n");
        return 1;
    }

    switch (atoi(argv[1]))
    {
    case -1:
      printf("No tests will be executed.\n");      
      break;
    case 0:
        printf("Testing Basic Operations:\n");
        test_list_init();
        test_list_insert();
        test_list_insert_after();
        test_list_insert_before();
        test_list_delete();
        test_list_search();
        test_list_count_nodes();
        test_list_cleanup();

        printf("\nTesting Stress and Edge Cases:\n");
        test_list_insert_loop(20);
        test_list_insert_after_loop(10);
        test_list_delete_loop(10);
        test_list_search_loop(10);
        test_list_edge_cases();
        break;
    case 1:
        test_list_init();
        break;
    case 2:

        test_list_insert();
        break;
    case 3:
        test_list_insert_after();
        break;
    case 4:
        test_list_insert_before();
        break;
    case 5:
        test_list_delete();
        break;
    case 6:
        test_list_search();
        break;
    case 7:
        break;
    case 8:
        test_list_count_nodes();
        break;
    case 9:
        test_list_cleanup();
        break;
    case 10:
        test_list_insert_loop(10);
        break;
    case 11:
        test_list_insert_after_loop(10);
        break;
    case 12:
        test_list_delete_loop(10);
        break;
    case 13:
        test_list_search_loop(10);
        break;
    case 14:
        test_list_edge_cases();
        break;

    default:
        printf("Invalid test function\n");
        break;
    }

    return 0;
}