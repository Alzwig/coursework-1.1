#include <stdio.h>
#include <string.h>
#include <strings.h>
#include "utils.h"
#include "config.h"
#include "text.h"
#include "primary_processing.h"

char* sentence_to_string(Sentence* s, int* error) {
    char* res = NULL;
    size_t size = 0;

    if (!*error && s) {
        for (size_t i = 0; i < s->len; i++) {
            if (s->words[i].chars) size += strlen(s->words[i].chars);
            if (s->words[i].sep) size += strlen(s->words[i].sep);
        }

        res = malloc((size+1) * sizeof(char));
        if (!res) print_error(MALLOC_FAULT, error);
        else {
            res[0] = '\0';
            for (size_t i = 0; i < s->len; i++) {
                strcat(res, s->words[i].chars);
                strcat(res, s->words[i].sep);
            }
        }
    }

    return res;
}

void remove_duplicate_sentences(Text* t, int* error) {
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    if (!*error && t) {
        while (i < t->len) {
            char* s1 = NULL;
            if (!*error) {
                s1 = sentence_to_string(&t->sentences[i], error);
            }

            if (!*error && s1) {
                j = i + 1;
                while (j < t->len) {
                    char* s2 = NULL;
                    if (!*error) {
                        s2 = sentence_to_string(&t->sentences[j], error);
                    }
                    if (!*error && s2) {
                        if (strcasecmp(s1,s2) == 0) {
                            free_sentence(&t->sentences[j]);

                            k = j + 1;
                            while (k < t->len) {
                                t->sentences[k - 1] = t->sentences[k];
                                k++;
                            }
                            t->len--;
                            free(s2);
                        } else {
                            free(s2);
                            j++;
                        }
                    } else {
                        free(s2);
                        j++;
                    }
                }
            }
            free(s1);
            i++;
        }
    }
}
