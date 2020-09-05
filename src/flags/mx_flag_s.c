#include "uls.h"

static t_result *one_obj(char *obj);
static char *trim(char *string, char **current_file);
static void add_inode_to_name_of_file(t_sorted_odj *sort);
static void two_and_more_obj(t_flags *flags);

t_result *mx_flag_s(t_flags *flags, char *object) {
    t_result *struct_result = NULL;
    flags->number_of_obj = flags->count_obj;
    if (flags->number_of_obj == 0 && !object) {
        struct_result = one_obj(".");
    }
    else if (flags->number_of_obj == 1 && !object) {
        two_and_more_obj(flags);
    }
    else if (flags->number_of_obj == 1 || object) {
        struct_result = one_obj(object);
    }
    else if (flags->number_of_obj > 1 && !object) {
        two_and_more_obj(flags);
    }
    return struct_result;
}

static t_result *one_obj(char *obj) {
    t_result *struct_result = (t_result *)malloc(sizeof(t_result));
    t_lattrib **lattrib = NULL;
    t_flags *flags = NULL;
    int len_of_array = 0;
    int temp;
    int i = 0;
    char *size_blocks;
    char **array = NULL;
    DIR *d;
    struct dirent *directory;
    struct stat sb;
    d = opendir(obj);
    if (d) {
        while ((directory = readdir(d)) != NULL) {
            if (directory->d_name[0] != '.') {
                len_of_array++;
            }
        }
        closedir(d);
        d = opendir(obj);
        array = (char **)malloc(sizeof(char *) * len_of_array);
        while ((directory = readdir(d)) != NULL) {
            if (directory->d_name[0] != '.') {
                mx_size_align_right(lattrib, flags);
            }
        }
        closedir(d);
        //mx_alphabet_sort2(array, len_of_array);
        //mx_output_by_size_of_wind(array, len_of_array);
        struct_result->result = (char **)malloc(sizeof(char *) * len_of_array);
        for (int k = 0; k < len_of_array; ++k) {
            struct_result->result[k] = mx_strdup(array[k]);
        }
        struct_result->length = len_of_array;
        mx_strdel(&array[len_of_array - 1]);
        mx_del_strarr(&array);
    }
    return struct_result;
}

static char *trim(char *string, char **current_file) {
    int count = 0;
    int index = 0;
    bool has_slash = false;
    char *res = NULL;
    int len = mx_strlen(string);
    for (int j = 0; j < len; ++j) {
        if (*string == '/') {
            has_slash = true;
            index = count;
        }
        string++;
        count++;
    }
    string -= count;
    res = mx_strnew(index);
    if (has_slash) {
        for (int i = 0; i <= index; i++) {
            *res = *string;
            res++;
            string++;
        }
        index++;
    }
    *current_file = mx_strdup(string);
    string -= index;
    res -= index;
    if (index == 0) {
        res = mx_strcpy(res, ".");
    }
    return res;
}

static void two_and_more_obj(t_flags *flags) {
    t_result *struct_result = NULL;
    t_sorted_odj *sort = (t_sorted_odj *)malloc(sizeof(t_sorted_odj));
    sort->len_of_dirs_array = sort->len_of_files_array = 0;
    mx_file_dir_sort(sort, flags);
    char **array = NULL;
    if (sort->len_of_files_array != 0) {
        mx_alphabet_sort(sort->files, sort->len_of_files_array);
        add_inode_to_name_of_file(sort);
    }
    if (sort->len_of_dirs_array != 0) {
        mx_alphabet_sort(sort->dirs, sort->len_of_dirs_array);
    }
    if (sort->len_of_files_array != 0) {
        mx_output_by_size_of_wind(sort->files, sort->len_of_files_array);
    }
    for (int j = 0; j < sort->len_of_dirs_array; ++j) {
        if (flags->number_of_obj != 1) {
            if (j != 0 || sort->len_of_files_array != 0)
                mx_printchar('\n');
            mx_printstr(sort->dirs[j]);
            mx_printstr(":\n");
        }
        struct_result = one_obj(sort->dirs[j]);
        mx_output_by_size_of_wind(struct_result->result, struct_result->length);
        for (int i = 0; i < struct_result->length; ++i) {
            mx_strdel(&struct_result->result[i]);
        }
        if (struct_result->result)
            free(struct_result->result);
        if (struct_result)
            free(struct_result);
    }
    mx_del_strarr(&sort->files);
    mx_del_strarr(&sort->dirs);
    free(sort);
}

static void add_inode_to_name_of_file(t_sorted_odj *sort) {
    char **array = (char **)malloc(sizeof(char *) * sort->len_of_files_array);
    DIR *d;
    struct dirent *directory;
    char *inode;
    for (int i = 0; i < sort->len_of_files_array; ++i) {
        char *current_file;
        char *current_dir = trim(sort->files[i], &current_file);
        d = opendir(current_dir);
        while ((directory = readdir(d)) != NULL) {
            if (mx_strcmp(directory->d_name, current_file) == 0) {
                array[i] = mx_strnew(mx_strlen(sort->files[i]) + mx_intlen(directory->d_ino) + 1);
                inode = mx_itoa(directory->d_ino);
                array[i] = mx_strcpy(array[i], inode);
                array[i] = mx_strcat(array[i], " ");
                array[i] = mx_strcat(array[i], sort->files[i]);
                mx_strdel(&inode);
            }
        }
        closedir(d);
        mx_strdel(&current_dir);
        mx_strdel(&current_file);
    }
    for (int j = 0; j < sort->len_of_files_array; ++j) {
        mx_strdel(&sort->files[j]);
        sort->files[j] = mx_strdup(array[j]);
        mx_strdel(&array[j]);
    }
    mx_del_strarr(&array);
}
