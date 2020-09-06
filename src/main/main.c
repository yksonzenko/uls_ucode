#include "uls.h"

int main(int argc, char **argv) {
    t_flags *flags = (t_flags*)malloc(sizeof(t_flags));
    t_sorted_odj *sort = NULL;
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
    d = opendir(".");

// if just ./uls
    if (flags->argc == 1)
        mx_print_root_files(flags);
    if (flags->argc > 1 && flags->argv[1][0] != '-') {
        // flags->all_obj = mx_store_all_obj_array(flags);
        mx_print_root_dirs_files(flags);
    }
// check illegal flags
    mx_error_illegal_option(flags);
// if ./uls + flags(-i -l -la ...)
    mx_check_flags(flags, sort);
    mx_check_and_connect_flags(flags, sort);
    // system("leaks -q uls");
}
