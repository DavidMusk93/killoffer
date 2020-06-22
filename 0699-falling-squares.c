//
// Created by Steve on 6/14/2020.
//

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define EXTENDED_LIST /* enable insert before one node */

#include "base/linked_list.h"
#include "macro.h"
#include "base/base.h"

#define LIST struct linked_list_t

void linked_list_swap(LIST *self) {
    if (self->next) {
        void *key = self->next->key;
        self->next->key = self->key;
        self->key = key;
    }
}

void linked_list_insert_after(LIST *self, LIST *node) {
    LIST *next = self->next;
    self->next = node;
    node->next = next;
    node->pre_next = &self->next;
    if (next) {
        next->pre_next = &node->next;
    }
}

void linked_list_insert_before(LIST *self, LIST *node) {
    if (!self->pre_next) { /* keep the head pointer unchanged */
        linked_list_insert_after(self, node);
        linked_list_swap(self);
    } else {
        node->pre_next = self->pre_next;
        *self->pre_next = node;
        node->next = self;
        self->pre_next = &node->next;
    }
}

LIST *linked_list_delete_this(LIST *self) {
    LIST *next = self->next;
    *self->pre_next = next;
    if (next) {
        next->pre_next = self->pre_next;
    }
    return self;
}

struct square_t {
    int left;
    int right;
    int height;
};
#define SQUARE struct square_t

struct falling_context_t {
    LIST *head;
    LIST *current;
    int height;
    int least_height;
    struct obj_pool_t *square_pool;
    struct obj_pool_t *node_pool;

    LIST *(*create_node)(struct falling_context_t *self, SQUARE *sp);

    void (*update_height)(struct falling_context_t *self, SQUARE *sp);
};

#define CONTEXT struct falling_context_t

LIST *falling_context_create_node(CONTEXT *self, SQUARE *sp) {
    SQUARE *key = self->square_pool->get(self->square_pool);
    *key = *sp;
    LIST node = {.key=key,};
    LIST *ptr = self->node_pool->get(self->node_pool);
    *ptr = node;
    return ptr;
}

void falling_context_update_height(CONTEXT *self, SQUARE *sp) {
    self->height = MAX(self->height, sp->height);
    self->height = MAX(self->height, self->least_height);
    sp->height = MAX(sp->height, self->least_height);
}

CONTEXT *falling_context_new(size_t capacity) {
    CONTEXT context = {
            .create_node=&falling_context_create_node,
            .update_height=&falling_context_update_height,
    };
    context.square_pool = obj_pool_new(capacity, sizeof(SQUARE));
    context.node_pool = obj_pool_new(capacity, sizeof(LIST));
    CONTEXT *ptr = malloc(sizeof(CONTEXT));
    *ptr = context;
    return ptr;
}

static LIST *node_recycle(CONTEXT *self, LIST *node) {
    LIST *next = node->next;
    self->square_pool->put(self->square_pool, node->key);
    self->node_pool->put(self->node_pool, node);
    return next;
}

void falling_context_destroy(CONTEXT *self) {
    LIST *head = self->head;
    while (head) {
        head = node_recycle(self, head);
    }
    obj_pool_destroy(self->node_pool);
    obj_pool_destroy(self->square_pool);
    memset(self, 0, sizeof(CONTEXT));
    free(self);
    self = 0;
}

void falling_context_update_least_height(CONTEXT *self, int height) {
    if (self->least_height < height) {
        self->least_height = height;
    }
}

enum square_relation_t {
    DISJOINT_LEFT,
    DISJOINT_RIGHT,
    LEFT_OVER,
    LEFT_COVER,
    LEFT_INTERSECT,
    RIGHT_OVER,
    RIGHT_COVER,
    RIGHT_INTERSECT,
    MIDDLE_OVER,
    MIDDLE_COVER,
    PROJECTION,
};

enum falling_status_t {
    ONGOING,
    DONE,
};

int square_relation_find(const SQUARE *lhs, const SQUARE *rhs) {
#define OP(x, y, op) (lhs->x op rhs->y)
#define OP_RL(op) OP(right,left,op)
#define OP_LL(op) OP(left,left,op)
#define OP_RR(op) OP(right,right,op)
#define OP_LR(op) OP(left,right,op)
    if (OP_RL(<=)) {
        return DISJOINT_RIGHT; /* define the relation from the perspective of rhs */
    } else if (OP_LL(<) && OP_RL(>)) {
        return OP_RR(<) ? RIGHT_INTERSECT : (OP_RR(==) ? RIGHT_OVER : MIDDLE_OVER);
    } else if (OP_LL(==)) {
        return OP_RR(<) ? RIGHT_COVER : (OP_RR(==) ? PROJECTION : LEFT_OVER);
    } else {
        return OP_RR(<)
               ? MIDDLE_COVER
               : (OP_RR(==) ? LEFT_COVER : (OP_LR(>=) ? DISJOINT_LEFT : LEFT_INTERSECT));
    }
#undef OP
}

int falling_context_update(CONTEXT *self, SQUARE *sp) {
    if (!self->head) {
        self->head = self->create_node(self, sp);
        self->height = sp->height;
        return DONE;
    }
    SQUARE *csp = ((LIST *) self->current)->key;
    switch (square_relation_find(csp, sp)) {
        case DISJOINT_LEFT: { /* DANGER */
            LIST *node = self->create_node(self, sp);
            sp = node->key;
            linked_list_insert_before(self->current, node);
            self->update_height(self, sp);
            return DONE;
        }
        case DISJOINT_RIGHT: { /* EASY */
            if (!self->current->next) {
                linked_list_insert_after(self->current, self->create_node(self, sp));
                self->update_height(self, sp);
                return DONE;
            }
            self->current = self->current->next;
            return ONGOING;
        }
        case LEFT_INTERSECT: /* DANGER */
        case LEFT_OVER: /* EASY */ {
            SQUARE square = *sp;
            square.height += csp->height;
            self->update_height(self, &square);
            csp->left = sp->right;
            LIST *node = self->create_node(self, &square);
            linked_list_insert_before(self->current, node);
            return DONE;
        }
        case LEFT_COVER: { /* DANGER */
            csp->left = sp->left;
            csp->height += sp->height;
            self->update_height(self, csp);
            return DONE;
        }
        case RIGHT_OVER: { /* EASY */
            csp->right = sp->left;
            sp->height += csp->height;
            self->update_height(self, sp);
            LIST *node = self->create_node(self, sp);
            linked_list_insert_after(self->current, node);
            return DONE;
        }
        case MIDDLE_COVER: /* DANGER */
        case RIGHT_COVER: /* EASY */ {
            csp->height += sp->height;
            if (!self->current->next) {
                csp->left = sp->left;
                csp->right = sp->right;
                self->update_height(self, csp);
                return DONE;
            }
            falling_context_update_least_height(self, csp->height);
            LIST *del = self->current;
            if (!self->current->pre_next) {
                linked_list_swap(self->current);
                del = del->next;
            } else {
                self->current = del->next;
            }
            LIST *node = linked_list_delete_this(del);
            node_recycle(self, node);
            return ONGOING;
        }
        case RIGHT_INTERSECT: { /* EASY */
            csp->right = sp->left;
            int height = csp->height + sp->height;
            if (!self->current->next) {
                sp->height = height;
                self->update_height(self, sp);
                LIST *node = self->create_node(self, sp);
                linked_list_insert_after(self->current, node);
                return DONE;
            }
            falling_context_update_least_height(self, height);
            self->current = self->current->next;
            return ONGOING;
        }
        case MIDDLE_OVER: { /* EASY */
            SQUARE square = *csp;
            csp->right = sp->left;
            square.left = sp->left;
            LIST *node = self->create_node(self, &square);
            linked_list_insert_after(self->current, node);
            self->current = node;
            return ONGOING;
        }
        case PROJECTION: { /* EASY */
            csp->height += sp->height;
            self->update_height(self, csp);
            return DONE;
        }
    }
    return DONE;
}

int *fallingSquares(int **positions, int positionsSize, int *positionsColSize, int *returnSize) {
    CONTEXT *context = falling_context_new(256);
    int *heights = malloc(positionsSize * sizeof(int)), *result = heights;
    FORWARD_FOR(i, 0, positionsSize) {
        SQUARE square = {.left=positions[i][0], .height=positions[i][1],};
        square.right = square.left + square.height;
        context->current = context->head;
        context->least_height = 0;
        while (falling_context_update(context, &square) != DONE);
        *heights++ = context->height;
    }
    falling_context_destroy(context);
    *returnSize = positionsSize;
    return result;
}

MAIN() {
#define ROW 3
#define COL 2
    int data[ROW][COL] = {{9, 6},
                          {2, 2},
                          {2, 6},};
    int *positions[ROW];
    FORWARD_FOR(i, 0, ROW) {
        positions[i] = data[i];
    }
    int col = COL, size;
    int *result = fallingSquares((int **) positions, ROW, &col, &size);
    FORWARD_FOR(i, 0, size) {
        printf("%d\n", result[i]);
    }
    free(result);
    return 0;
}