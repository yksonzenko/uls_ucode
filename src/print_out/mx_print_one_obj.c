#include "uls.h"

static int get_dir_len(char *obj);

void mx_print_one_obj(char *obj) {
    int len_of_array;
    int i = 0;
    char **array = NULL;
    char *full_path = NULL;
    DIR *d;
    DIR *temp_d;
    struct dirent *directory;
    d = opendir(obj);

    if (d) {
        len_of_array = get_dir_len(obj);
        array = (char **)malloc(sizeof(char *) * len_of_array);
        while ((directory = readdir(d)) != NULL) {
            if (directory->d_name[0] != '.') {
                full_path = mx_strnew(mx_strlen(obj) + 1 + mx_strlen(directory->d_name));
                full_path = mx_strcpy(full_path, obj);
                full_path = mx_strcat(full_path, directory->d_name);
                if ((temp_d = opendir(full_path))) {
                // if (directory->d_type == DT_DIR) {

                    array[i] = malloc(mx_strlen(directory->d_name) + 1);
                    array[i] = mx_strcpy(array[i], directory->d_name);
                    closedir(temp_d);
                }
                else {

                    array[i] = malloc(mx_strlen(directory->d_name));
                    array[i] = mx_strcpy(array[i], directory->d_name);
                }
                i++;
                mx_strdel(&full_path);
            }
        }
        closedir(d);
        mx_alphabet_sort(array, len_of_array);
        mx_output_by_size_of_wind(array, len_of_array);
        mx_strdel(&array[len_of_array - 1]);
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
