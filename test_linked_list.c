#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

#include "common_defs.h"

// Helper to assert node values and report
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

// Test inserting elements

void test_list_init()
{
    printf(" Testing list_init ---> ");
    Node *head = NULL;
    list_init(&head, sizeof(Node));
    my_assert(head == NULL);
    list_cleanup(&head);
    printf_green("[PASS].\n");
}

void test_insert()
{
    printf_yellow("Testing list_insert...\n");
    Node *head = NULL;
    list_init(&head);
    list_insert(&head, 10);
    list_insert(&head, 20);
    assert_node_value(head, 10, "test_insert");
    assert_node_value(head->next, 20, "test_insert");

    list_cleanup(&head);
}

// Test inserting elements
// Test inserting after
void test_insert_after()
{
    printf_yellow("Testing list_insert_after...\n");
    Node *head = NULL;
    list_init(&head, sizeof(Node) * 3);
    list_insert(&head, 10);
    Node *node = head;
    list_insert_after(node, 20);
    assert_node_value(node->next, 20, "test_insert_after");

    list_cleanup(&head);
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
    assert(head->next->data == 20);

    list_cleanup(&head);
    printf_green("[PASS].\n");
}


// Test deletion
void test_delete()
{
    printf_yellow(" Testing list_delete ---> ");
    Node *head = NULL;
    list_init(&head, sizeof(Node) * 2);
    list_insert(&head, 10);
    list_insert(&head, 20);
    list_delete(&head, 10);
    assert(head->data == 20);
    list_delete(&head, 20);
    assert(head == NULL);

    list_cleanup(&head);
    printf_green("[PASS].\n");
}

// Test searching
void test_list_search()
{
    printf_yellow(" Testing list_search ---> ");
    Node *head = NULL;
    list_init(&head, sizeof(Node) * 2);
    list_insert(&head, 10);
    list_insert(&head, 20);
    Node *found = list_search(&head, 10);
    assert(found->data == 10);

    Node *not_found = list_search(&head, 30);
    assert(not_found == NULL);

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
    assert(count == 3);

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

// Main function to run all tests
int main()
{
    test_insert();
    test_insert_loop(100);
    test_insert_after();
    test_delete();
    test_search();
    return 0;
}
