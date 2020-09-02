#include "yksuls.h"

void mx_print_root_files(t_flags *flags) {
    flags->count_obj = 0;
    DIR *d;
    struct dirent *dir;

    d = opendir(".");
    if (flags->argc == 1) {
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
                flags->all_obj[i] = mx_strnew(dir->d_namlen);
                flags->all_obj[i] = mx_strcpy(flags->all_obj[i], dir->d_name);
                i++;
            }
        flags->all_obj[i] = NULL;
        mx_bubble_sort(flags->all_obj, flags->count_obj);
        mx_print_strarr(flags->all_obj, "\t"); // TODO change function for output
        mx_printchar('\n');
        mx_del_strarr(&flags->all_obj);
        closedir(d);
    }
}
