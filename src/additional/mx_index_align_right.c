#include "uls.h"

static int max_len_of_index(t_lattrib **lattrib, t_flags *flags);

void mx_index_align_right(t_lattrib **lattrib, t_flags *flags) {
    int temp = 0;
    char *temp_str = NULL;
    int max_len_of_id = 0;

    max_len_of_id = max_len_of_index(lattrib, flags);
    for (int i = 0; i < flags->count_obj; i++) {
        lattrib[i]->id_str = mx_strnew(max_len_of_id);
        temp = max_len_of_id - mx_intlen(lattrib[i]->id);
        if (temp != 0) {
            for (int j = 0; j < temp; j++) {
                if (j == 0)
                    lattrib[i]->id_str = mx_strcpy(lattrib[i]->id_str, " ");
                else
                    lattrib[i]->id_str = mx_strcat(lattrib[i]->id_str, " ");
            }
            temp_str = mx_itoa(lattrib[i]->id);
            lattrib[i]->id_str = mx_strcat(lattrib[i]->id_str, temp_str);
        }
        else {
            temp_str = mx_itoa(lattrib[i]->id);
            lattrib[i]->id_str = mx_strcpy(lattrib[i]->id_str, temp_str);
        }
        if (temp_str)
            mx_strdel(&temp_str);
    }
}

static int max_len_of_index(t_lattrib **lattrib, t_flags *flags) {
    int res = 0;

    for (int i = 0; i < flags->count_obj; i++) {
        if (mx_intlen(lattrib[i]->id) > res)
            res = mx_intlen(lattrib[i]->id);
    }
    return res;
}
