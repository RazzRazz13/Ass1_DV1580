#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct Memory_Block {
    int free;  //Stores bool to show if its free
    size_t size; //Stores the size of the memory block
    struct Memory_Block* next; //Stores the next memory block
} Memory_Block;

static Memory_Block* first_block;
static void* memorypool;

void mem_init(size_t size){
    memorypool = malloc(size); //Initialize the memeorypool
    first_block = (Memory_Block*)(char*)memorypool + sizeof(Memory_Block); //Create the first empty block
    (*first_block).free = 1;
    (*first_block).size = size;
    (*first_block).next = NULL;
}

void* mem_alloc(size_t size) {

    if (size == 0) {
        return NULL;  //If trying to allocate 0 bytes reutn the memorypool
    }
    
    Memory_Block* current_block = first_block;

    while(current_block){ //Iterates all existing blocks in memorypool
        if ((*current_block).free == 1 && (*current_block).size >= size){
            if ((*current_block).size > size){ //If the current block is free and its size is greater than the allocating size: use it 
                Memory_Block* next_block = (Memory_Block*)((char*)current_block + size + sizeof(Memory_Block)); //Creating new empty block
                (*next_block).free = 1;
                (*next_block).size = (*current_block).size - size;
                (*next_block).next = (*current_block).next;
                (*current_block).free = 0;
                (*current_block).size = size;
                (*current_block).next = next_block; //Setting the found block as allocated han connecting it to the new empty block
            } else {
                (*current_block).free = 0; //This will be run when current block is equal in size to the allocating
            }
            return (char*)current_block; //Returns pointer to the allocated block
        }
        current_block = (*current_block).next;
    }
    //return;
}

void mem_free(void* block) {
    if(block == NULL){
        return;
    }
    Memory_Block* freed_block = (Memory_Block*)((char*)block);
    Memory_Block* current_block = first_block;
    int free_before = 0;
    int free_after = 0;
    
    if (freed_block != current_block){
        while ((*current_block).next != freed_block && (*current_block).next != NULL){
            current_block = (*current_block).next;
        }
        if ((*current_block).free == 1 && (*current_block).next == freed_block){
            free_before = 1;
        }
    }

    Memory_Block* next_block = (*freed_block).next;
    if (next_block != NULL && (*next_block).free == 1){
        free_after = 1;
    }

    if(free_after == 1 && free_before == 1){
        (*current_block).size = (*current_block).size + (*freed_block).size + (*next_block).size;
        (*current_block).next = (*next_block).next;

    } else if (free_after == 1){
        (*freed_block).size = (*freed_block).size + (*next_block).size;
        (*freed_block).next = (*next_block).next;
        (*freed_block).free = 1;
    
    } else if (free_before == 1){
        (*current_block).size = (*current_block).size + (*freed_block).size;
        (*current_block).next = (*freed_block).next;

    } else {
        (*freed_block).free = 1; //Sets the intended block as free
    }
}

void* mem_resize(void* block, size_t size){
    Memory_Block* current_block = (Memory_Block*)block;

    if((*current_block).size < size){
        Memory_Block* next_block = (Memory_Block*)((char*)current_block + size); //Creating new empty block
        (*next_block).free = 1;
        (*next_block).size = (*current_block).size - size;
        (*next_block).next = (*current_block).next;

        (*current_block).free = 0;
        (*current_block).size = size;
        (*current_block).next = next_block; //Splitting one bock into two blocks with one as the intended size

    }else if ((*current_block).size > size){
        Memory_Block* new_block = mem_alloc(size); //Getting a new block with the intended size
        mem_free(current_block); // Freeing the old block
        current_block = new_block; //Returning the new block
    }
    return current_block;
}

void mem_deinit(){
    free(memorypool); //Freeing the memorypool
}

