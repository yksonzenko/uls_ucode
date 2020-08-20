#include "yksuls.h"



int main(int argc, char **argv) {
    t_flags *flags = (t_flags*)malloc(sizeof(t_flags));
    flags->all_flags = (char **)malloc(sizeof(char *) * 3);
    flags->switch_flags = (int *)malloc(sizeof(int) * 3);
    flags->argc = argc;
    flags->argv = argv;

// if just ./uls
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (flags->argc == 1) {
        if (d) {
            while ((dir = readdir(d)) != NULL)
                if (dir->d_name[0] != '.') {
                    mx_printstr(dir->d_name);
                    mx_printchar('\n');
                }
        }
        closedir(d);
    }
    // mx_printint(flags->argc);
    mx_check_flags(flags);
}
