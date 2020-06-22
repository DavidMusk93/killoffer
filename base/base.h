//
// Created by Steve on 6/12/2020.
//

#pragma once

#include <stddef.h>

//#define TEST_POOL 1

struct container_t {
    void **data;
    size_t size;
    size_t capacity;

    void (*push)(struct container_t *self, void *v);

    void *(*pop)(struct container_t *self);

    void *(*top)(struct container_t *self);
};

struct obj_pool_t {
    void *data;
    size_t size;
    size_t capacity;
    size_t block;
    struct container_t *stack;
#if TEST_POOL
    size_t n;
#endif

    void *(*get)(struct obj_pool_t *self);

    void (*put)(struct obj_pool_t *self, void *v);
};

struct container_t *container_new(size_t capacity);

void container_destroy(struct container_t *self);

struct obj_pool_t *obj_pool_new(size_t capacity, size_t block);

void obj_pool_destroy(struct obj_pool_t *self);
