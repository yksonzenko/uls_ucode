#include "uls.h"

void mx_print_root_files(t_flags *flags) {
    flags->count_obj = 0;
    DIR *d;
    struct dirent *dir;

    d = opendir(".");
        if (d) {
            while ((dir = readdir(d)) != NULL)
                if (dir->d_name[0] != '.')
                    flags->count_obj++;
        }
    closedir(d);
    d = opendir(".");
    int i = 0;
    flags->all_obj = (char **)malloc(sizeof(char *) * flags->count_obj + 1);
    while ((dir = readdir(d)) != NULL)
        if (dir->d_name[0] != '.') {
            flags->all_obj[i] = mx_strdup(dir->d_name);
            i++;
        }
    mx_bubble_sort(flags->all_obj, flags->count_obj);
    if (isatty(1)) {
        mx_output_by_size_of_wind(flags->all_obj, flags->count_obj);
    }
    else {
        mx_output_in_one_column(flags->all_obj, flags->count_obj);
    }
    mx_del_strarr(&flags->all_obj);
    closedir(d);
}
