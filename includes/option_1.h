#pragma once
#include <stddef.h>
#include "text.h"

typedef struct {
    char* word;
    size_t count;
} WordCount;
 
WordCount* count_words(Text* text, int* error, size_t* total_words);
void print_word_entries(WordCount* entries, size_t total_words, int* error);
