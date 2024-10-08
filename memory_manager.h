#ifndef MY_H
#define MY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void mem_init(size_t size);

void* mem_alloc(size_t size);

void mem_free(void* block);

void* mem_resize(void* block, size_t size);

void mem_deinit();

#endif