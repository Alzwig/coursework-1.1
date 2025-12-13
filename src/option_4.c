#include <stdlib.h>
#include <ctype.h>
#include "./includes/option_4.h"
#include "./includes/text.h"

int is_sep(char c) {
    int result = 0;  // единственная точка выхода

    if (c == ' ' || c == '.')
        result = 1;
    else if (ispunct((unsigned char)c) && c != '-')
        result = 1;

    return result;
}

int get_5th_char(const Sentence *s) {
    int count = 0;
    int result = -1; // единственная точка выхода

    for (size_t i = 0; i < s->len && result == -1; i++) {
        Word *w = &s->words[i];

        // символы слова
        for (size_t j = 0; j < w->len && result == -1; j++) {
            char c = w->chars[j];
            count++;

            if (count >= 5 && !is_sep(c)) {
                result = (unsigned char)c;  // нашли нужный символ
            }
        }

        // символы сепаратора
        for (size_t j = 0; w->sep && w->sep[j] != '\0' && result == -1; j++) {
            char c = w->sep[j];
            count++;

            if (count >= 5 && !is_sep(c)) {
                result = (unsigned char)c;  // нашли нужный символ
            }
        }
    }

    return result; // единственная точка выхода
}




int cmp_sentences(const void *a, const void *b) {
    const SentenceWrap *x = a;
    const SentenceWrap *y = b;

    int result = 0;           // единственная точка выхода
    int c1 = get_5th_char(x->s);
    int c2 = get_5th_char(y->s);

    if (c1 != c2)
        result = c2 - c1;    // по убыванию
    else
        result = x->index - y->index; // сохраняем порядок при равенстве

    return result;
}


void sort_text(Text *text) {
    size_t n = text->len;
    SentenceWrap *array = malloc(n * sizeof(SentenceWrap));

    for (size_t i = 0; i < n; i++) {
        array[i].s = &text->sentences[i];
        array[i].index = i;
    }

    qsort(array, n, sizeof(SentenceWrap), cmp_sentences);

    Sentence *tmp = malloc(n * sizeof(Sentence));
    for (size_t i = 0; i < n; i++)
        tmp[i] = *array[i].s;

    for (size_t i = 0; i < n; i++)
        text->sentences[i] = tmp[i];

    free(tmp);
    free(array);
}
