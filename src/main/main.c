#include "yksuls.h"

int main(int argc, char **argv) {
    t_flags *flags = (t_flags*)malloc(sizeof(t_flags));
    flags->all_flags = (char **)malloc(sizeof(char *) * 3);
    flags->switch_flags = (int *)malloc(sizeof(int) * 3);
    flags->argc = argc;
    flags->argv = argv;

// if just ./uls
    mx_print_root_files(flags);
// if ./uls + flags(-i -l -la ...)
    mx_check_flags(flags);
}
