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
                Memory_Block* next_block = (Memory_Block*)(current_block + size);
                (*next_block).free = 1;
                (*next_block).size = (*current_block).size - size;
                (*next_block).next = (*current_block).next;

                (*current_block).free = 0;
                (*current_block).size = size;
                (*current_block).next = next_block;
            } else {
                (*current_block).free = 0;
            }
            return(current_block);
        }
        current_block = (*current_block).next;
    }
}
void mem_free(void* block) {
    Memory_Block* current_block = (Memory_Block*)block;
    (*current_block).free = 1;
    //printf("Contents of structure %d are %lu, %p\n", (*current_block).free, (*current_block).size, (void*)(*current_block).next);

}
void* mem_resize(void* block, size_t size){
    Memory_Block* current_block = (Memory_Block*)block;

    if((*current_block).size < size){
        Memory_Block* next_block = (Memory_Block*)(current_block + size);
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

int main(){
    mem_init(1024); // Initialize memory pool with 1024 bytes

    void* block1 = mem_alloc(100);
    printf("Allocated block1: %p\n", block1);
    
    void* block2 = mem_alloc(200);
    printf("Allocated block2: %p\n", block2);
    
    mem_free(block1);
    printf("Freed block1.\n");
    
    void* block3 = mem_alloc(50);
    printf("Allocated block3: %p\n", block3);
    
    mem_resize(block2, 250);
    printf("Resized block2: %p\n", block2);
    
    mem_deinit();
    printf("Deinitialized memory manager.\n");
}






