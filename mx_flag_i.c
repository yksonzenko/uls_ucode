#include "yksuls.h"

static void one_obj(char *obj);
static char *trim(char *string, char **current_file);
static void zero_obj();
static void two_and_more_obj(int number_of_obj, char **array_of_obj);
static void file_dir_sort(char ***files, char ***dirs, int number_of_obj, char **array_of_obj); //TODO struct to sort all obj to files/non + dirs


void mx_flag_i(int number_of_obj, char **array_of_obj) { //TODO make three+ obj
    if (number_of_obj == 1) {
        one_obj(array_of_obj[2]);
    }
    else if (number_of_obj == 0) {
        zero_obj();
    }
    else if (number_of_obj >= 2) {
        two_and_more_obj(number_of_obj, array_of_obj);
    }
}

static void one_obj(char *obj) {
    DIR *d;
    struct dirent *directory;
    d = opendir(obj);
    if (d) {
        while ((directory = readdir(d)) != NULL) {
            if (directory->d_name[0] != '.') {
                mx_printint(directory->d_ino);
                mx_printchar(' ');
                mx_printstr(directory->d_name);
                mx_printchar('\n');
            }
        }
        closedir(d);
    }
    else if (open(obj, O_RDONLY) != -1) {
        char *current_file;
        char *current_dir = trim(obj, &current_file);
        d = opendir(current_dir);
        while ((directory = readdir(d)) != NULL) {
            if (mx_strcmp(directory->d_name, current_file) == 0) {
                mx_printint(directory->d_ino);
                mx_printchar(' ');
                mx_printstr(directory->d_name);
                mx_printchar('\n');
            }
        }
        closedir(d);
        mx_strdel(&current_dir);
        mx_strdel(&current_file);
    }
    else {
        mx_printerr("ls: ");
        mx_printerr(obj);
        mx_printerr(": No such file or directory");
    }
}

static void zero_obj() {
    DIR *d;
    struct dirent *directory;
    d = opendir(".");
    if (d) {
        while ((directory = readdir(d)) != NULL) {
            if (directory->d_name[0] != '.') {
                mx_printint(directory->d_ino);
                mx_printchar(' ');
                mx_printstr(directory->d_name);
                mx_printchar('\n');
            }
        }
        closedir(d);
    }
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

static void two_and_more_obj(int number_of_obj, char **array_of_obj) { // ./uls -i stage2 test Desktop test1
    char **files = NULL;
    char **dirs = NULL;
    file_dir_sort(&files, &dirs, number_of_obj,array_of_obj);
//    for (int i = 2; i <= number_of_obj + 1; ++i) {
//        one_obj(array_of_obj[i]);
//    }
}

static void file_dir_sort(char ***files, char ***dirs, int number_of_obj, char **array_of_obj) {
    int a = 0;
    int b = 0;
    *files = (char **)malloc(sizeof(char *) * number_of_obj * 10);
    *dirs = (char **)malloc(sizeof(char *) * number_of_obj * 10);
    for (int i = 0; i < number_of_obj; ++i) {
        *(files[i]) = mx_strnew(10);
        *(dirs[i]) = mx_strnew(10);
    }
    for (int j = 2; j < number_of_obj; ++j) {
        if (opendir(array_of_obj[j])) {
            *(dirs[a]) = mx_realloc(*(dirs[a]), mx_strlen(array_of_obj[j]));
            *(dirs[a]) = mx_strcpy(*(dirs[a]), array_of_obj[j]);
            a++;
        } else {
            *(files[b]) = mx_realloc(*(files[b]), mx_strlen(array_of_obj[j]));
            *(files[b]) = mx_strcpy(*(files[b]), array_of_obj[j]);
            b++;
        }
    }
}
