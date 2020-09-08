#include "uls.h"

void mx_check_and_rewrite_obj(t_flags *flags) {
    int new_len = 0;
    DIR *d;
    int fd;
    flags->number_of_obj = flags->count_obj;
    char **temp_array = (char **)malloc(sizeof(char *) * flags->number_of_obj);
    for (int i = 0; i < flags->number_of_obj; i++)
        temp_array[i] = NULL;
    for (int j = 0; j < flags->number_of_obj; j++) {
        if ((d = opendir(flags->all_obj[j]))) {
            temp_array[new_len] = mx_strdup(flags->all_obj[j]);
            new_len++;
            closedir(d);
        }
        else if ((fd = open(flags->all_obj[j], O_RDONLY)) > 0) {
            temp_array[new_len] = mx_strdup(flags->all_obj[j]);
            new_len++;
            close(fd);
        }
        else
            mx_no_file_dir(flags->all_obj[j]);
    }
    if (flags->all_obj) {
        mx_strdel(&flags->all_obj[flags->number_of_obj - 1]);
        mx_del_strarr(&flags->all_obj);
    }
    flags->number_of_obj = new_len;
    flags->all_obj = (char **)malloc(sizeof(char *) * flags->number_of_obj);
    for (int i = 0; i < flags->number_of_obj; i++)
        flags->all_obj[i] = mx_strdup(temp_array[i]);
    if (temp_array) {
        mx_strdel(&temp_array[new_len - 1]);
        mx_del_strarr(&temp_array);
    }
    flags->count_obj = flags->number_of_obj;
}
