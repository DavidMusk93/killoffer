//
// Created by Steve on 6/21/2020.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool is_inflected_words(const char *p1, const char *p2, size_t n) {
#define KEY_TYPE unsigned char
    int map[(KEY_TYPE) -1] = {};
//    memset(map, 0, sizeof(map));
    for (size_t i = 0; i < n; ++i) {
        map[(KEY_TYPE) p1[i]]++;
    }
    for (size_t i = 0; i < n; ++i) {
        map[(KEY_TYPE) p2[i]]--;
    }
    for (size_t i = 0; i < (KEY_TYPE) -1; ++i) {
        if (map[i] != 0) {
            return false;
        }
    }
    return true;
#undef KEY_TYPE
}

int main() {
    int a, b;
    char *p1, *p2, *data;
    scanf("%d %d", &a, &b);
    if (a != b) {
        puts("false");
        return 0;
    }
    data = malloc(2 * (a + 1));
    p1 = data, p2 = &data[a + 1];
    scanf("%s", p1);
    scanf("%s", p2);
    bool res = is_inflected_words(p1, p2, a);
    puts(res ? "true" : "false");
    free(data);
    return 0;
}