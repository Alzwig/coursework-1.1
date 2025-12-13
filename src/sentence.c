#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../includes/sentence.h"
#include "../includes/word.h"
#include "../includes/config.h"
#include "../includes/utils.h"

void free_sentence(Sentence* s) {
    if (!s) return;

    for (size_t i = 0; i < s->len; i++){
        free_word(&s->words[i]);
    }
    free(s->words);
    free(s->sep);
    s->words = NULL;
    s->sep = NULL;
    s->len = 0;
}


Sentence read_sentence(int* end_of_text, int* error) {
    Sentence s;
    size_t words_capacity = INIT_SENTECE_SIZE;
    int sent_ended = SENTENCE_NOT_ENDED; // конец предложения

    s.len = 0;
    s.number = 0;
    s.sep = NULL;
    s.words = malloc(words_capacity * sizeof(Word));

    if (!s.words) {
        print_error(MALLOC_FAULT, error);
    }

    while (!*error && !sent_ended && !*end_of_text) {
        Word w = read_word(end_of_text, error);
        int stop_word_processing = CONTINUE; // обработка слова
        
        if(*error){
            sent_ended = SENTENCE_ENDED;
            stop_word_processing = STOP;
        }
        
        if (!stop_word_processing) {
            if (w.len == 0) {
                free_word(&w);
                if (*end_of_text) sent_ended = SENTENCE_ENDED;
            } else {
                overflow_check((void**)&s.words, &s.len, &words_capacity, sizeof(Word), error);
                if (!*error) {
                    s.words[s.len++] = w;

                    char* dot_position = strchr(w.sep, '.');
                    if (dot_position) {
                        size_t sep_len = strlen(dot_position);
                        s.sep = malloc(sep_len + 1);
                        if (!s.sep) {
                            print_error(MALLOC_FAULT, error);
                            sent_ended = SENTENCE_ENDED;
                        } else {
                            strcpy(s.sep, dot_position);
                            *dot_position = '\0';
                            sent_ended = SENTENCE_ENDED;
                        }
                    }
                } else {
                    free_word(&w);
                }
            }
        }
    }

    if (*error) {
        free_sentence(&s);
    }
    return s;
}

