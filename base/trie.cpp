//
// Created by Steve on 9/22/2020.
//

#include "trie.h"
#include "../macro.h"

MAIN(){
    Trie trie;
    trie.insert("cat");
    trie.insert("dog");
    trie.insert("cattle");
    trie.insert("bag");
#define SEARCH_TEST(x) LOG("%d",trie.search(x))
#define STARTSWITH_TEST(x) LOG("%d",trie.startsWith(x))
    SEARCH_TEST("cat");
    SEARCH_TEST("bag");
    STARTSWITH_TEST("ca");

    SEARCH_TEST("catt");
    SEARCH_TEST("pig");
    SEARCH_TEST("");
    STARTSWITH_TEST("");
    STARTSWITH_TEST("cab");
}