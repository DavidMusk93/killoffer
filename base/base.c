//
// Created by Steve on 6/12/2020.
//

#include "base.h"

#if TEST_POOL
#include "log.h"
#endif

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define CONTAINER struct container_t
#define POOL      struct obj_pool_t

/*******************************************************************************
 * INTERNAL FUNCTION & TYPE
 */

void container_check(CONTAINER *self) {
    if (self->size == self->capacity) {
        self->capacity += self->capacity / 2 + 1;
        self->data = realloc(self->data, self->capacity * sizeof(void *)); /*@NOTICE realloc is danger*/
    }
}

void container_push(CONTAINER *self, void *v) {
    container_check(self);
    self->data[self->size++] = v;
}

void *container_pop(CONTAINER *self) {
    if (!self->size) {
        return 0;
    }
    return self->data[--self->size];
}

void *container_top(CONTAINER *self) {
    if (!self->size) {
        return 0;
    }
    return self->data[self->size - 1];
}

enum block_type_t {
    BLOCK_INTERIOR,
    BLOCK_EXTERIOR,
};

typedef size_t header_type_t;

void *obj_pool_get(POOL *self) {
    void *v;
    if (!(v = self->stack->pop(self->stack))) {
        if (self->size < self->capacity) {
            v = (char *) self->data + self->block * self->size++;
            *(header_type_t *) v = BLOCK_INTERIOR;
        } else {
            v = malloc(self->block);
            *(header_type_t *) v = BLOCK_EXTERIOR;
#if TEST_POOL
            ++self->n;
#endif
        }
    }
#if TEST_POOL
    LOG("@%s block#%zu {%zu,%zu}", __func__, self->block, self->stack->size, self->n);
#endif
    return (char *) v + sizeof(header_type_t);
}

void obj_pool_put(POOL *self, void *v) {
    if (v) {
        v = (char *) v - sizeof(header_type_t);
        header_type_t type = *(header_type_t *) v;
        assert(type == BLOCK_INTERIOR || type == BLOCK_EXTERIOR);
        if (type == BLOCK_INTERIOR) {
            self->stack->push(self->stack, v);
        } else {
            free(v);
#if TEST_POOL
            --self->n;
#endif
        }
#if TEST_POOL
        LOG("@%s block#%zu {%zu,%zu}", __func__, self->block, self->stack->size, self->n);
#endif
    }
}

/*******************************************************************************
 * EXPORT FUNCTION
 */

CONTAINER *container_new(size_t capacity) {
    CONTAINER container = {
            .size=0,
            .capacity=capacity,
            .push=&container_push,
            .pop=&container_pop,
            .top=&container_top,
    };
    container.data = malloc(capacity * sizeof(void *));
    CONTAINER *ptr = malloc(sizeof(CONTAINER));
    *ptr = container;
    return ptr;
}

void container_destroy(CONTAINER *self) {
    if (self) {
        free(self->data);
//        bzero(self, sizeof(CONTAINER));
        memset(self, 0, sizeof(CONTAINER));
        free(self);
        self = 0;
    }
}

POOL *obj_pool_new(size_t capacity, size_t block) {
    POOL pool = {
            .size=0,
            .capacity=capacity,
#if TEST_POOL
            .n=0,
#endif
            .get=&obj_pool_get,
            .put=&obj_pool_put,
    };
    size_t mask = sizeof(header_type_t) - 1;
    if (block & mask) {
        pool.block = (block & (~mask)) + sizeof(header_type_t) * 2;
    } else {
        pool.block = block + sizeof(header_type_t);
    }
    pool.data = malloc(capacity * pool.block);
    pool.stack = container_new(capacity);
    POOL *ptr = malloc(sizeof(POOL));
    *ptr = pool;
    return ptr;
}

void obj_pool_destroy(POOL *self) {
    if (self) {
        container_destroy(self->stack);
        free(self->data);
//        bzero(self, sizeof(POOL));
        memset(self, 0, sizeof(CONTAINER));
        free(self);
        self = 0;
    }
}

#if TEST_POOL

int main() {
    CONTAINER *container = container_new(4);
    POOL *pool = obj_pool_new(3, 6);
    void *v;
    for (size_t i = 0; i < 6; ++i) {
        v = pool->get(pool);
        *(size_t *) v = i * i;
        container->push(container, v);
    }
    while ((v = container->pop(container))) {
        pool->put(pool, v);
    }
    while ((v = pool->stack->pop(pool->stack))) {
        LOG("%zu", *(size_t *) ((char *) v + 4));
    }
    obj_pool_destroy(pool);
    container_destroy(container);
    return 0;
}

#endif

#undef CONTAINER
#undef POOL