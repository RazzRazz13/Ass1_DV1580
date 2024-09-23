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

void mem_init(size_t size){
    memorypool = malloc(size);
    firstblock = (Memory_Block*)(char*)memorypool;
    (*firstblock).free = 1;
    (*firstblock).size = size;
    (*firstblock).next = NULL;
}

void* mem_alloc(size_t size) {
    if (size == 0) {
        return NULL; 
    }

    Memory_Block* current_block = firstblock;

    while(current_block){
        if ((*current_block).free == 1 && (*current_block).size >= size){
            if ((*current_block).size > size){
                Memory_Block* next_block = (Memory_Block*)((char*)current_block  + size);
                (*next_block).free = 1;
                (*next_block).size = (*current_block).size - size;
                (*next_block).next = (*current_block).next;
                (*current_block).free = 0;
                (*current_block).size = size;
                (*current_block).next = next_block;
            } else {
                //printf_yellow("Testing edge case allocations...\n");
                (*current_block).free = 0;
            }
            return(current_block);
        }
        current_block = (*current_block).next;
    }
}

void mem_free(void* block) {
    Memory_Block* current_block = (Memory_Block*)((char*)block);
    (*current_block).free = 1;
}

void* mem_resize(void* block, size_t size){
    Memory_Block* current_block = (Memory_Block*)block;

    if((*current_block).size < size){
        Memory_Block* next_block = (Memory_Block*)((char*)current_block + size);
        (*next_block).free = 1;
        (*next_block).size = (*current_block).size - size;
        (*next_block).next = (*current_block).next;

        (*current_block).free = 0;
        (*current_block).size = size;
        (*current_block).next = next_block;

    }else if ((*current_block).size > size){
        Memory_Block* new_block = mem_alloc(size);
        mem_free(current_block);
        current_block = new_block;
    }
    return current_block;
}

void mem_deinit(){
    free(memorypool);
}






