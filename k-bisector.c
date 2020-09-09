//
// Created by Steve on 6/10/2020.
//

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "macro.h"

struct point_t {
    float x;
    float y;
};

void point_print(struct point_t *self) {
    printf("@%s {%.3f, %.3f}\n", __func__, self->x, self->y);
}

enum line_type_t {
    TOP,
    BOTTOM,
    LEFT,
    RIGHT,
};

struct line_t {
    struct point_t *start;
    int type;
    float length;
    float left;
};

bool line_reach_bisector(struct line_t *self, float *left) {
    if (self->left < *left) {
        *left -= self->left;
        self->left = 0;
        return false;
    }
    self->left -= *left;
    return true;
}

float line_from_points(struct line_t *lines, struct point_t *points, size_t n, size_t k) {
    struct point_t *p0 = points, *p1, *p2;
    float sum = 0;
    for (size_t i = 0; i < n; ++i) {
        p1 = points;
        p2 = ++points;
        if (i == n - 1) {
            p2 = p0;
        }
        lines->start = p1;
        if (p1->x == p2->x) {
            if (p1->y < p2->y) {
                lines->type = TOP;
                lines->left = lines->length = p2->y - p1->y;
            } else {
                lines->type = BOTTOM;
                lines->left = lines->length = p1->y - p2->y;
            }
        } else {
            if (p1->x < p2->x) {
                lines->type = RIGHT;
                lines->left = lines->length = p2->x - p1->x;
            } else {
                lines->type = LEFT;
                lines->left = lines->length = p1->x - p2->x;
            }
        }
        sum += lines->length;
        ++lines;
    }
    return sum / k;
}

void line_generate_point(struct line_t *self, struct point_t *point) {
    float delta = self->length - self->left;
    switch (self->type) {
        case TOP: {
            point->x = self->start->x;
            point->y = self->start->y + delta;
            break;
        }
        case BOTTOM: {
            point->x = self->start->x;
            point->y = self->start->y - delta;
            break;
        }
        case LEFT: {
            point->x = self->start->x - delta;
            point->y = self->start->y;
            break;
        }
        case RIGHT: {
            point->x = self->start->x + delta;
            point->y = self->start->y;
            break;
        }
    }
}

void find_k_bisector(struct point_t *points, size_t n, size_t k, struct point_t *bisectors) {
    struct line_t *lines = malloc(n * sizeof(struct line_t)), *p = lines;
    const float length = line_from_points(lines, points, n, k);
    float left;
    *bisectors++ = *lines->start;
    while (--k) {
        left = length;
        while (true) {
            if (line_reach_bisector(lines, &left)) {
                line_generate_point(lines, bisectors++);
                break;
            }
            ++lines;
        }
    }
    free(p);
}

MAIN_EX(argc, argv) {
    struct point_t points[] = {{1, 1},
                               {1, 2},
                               {2, 2},
                               {2, 3},
                               {5, 3},
                               {5, 1}};
    size_t k = 3;
    if (argc > 1) {
        k = strtol(argv[1], 0, 10);
    }
    k = k < 2 ? 2 : k;
    struct point_t *bisectors = malloc(k * sizeof(struct point_t));
    find_k_bisector(points, dimension_of(points), k, bisectors);
    for (size_t i = 0; i < k; ++i) {
        point_print(&bisectors[i]);
    }
    free(bisectors);
    return 0;
}