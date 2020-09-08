#include "uls.h"

char **store_all_obj_array(t_flags *flags, int k);

// searching for flags
void mx_check_flags(t_flags *flags, t_sorted_odj *sort) {
    flags->count_obj = 0;
    flags->count_flags = 0;
    flags->switch_flags = (int *)malloc(sizeof(int) * 9);
    flags->all_obj = (char **)malloc(sizeof(char *) * 1000);

    for (int i = 0; i < 9; i++)
        flags->switch_flags[i] = 0;
    flags->all_flags = mx_strsplit(FLAGS, ' ');
    for (int k = 1; k < flags->argc; k++) {
        if (flags->argv[k][0] == '-' && flags->argv[k][1]) {
            for (int h = 1; flags->argv[k][h]; h++) {
                for (int j = 0; flags->all_flags[j]; j++)
                    if (flags->argv[k][h] == flags->all_flags[j][0]) {
                        flags->switch_flags[j] = 1;
                        flags->count_flags += 1;
                    }
            }
        /*TRY TO CHECK HERE IF JUST ./ULS AND DIRS/FILES*/
        }
// move all obj after flags to new 2d array
        if (flags->argv[k][0] != '-' || (flags->argv[k][0] == '-' &&
            !flags->argv[k][1])) {
            flags->all_obj = store_all_obj_array(flags, k);
            // mx_check_and_rewrite_obj(flags);
            // printf("OBJ_COUNT: %d\n", flags->count_obj);
            // printf("ALL_OBJECTS: \n");
            // mx_print_strarr(flags->all_obj, "\t");
            // mx_printchar('\n');
            break;
        }
// move all obj after '--' to new 2d array
        if (flags->argv[k][0] == '-' && flags->argv[k][1] == '-' &&
            !flags->argv[k][2]) {
            k += 1;
            flags->all_obj = store_all_obj_array(flags, k);
            mx_check_and_rewrite_obj(flags);
            mx_file_dir_sort(sort, flags);
            // printf("OBJ_COUNT: %d\n", flags->count_obj);
                // mx_print_strarr(flags->all_obj, " ");
        }
    }
// -----------
        // printf("\n--switch_flags--\n");
        // printf("%d\t", flags->switch_flags[0]);
        // printf("%d\t", flags->switch_flags[1]);
        // printf("%d\t", flags->switch_flags[2]);
        // printf("%d\t", flags->switch_flags[3]);
        // printf("%d\t", flags->switch_flags[4]);
        // printf("%d\t", flags->switch_flags[5]);
        // printf("%d\t", flags->switch_flags[6]);
        // printf("%d\t\n\n", flags->switch_flags[7]);
// -----------
    // if (flags->all_obj) {
    //     mx_strdel(&flags->all_obj[999]);
    //     mx_del_strarr(&flags->all_obj);
    // }
}

char **store_all_obj_array(t_flags *flags, int k) {
    for (int i = 0; flags->argv[k]; i++, k++) {
        flags->all_obj[i] = mx_strdup(flags->argv[k]);
        flags->count_obj++;
    }
    return flags->all_obj;
}
