#include "yksuls.h"

static void check_what_flag(t_flags *flags);
static void connect_flags(t_flags *flags);

void mx_check_flags(t_flags *flags) {
// searching for flags
    flags->switch_flags = (int *)malloc(sizeof(int) * 3);
    for (int i = 0; i < 3; i++) {
        flags->switch_flags[i] = 0;
        // printf("%d\t", flags->switch_flags[i]);
    }
    // printf("\n");
    flags->all_flags = mx_strsplit(FLAGS, ' ');
    // for (int j = 0; flags->all_flags[j]; j++) {
    //     printf("%s\t", flags->all_flags[j]);
    // }
    // exit(0);
    // printf("\n");
    // mx_printint(flags->argc);
    for (int k = 1; k < flags->argc; k++) {
        if (flags->argv[k][0] == '-') {
            for (int h = 1; flags->argv[k][h]; h++) {
                for (int j = 0; flags->all_flags[j]; j++) {
                    // printf("TEST\n");
                    // printf("ARGV: %c\n", argv[k][h]);
                    // printf("FLAG in arr: %s\n\n", flags->all_flags[j]);
                    if (flags->argv[k][h] == flags->all_flags[j][0]) {
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

static void check_what_flag(t_flags *flags) {
    for (int i =0; i < 3; i++) {
        printf("! %d ", flags->fi);
    }
    if (flags->fi == 0) // flag -a
        printf("---flag 'a'---\n");
    if (flags->fi == 1) // flag -l
        printf("---flag 'l'---\n");
    if (flags->fi == 2) // flag -i
        mx_flag_i(flags);
}
// point which flag to be used
static void connect_flags(t_flags *flags) {
    for (flags->fi = 0; flags->fi < 3; flags->fi++)
        if (flags->switch_flags[flags->fi] == 1){
            printf("INDEX2222: %d\n", flags->fi);
            check_what_flag(flags);
        }
}
