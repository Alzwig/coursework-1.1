#pragma once

/*----- Начальный размер массива -----*/
#define INIT_SEP_SIZE 5
#define INIT_WORD_SIZE 15
#define INIT_SENTECE_SIZE 20
#define INIT_TEXT_SIZE 25

/*----- Конец текста -----*/
#define CONTINUE_TEXT 0
#define END_OF_TEXT 1

/*----- Продолжить(остановиться) -----*/
#define CONTINUE 0
#define STOP 1

/*----- Чтение слова -----*/
#define NOT_READING_WORD 0
#define READING_WORD 1

/*----- Подсчет перевода строки -----*/
#define INITIAL_NEWLINE_COUNT 0
#define END_TEXT_NEWLINE_COUNT 2


/*----- Конец предложения -----*/
#define SENTENCE_NOT_ENDED 0
#define SENTENCE_ENDED 1

/*----- Код ошибки -----*/
enum Error_Code{
    NO_ERROR = 0,
    MALLOC_FAULT,
    REALLOC_FAULT,
    UNGETC_FAULT,
    INVALID_OPTION
};

/*----- Номер опции -----*/
enum Option_Code{
    PRINT_TEXT = 0,
    PRINT_WORDS,
    REVERSE_SYM,
    DELETE_SENTENCES,
    SORT_SENTENCES,
    HELP,
};
