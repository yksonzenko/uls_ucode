#include "uls.h"

void mx_alphabet_sort2(char **array, int len) {
    char *temp_str = NULL;
    int count_i = 0;
    int count_j = 0;
    for (int i = 0; i < len; ++i) {
        for (int j = i + 1; j < len; ++j) {
            while (!mx_in_alphabet(*array[i]) || !mx_in_alphabet(*array[j])) {
                if (!mx_in_alphabet(*array[i])) {
                    array[i]++;
                    count_i++;
                }
                if (!mx_in_alphabet(*array[j])){
                    array[j]++;
                    count_j++;
                }
            }
            if (mx_strcmp(array[i], array[j]) > 0) {
                temp_str = array[i];
                array[i] = array[j];
                array[j] = temp_str;
                array[i] -= count_j;
                array[j] -= count_i;
            } else {
                array[i] -= count_i;
                array[j] -= count_j;
            }
            count_i = count_j = 0;
        }
    }
}
