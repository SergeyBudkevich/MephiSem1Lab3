#include "array_func.h"
#include "io_func.h"

//---------------------------------------------------------------------
//ПУНКТ 1
err init_arr(int **arr, int *memory_len, int *len, int len_mass, err errors) {
    if (*arr != NULL) { // очистка памяти, при перетирании массива
        free(*arr);
        *arr = NULL;
    }

    int member;

    if (errors != ERR_OK) { //проверка ввода
        return ERR_EOF;
    }
    if (len_mass < 1) {      
        return ERR_INPUT;
    }

    *arr = calloc(len_mass * 2, sizeof(int)); //выделение памяти под массив
    if (*arr == NULL) { 
        return ERR_MEMORY;
    }

    *memory_len = len_mass * 2; //отслеживаем размер выделенной памяти
*len = len_mass;

    printf("Введите %d элементов целочисленного массива: \n", len_mass);
    for (int i = 0; i < len_mass; i++) { //заполнение массива элементами в цикле
        if (input_number(&member) != ERR_OK) { //проверка ввода 
            free(*arr);
            *arr = NULL;
            *len = 0;
            *memory_len = 0;
            return ERR_EOF;
        }
        (*arr)[i] = member;
    }
     return ERR_OK;
}
//---------------------------------------------------------
//ПУНКТ 2
err member_app(int **arr_ptr, int *memory_len, int *len, int index_new, err errors1, int new_member, err errors2) {
    if (arr_ptr == NULL || *arr_ptr == NULL) {
        printf("Массив еще не иницилизирован.\n");
        return ERR_EMPTY;
    }
    
    if (errors1 != ERR_OK) { //проверка ввода 
        return ERR_EOF;
    }
    if (index_new < 0) {
        return ERR_INDEX;
    }
    if (index_new > *len) {
        index_new = *len;
    }


    if (errors2 != ERR_OK) {
        return errors2;
    }

    if (*len == *memory_len) { //удлиняем память в случае заполнения
        int *check = realloc(*arr_ptr, 2 * *memory_len * sizeof(int));
        if (check == NULL) {
            return ERR_MEMORY;
        }
        *arr_ptr = check;
        *memory_len = *memory_len * 2;
    }

    for (int i = *len; i > index_new; --i) { // сдвиг эллементов массива вправо
        (*arr_ptr)[i] = (*arr_ptr)[i - 1];
    }
       
    (*arr_ptr)[index_new] = new_member;
    *len = *len + 1;


    return ERR_OK;
}
//----------------------------------------------------------------------
//ПУНКТ 3
err member_del(int **arr_ptr, int *memory_len, int *len, int index_del, err erorrs3) {
    if (*len == 0 || arr_ptr == NULL || *arr_ptr == NULL) {
        printf("Массив пуст\n");
        return ERR_EMPTY;
    }
    
    if (erorrs3 != ERR_OK) { //проверка ввода индекса элемента
        return erorrs3;
    }

    if (index_del < 0 || index_del > (*len - 1)) { 
        return ERR_INDEX;
    }

    for (int i = index_del; i < (*len - 1); i++) {
    (*arr_ptr)[i] = (*arr_ptr)[i + 1];
    }
    *len = *len - 1;

    if (*len > 0 || *len < *memory_len / 2) {
        int new_memory_len = *len + 1;
        int* check = realloc(*arr_ptr, new_memory_len * sizeof(int));
        if (check == NULL) {
            return ERR_MEMORY;
        }
        *arr_ptr = check;
        *memory_len = new_memory_len;

    }
    return ERR_OK;
}

//-------------------------------------------------------------
//ПУНКТ 4
err uniq_elem(int **arr_ptr, int *len, int *memory_len) {
    if (*len == 0 || arr_ptr ==  NULL || *arr_ptr == NULL) { //проверка на путой массив
        printf("Массив пуст\n");
        return ERR_EMPTY;
    }
 
    int unique_len = 0;
    int unique_mem_len = 2;
    int *unique_arr = calloc(unique_mem_len, sizeof(int));
    if (unique_arr == NULL) {
        return ERR_MEMORY; 
    }

    for (int i = 0; i < *len;) {
        int counter = 0;
        int i_member = (*arr_ptr)[i];

        for (int j = 0; j < *len; j++) { //считаем кол-во вхождений i-го элемента в массиве
            if (i_member == (*arr_ptr)[j]) {
                counter++;
            }
        }

        if (counter == 1) {
            //добавляем i-й член в конец уникального массива
            err erorrs1 = ERR_OK;
            err erorrs2 = ERR_OK;
            int index_new = unique_len;
            int new_member = i_member;
            err err_ch1 = ERR_OK;
            err_ch1 = member_app(&unique_arr, &unique_mem_len, &unique_len, index_new, erorrs1, new_member, erorrs2);
            if (err_ch1 != ERR_OK) {
                free(unique_arr);
                return err_ch1;
            }
            //удаляем i-й член из предыдущего массива
            err erorrs3 = ERR_OK;
            int index_del = i;
            err err_ch2 = ERR_OK;
            err_ch2 = member_del(arr_ptr, memory_len, len, index_del, erorrs3);
            if (err_ch2 != ERR_OK) {
                free(unique_arr);
                return err_ch2;
            }

        } else {
            i++;
        }
    }
    printf("\nМассив не уникальных элементов: ");
    output_arr(*arr_ptr, len);
    printf("\nМассив уникальных элементов: ");
    output_arr(unique_arr, &unique_len);
        
    free(unique_arr);
    return ERR_OK;
}
