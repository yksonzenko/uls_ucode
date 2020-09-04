#include "uls.h"

static void  add_space(t_lattrib **lattrib, t_flags *flags);

void mx_flag_h(t_lattrib **lattrib, t_flags *flags) {
    for (int i = 0; i < flags->number_of_obj; i++)
        lattrib[i]->size_with_type = mx_convert_bytes(lattrib[i]->size);
    add_space(lattrib, flags);
    for (int i = 0; i < flags->number_of_obj; i++) {
        mx_printstr(lattrib[i]->size_with_type);
        mx_printchar('\n');
    }
}

static void  add_space(t_lattrib **lattrib, t_flags *flags) {
    int the_biggest_len = 0;
    int temp;
    char *temp_str = NULL;
    for (int i = 0; i < flags->number_of_obj; i++) {
        temp = mx_strlen(lattrib[i]->size_with_type);
        if (temp > the_biggest_len)
            the_biggest_len = temp;
    }
    for (int i = 0; i < flags->number_of_obj; i++) {
        temp = the_biggest_len - mx_strlen(lattrib[i]->size_with_type);
        if (temp != 0) {
            temp_str = mx_strdup(lattrib[i]->size_with_type);
            mx_strdel(&lattrib[i]->size_with_type);
            lattrib[i]->size_with_type = mx_strnew(the_biggest_len);
            for (int j = 0; j < temp; j++) {
                if (j == 0)
                    lattrib[i]->size_with_type = mx_strcpy(lattrib[i]->size_with_type, " ");
                else
                    lattrib[i]->size_with_type = mx_strcat(lattrib[i]->size_with_type, " ");
            }
            lattrib[i]->size_with_type = mx_strcat(lattrib[i]->size_with_type, temp_str);
            mx_strdel(&temp_str);
        }
    }
}
