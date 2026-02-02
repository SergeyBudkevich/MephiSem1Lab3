#include "io_func.h"


void clean(void) { //очистка буфера ввода 

    scanf("%*[^\n]");
    scanf("%*c");
}

err input_number(int *number) { //проверка ввода числа типа int
    char bk2;
    while (1) {
        int input = scanf("%d%c", number, &bk2);
        if (input == EOF) {
            return ERR_EOF;
        }
        if (input == 2 && bk2 == '\n') {
            return ERR_OK;
        }
        clean();
        printf("Ошибка! Введите корректное число: ");
    }
}

void output_arr(int *arr_ptr, int *len) { //функция вывода массива
    if (*len == 0 || arr_ptr == NULL) {
        printf("[]");
        return;
    }
    printf("[ ");
    for(int i = 0; i < *len; i++) {
        printf("%d ", arr_ptr[i]);
    }
    printf("]");
}


void error_out(err error) {
    switch (error) {
        case ERR_OK:
            break;

        case ERR_INPUT:
            printf("ERROR INPUT\n");
            break;

        case ERR_MEMORY:
            printf("ERROR MEMORY\n");
            break;

        case ERR_EOF:
            printf("ERROR EOF\n");
            break;

        case ERR_INDEX:
            printf("ERROR INDEX\n");
            break;

        case ERR_EMPTY:
            printf("ERROR EMPTY\n");
            break;
        }
    return;
}
