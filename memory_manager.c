#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Memory_Block {
    int free;
    size_t size;
    struct Memory_Block* next;
} Memory_Block;

static Memory_Block* firstblock;
static void* memorypool;
static size_t memorysize;


void mem_init(size_t size){

    memorypool = malloc(size);
    memorysize = size;
    firstblock = (Memory_Block*)memorypool;
    (*firstblock).free = 1;
    (*firstblock).size = size;
    (*firstblock).next = NULL;

}

void* mem_alloc(size_t size) {
    Memory_Block* current_block = firstblock;

    while(current_block){
        if ((*current_block).free == 1 && (*current_block).size >= size){
            if ((*current_block).size > size){

            } else {

            }
        }
    }






