#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "config.h"
#include "option_1.h"
#include "utils.h"
#include "text.h"


WordCount* count_words(Text* text, int* error, size_t* total_words) {
    WordCount* entries = NULL;
    size_t length = 0;
    size_t capacity = 16;
    *total_words = 0;

    if (!text || !total_words) {
        if (error) *error = INVALID_OPTION;
    } else {
        entries = malloc(capacity * sizeof(WordCount));
        if (!entries) {
            print_error(MALLOC_FAULT, error);
        } else {
            for (size_t i = 0; i < text->len && !*error; i++) {
                Sentence* s = &text->sentences[i];
                for (size_t j = 0; j < s->len && !*error; j++) {
                    Word* w = &s->words[j];
                    if (w && w->chars && w->len > 0) {
                        // создаём слово в нижнем регистре
                        char* lower = malloc(w->len + 1);
                        if (!lower) {
                            print_error(MALLOC_FAULT, error);
                        } else {
                            for (size_t k = 0; k < w->len; k++)
                                lower[k] = tolower((unsigned char)w->chars[k]);
                            lower[w->len] = '\0';

                            // поиск слова
                            int found_flag = 0;
                            size_t found_index = 0;
                            size_t k = 0;
                            while (k < length && !found_flag) {
                                if (strcmp(entries[k].word, lower) == 0) {
                                    found_flag = 1;
                                    found_index = k;
                                }
                                k++;
                            }

                            if (found_flag) {
                                entries[found_index].count++;
                                free(lower);
                            } else if (!*error) {
                                // проверка на расширение массива
                                if (length == capacity) {
                                    size_t new_capacity = capacity * 2;
                                    WordCount* tmp = realloc(entries, new_capacity * sizeof(WordCount));
                                    if (!tmp) {
                                        print_error(REALLOC_FAULT, error);
                                        free(lower);
                                    } else {
                                        entries = tmp;
                                        capacity = new_capacity;
                                    }
                                }

                                if (!*error) {
                                    entries[length].word = lower;
                                    entries[length].count = 1;
                                    length++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    *total_words = length;
    return entries;
}



void print_word_entries(WordCount* entries, size_t total_words, int* error) {
    if (!*error && entries) {
        size_t i = 0;
        while (i < total_words) {
            if (entries[i].word) {
                printf("%s : %zu\n", entries[i].word, entries[i].count);
            }
            i++;
        }
    }
}

