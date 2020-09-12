#include "uls.h"

int main(int argc, char **argv) {
    t_flags *flags = (t_flags*)malloc(sizeof(t_flags));
    t_sorted_odj *sort = (t_sorted_odj *)malloc(sizeof(t_sorted_odj));
    t_lattrib **lattrib = NULL;
    flags->argc = argc;
    flags->argv = argv;
    DIR *d;
    struct dirent *dir;
    flags->num_dir_file = 0;

    d = opendir(".");
        while ((dir = readdir(d)) != NULL)
            if (dir->d_name[0] != '.')
                flags->num_dir_file++;
    closedir(d);
// if just ./uls
    if (flags->argc == 1 || ((mx_strcmp(flags->argv[1], "-h") == 0) &&
        !flags->argv[2]) || ((mx_strcmp(flags->argv[1], "--") == 0) &&
        !flags->argv[2])) {
        mx_print_root_files(flags);
       exit(0);
    }
// check illegal flags
    mx_error_illegal_option(flags);

// if ./uls + flags(-i -l -la ...)
    mx_check_flags(flags, sort);
    mx_check_and_rewrite_obj(flags);
    mx_check_and_connect_flags(flags, sort);

    if (flags->argc > 1 && flags->count_flags == 0)
        mx_print_two_and_more_obj(flags);
    mx_printstr("\n\n");
     system("leaks -q uls");
}
