#include "yksuls.h"

static void check_what_flag(t_flags *flags);
// point which flag to be used
static void connect_flags(t_flags *flags);
static void store_all_obj_array(t_flags *flags, int k);

void mx_check_flags(t_flags *flags) {
// searching for flags
    flags->count_obj = 0;
    flags->switch_flags = (int *)malloc(sizeof(int) * 3);
    flags->all_obj = (char **)malloc(sizeof(char *) * 1000);

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
    bool t;
    for (int k = 1; k < flags->argc; k++) {
        if (flags->argv[k][0] == '-') {
            t = true;
            for (int h = 1; flags->argv[k][h]; h++) {
                for (int j = 0; flags->all_flags[j]; j++) {
                    // printf("TEST\n");
                    // printf("ARGV: %c\n", flags->argv[k][h]);
                    // printf("FLAG in arr: %s\n\n", flags->all_flags[j]);
                    if (flags->argv[k][h] == flags->all_flags[j][0])
                        flags->switch_flags[j] = 1;
                    else {
                        mx_printerr("./uls: illegal option -- ");
                        mx_printerr(&flags->argv[k][h]);
                        break;
                    }
                }
            }
// move all obj after '--' to new 2d array
            if (flags->argv[k][2] == '\0') {
                k += 2;
                store_all_obj_array(flags, k);
                printf("%d\n", flags->count_obj);
                mx_print_strarr(flags->all_obj, " ");
                break;
            }
            printf("K: %d\n", k);
            if (mx_isalpha(flags->argv[k][0])) {
                store_all_obj_array(flags, k);
            }
        }
    }
// -----------
        printf("\n--switch_flags--\n");
        printf("%d\t", flags->switch_flags[0]);
        printf("%d\t", flags->switch_flags[1]);
        printf("%d\t\n\n", flags->switch_flags[2]);
// -----------
    connect_flags(flags);
}

static void store_all_obj_array(t_flags *flags, int k) {
    for (int i = 0; flags->argv[k]; i++, k++) {
        flags->all_obj[i] = flags->argv[k];
        flags->count_obj++;
    }
}

static void check_what_flag(t_flags *flags) {
    if (flags->fi == 0) // flag -a
        mx_flag_a(flags);
    if (flags->fi == 1) // flag -l
        mx_flag_l(flags);
    if (flags->fi == 2) // flag -i
        mx_flag_i(flags);
}

static void connect_flags(t_flags *flags) {
    for (flags->fi = 0; flags->fi < 3; flags->fi++)
        if (flags->switch_flags[flags->fi] == 1){
            check_what_flag(flags);
        }
}
