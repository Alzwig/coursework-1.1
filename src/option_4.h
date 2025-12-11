#pragma once
#include "text.h"

typedef struct {
    Sentence *s;
    int index;
} SentenceWrap;

int is_sep(char c);
int get_5th_char(const Sentence *s);
int cmp_sentences(const void *a, const void *b);
void sort_text(Text *text);
