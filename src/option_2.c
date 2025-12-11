#include <stdio.h>
#include <string.h>
#include "text.h"

void reverse_word_chars(Word* w) {
    if (w && w->chars && w->len > 1) {
        size_t left = 0;
        size_t right = w->len - 1;
        while (left < right) {
            char tmp = w->chars[left];
            w->chars[left] = w->chars[right];
            w->chars[right] = tmp;
            left++;
            right--;
        }
    }
}

void reverse_sentence_words(Sentence* s) {
    if (s) {
        size_t i = 0;
        while (i < s->len) {
            reverse_word_chars(&s->words[i]);
            i++;
        }
    }
}

void reverse_text_words(Text* t) {
    if (t) {
        size_t i = 0;
        while (i < t->len) {
            reverse_sentence_words(&t->sentences[i]);
            i++;
        }
    }
}
