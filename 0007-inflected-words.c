//
// Created by Steve on 6/21/2020.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool is_inflected_words(const char *p1, const char *p2, size_t n) {
#define MAP_SIZE 0x100
#define KEY_TYPE unsigned char
    int map[MAP_SIZE] = {};
//    memset(map, 0, sizeof(map));
    for (size_t i = 0; i < n; ++i) {
        map[(KEY_TYPE) p1[i]]++;
    }
    for (size_t i = 0; i < n; ++i) {
        map[(KEY_TYPE) p2[i]]--;
    }
    for (size_t i = 0; i < MAP_SIZE; ++i) {
        if (map[i] != 0) {
            return false;
        }
    }
    return true;
#undef KEY_TYPE
}

#define KEY_TYPE unsigned char
#define PLUS_ONE 1
#define MINUS_ONE -1

void record_char(int map[(KEY_TYPE) -1], const char *s, size_t n, int delta) {
    for (size_t i = 0; i < n; ++i) {
        map[(KEY_TYPE) s[i]] += delta;
    }
}

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    if (a != b) {
        puts("false");
        return 0;
    }
#if 0
    char *p1, *p2, *data;
    data = malloc(2 * (a + 1));
    p1 = data, p2 = &data[a + 1];
    scanf("%s", p1);
    scanf("%s", p2);
    bool res = is_inflected_words(p1, p2, a);
    free(data);
#else
    char *p = malloc(a + 1);
    int map[(KEY_TYPE) -1] = {};
    bool res = true;
    scanf("%s", p);
    record_char(map, p, a, PLUS_ONE);
    scanf("%s", p);
    record_char(map, p, a, MINUS_ONE);
    for (size_t i = 0; i < MAP_SIZE; ++i) {
        if (map[i] != 0) {
            res = false;
            break;
        }
    }
    free(p);
#endif
    puts(res ? "true" : "false");
    return 0;
}