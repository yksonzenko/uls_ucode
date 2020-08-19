#include "yksuls.h"

static void check_what_flag(t_flags *flags, int fi) {
    // printf("INDEX: %d\n", fi);
    if (fi == 0)
        printf("---flag 'a'---\n");
    if (fi == 1)
        printf("---flag 'l'---\n");
    if (fi == 2)
        mx_flag_i(flags);
}
// point which flag to be used
static void connect_flags(t_flags *flags) {
    for (int i = 0; i < 3; i++)
        if (flags->switch_flags[i] == 1)
            check_what_flag(flags, i);
}

int main(int argc, char **argv) {
    t_flags *flags = (t_flags*)malloc(sizeof(t_flags));
    flags->all_flags = (char **)malloc(sizeof(char *) * 3);
    flags->switch_flags = (int *)malloc(sizeof(int) * 3);

// if just ./uls
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (argc == 1) {
        if (d) {
            while ((dir = readdir(d)) != NULL)
                if (dir->d_name[0] != '.') {
                    mx_printstr(dir->d_name);
                    mx_printchar('\n');
                }
        }
        closedir(d);
    }

// check for flags
    for (int i = 0; i < 3; i++) {
        flags->switch_flags[i] = 0;
        // printf("%d\t", flags->switch_flags[i]);
    }
    // printf("\n");
    flags->all_flags = mx_strsplit(FLAGS, ' ');

    // for (int j = 0; flags->all_flags[j]; j++) {
        // printf("%s\t", flags->all_flags[j]);
    // }
    // printf("\n");
    for (int k = 1; k < argc; k++) {
        if (argv[k][0] == '-') {
            for (int h = 1; argv[k][h]; h++) {
                for (int j = 0; flags->all_flags[j]; j++) {
                    // printf("TEST\n");
                    // printf("ARGV: %c\n", argv[k][h]);
                    // printf("FLAG in arr: %s\n\n", flags->all_flags[j]);
                    if (mx_strcmp(&argv[k][h], flags->all_flags[j]) == 0) {
                        // printf("\r\33[2K\033[32;1mCOMPARED\033[0m\n");
                        flags->switch_flags[j] = 1;
                        // printf("%d\t", flags->switch_flags[0]);
                        // printf("%d\t", flags->switch_flags[1]);
                        // printf("%d\t\n", flags->switch_flags[2]);
                    }
                }
            }
        }
    }
    connect_flags(flags);
}
