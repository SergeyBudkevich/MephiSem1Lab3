#include "io_func.h"
#include "array_func.h"

int main(void) { 
    int flag = 1;
    int option;
    int len = 0;
    int *arr_ptr = NULL;
    int memory_len = 0;

    while (flag) {
        
        
        printf("\nТекущее состояние массива: ");
        output_arr(arr_ptr, &len); //вывод массива
    
        printf("\nМеню:\n");
        printf("1. Инициализация массива\n");
        printf("2. Вставка нового элемента\n");
        printf("3. Удаление элемента\n");
        printf("4. Создать последовательность всех уникальных элементов, из тех, которые содержатся в текущей\n");
        printf("5. Вывод содержимого массива\n");
        printf("0. Выход из программы\n");
        printf("Выберите пункт: ");   
        
        if (input_number(&option) != ERR_OK) {
            printf("\nОбнаружен EOF.\n");
            printf("Завершение программы, пока-пока\n");
            free(arr_ptr);
            arr_ptr = NULL;
            break;
        }
        
        switch (option) {
            case 1:
                  printf("Введите длину нового массива:\n");
                int len_mass = 0;
                err errors = input_number(&len_mass);
                err err_check1 = init_arr(&arr_ptr, &memory_len, &len, len_mass, errors);
                if (err_check1 != ERR_OK) {
                    printf("Ошибка инициализации массива. ");
                    error_out(err_check1);
                }           
                break;

            case 2:
                printf("Укажите индекс нового элемента:\n");
                int index_new = 0;
                err errors1 = input_number(&index_new);
                printf("Введите новый элемент: ");
                int new_member = 0;
                err errors2 = input_number(&new_member);
                
                err err_check2 = member_app(&arr_ptr, &memory_len, &len, index_new, errors1, new_member, errors2);
                if (err_check2 != ERR_OK) {
                    printf("Ошибка добавления элемента. ");
                    error_out(err_check2);
                }
                break;

            case 3:
                printf("Укажите индекс удаляемого элемента:\n");
                int index_del = 0;
                err errors3 = input_number(&index_del);
                err err_check3 = member_del(&arr_ptr, &memory_len, &len, index_del, errors3);
                if (err_check3 != ERR_OK) {
                    printf("Ошибка удаления элемента. ");
                    error_out(err_check3);
                }
                break;

            case 4:
                printf("Выолнение операции...\n");
                err err_check4 = uniq_elem(&arr_ptr, &len, &memory_len);
                if (err_check4 != ERR_OK) {
                    printf("Ошибка выполнения. ");
                    error_out(err_check4);
                }
                break;

            case 5:
                //пустой case
                break;

            case 0:
                printf("Завершение программы\n");
                flag = 0;
                free(arr_ptr);
                break;

            default:
                printf("Некорректный ввод. Укажите пункт меню из предложенных.\n");
                break;
        } 
    }
    return 0; 
}
