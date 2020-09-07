#include "uls.h"

static int get_dir_len(char *obj);

void mx_print_one_obj(char *obj) {
    int len_of_array;
    int i = 0;
    char **array = NULL;
    DIR *d;
    DIR *temp_d;
    struct dirent *directory;
    d = opendir(obj);
    t_flags *flags = NULL;

    if (d) {
        len_of_array = get_dir_len(obj);
        array = (char **)malloc(sizeof(char *) * len_of_array);
        while ((directory = readdir(d)) != NULL) {
            if (directory->d_name[0] != '.') {
                array[i] = malloc(mx_strlen(directory->d_name));
                array[i] = mx_strcpy(array[i], directory->d_name);
                i++;
            }
        }
        closedir(d);
        mx_alphabet_sort(array, len_of_array);
        mx_output_by_size_of_wind(array, len_of_array);
        if (array[len_of_array - 1])
            mx_strdel(&array[len_of_array - 1]);
        if (array)
            mx_del_strarr(&array);
    }
    else {
        mx_printstr(obj);
        mx_printchar('\n');
    }
}

static int get_dir_len(char *obj) {
    DIR *d;
    int len_of_array = 0;
    struct dirent *directory;
    d = opendir(obj);
    if (d) {
        while ((directory = readdir(d)) != NULL)
            if (directory->d_name[0] != '.')
                len_of_array++;
        closedir(d);
    }
    return len_of_array;
}
