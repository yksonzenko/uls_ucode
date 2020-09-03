#include "yksuls.h"

int main(int argc, char **argv) {
    t_flags *flags = (t_flags*)malloc(sizeof(t_flags));
    t_sorted_odj *sort = NULL;
    flags->all_flags = (char **)malloc(sizeof(char *) * 3);
    flags->switch_flags = (int *)malloc(sizeof(int) * 3);
    flags->argc = argc;
    flags->argv = argv;
    DIR *d;
    struct dirent *dir;

// check illegal flags
    mx_error_illegal_option(flags);
// if just ./uls
    d = opendir(".");
    if (flags->argc == 1)
        mx_print_root_files(flags);
// if ./uls + flags(-i -l -la ...)
    mx_check_flags(flags, sort);

    // system("leaks -q uls");
}
