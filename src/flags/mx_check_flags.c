#include "yksuls.h"

// point which flag to be used
static void check_and_connect_flags(t_flags *flags, t_sorted_odj *sort);
static void store_all_obj_array(t_flags *flags, int k);

// searching for flags
void mx_check_flags(t_flags *flags, t_sorted_odj *sort) {
    flags->count_obj = 0;
    flags->switch_flags = (int *)malloc(sizeof(int) * 3);
    flags->all_obj = (char **)malloc(sizeof(char *) * 1000);

    for (int i = 0; i < 3; i++)
        flags->switch_flags[i] = 0;
    flags->all_flags = mx_strsplit(FLAGS, ' ');
    // mx_illegal_option(flags);
    for (int k = 1; k < flags->argc; k++) {
        if (flags->argv[k][0] == '-' && flags->argv[k][1]) {
            for (int h = 1; flags->argv[k][h]; h++) {
                for (int j = 0; flags->all_flags[j]; j++)
                    if (flags->argv[k][h] == flags->all_flags[j][0])
                        flags->switch_flags[j] = 1;
            }
        }
// move all obj after '--' to new 2d array
        if (flags->argv[k][0] == '-' && flags->argv[k][1] == '-' &&
            !flags->argv[k][2]) {
            k += 1;
            store_all_obj_array(flags, k);
            printf("OBJ_COUNT: %d\n", flags->count_obj);
            mx_print_strarr(flags->all_obj, " ");
            break;
        }
// move all obj after flags to new 2d array
        if (flags->argv[k][0] != '-') {
            store_all_obj_array(flags, k);
            // printf("OBJ_COUNT: %d\n", flags->count_obj);
            // printf("ALL_OBJECTS\n");
            // mx_print_strarr(flags->all_obj, "\t");
            break;
        }
    }
// -----------
        // printf("\n--switch_flags--\n");
        // printf("%d\t", flags->switch_flags[0]);
        // printf("%d\t", flags->switch_flags[1]);
        // printf("%d\t\n\n", flags->switch_flags[2]);
// -----------
    check_and_connect_flags(flags, sort);
}

static void store_all_obj_array(t_flags *flags, int k) {
    for (int i = 0; flags->argv[k]; i++, k++) {
        //flags->all_obj[i] = flags->argv[k];
        flags->all_obj[i] = mx_strdup(flags->argv[k]);
        flags->count_obj++;
    }
}

static void check_and_connect_flags(t_flags *flags, t_sorted_odj *sort) {
// flag -a
    if (flags->switch_flags[0] == 1 && flags->switch_flags[1] == 0 &&
        flags->switch_flags[2] == 0)
        mx_flag_a(flags);
// flag -l
    if (flags->switch_flags[0] == 0 && flags->switch_flags[1] == 1 &&
        flags->switch_flags[2] == 0)
        mx_flag_l(flags, sort);
// flag -i
    if (flags->switch_flags[0] == 0 && flags->switch_flags[1] == 0 &&
        flags->switch_flags[2] == 1)
        mx_flag_i(flags, sort);
// flags -a and -l
    if (flags->switch_flags[0] == 1 && flags->switch_flags[1] == 1)
        mx_flag_a_l(flags);
}
