#include "uls.h"

static void one_obj(char *obj);
static int get_dir_len(char *obj);
static void two_and_more_obj(t_flags *flags);

void mx_flag_p(t_flags *flags) {
    if (flags->number_of_obj == 0) {
        one_obj(".");
    }
    else if (flags->number_of_obj == 1) {
        two_and_more_obj(flags);
    }
    else if (flags->number_of_obj > 1) {
        two_and_more_obj(flags);
    }
}

static void one_obj(char *obj) {
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
                full_path = mx_strcat(full_path, "/");
                full_path = mx_strcat(full_path, directory->d_name);
                if ((temp_d = opendir(full_path))) {
                    array[i] = malloc(mx_strlen(directory->d_name) + 1);
                    array[i] = mx_strcpy(array[i], directory->d_name);
                    array[i] = mx_strcat(array[i], "/");
                    closedir(temp_d);
                } else {
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
}

static void two_and_more_obj(t_flags *flags) {
    t_sorted_odj *sort = (t_sorted_odj *)malloc(sizeof(t_sorted_odj));
    sort->len_of_dirs_array = sort->len_of_files_array = 0;
    mx_file_dir_sort(sort, flags);
    if (sort->len_of_files_array != 0) {
        mx_alphabet_sort(sort->files, sort->len_of_files_array);
    }
    if (sort->len_of_dirs_array != 0) {
        mx_alphabet_sort(sort->dirs, sort->len_of_dirs_array);
    }
    if (sort->len_of_files_array != 0) {
        mx_output_by_size_of_wind(sort->files, sort->len_of_files_array);
    }
    for (int j = 0; j < sort->len_of_dirs_array; ++j) {
        if (j != 0 || sort->len_of_files_array != 0)
            mx_printchar('\n');
        mx_printstr(sort->dirs[j]);
        mx_printstr(":\n");
        one_obj(sort->dirs[j]);
    }
    mx_del_strarr(&sort->files);
    mx_del_strarr(&sort->dirs);
    free(sort);
}

static int get_dir_len(char *obj) {
    DIR *d;
    int len_of_array = 0;
    struct dirent *directory;
    d = opendir(obj);
    if (d) {
        while ((directory = readdir(d)) != NULL) {
            if (directory->d_name[0] != '.') {
                len_of_array++;
            }
        }
        closedir(d);
    }
    return len_of_array;
}
