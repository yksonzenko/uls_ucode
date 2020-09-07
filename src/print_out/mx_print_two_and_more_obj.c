#include "uls.h"

void mx_print_two_and_more_obj(t_flags *flags) {
    t_sorted_odj *sort = (t_sorted_odj *)malloc(sizeof(t_sorted_odj));
    sort->len_of_dirs_array = sort->len_of_files_array = 0;
    // /*flags->all_obj = */ mx_store_all_obj_array(flags);
    // mx_check_and_rewrite_obj(flags);
    mx_file_dir_sort(sort, flags);
    if (sort->len_of_files_array != 0) {
        mx_alphabet_sort(sort->files, sort->len_of_files_array);
    }
    if (sort->len_of_dirs_array != 0) {
        mx_alphabet_sort(sort->dirs, sort->len_of_dirs_array);
    }
    if (sort->len_of_files_array != 0) {
        mx_output_by_size_of_wind(sort->files, sort->len_of_files_array);
    }
    for (int j = 0; j < sort->len_of_dirs_array; ++j) {
        if (j != 0 || sort->len_of_files_array != 0)
            mx_printchar('\n');
        mx_printstr(sort->dirs[j]);
        mx_printstr(":\n");
        mx_print_one_obj(sort->dirs[j]);
    }
    mx_del_strarr(&sort->files);
    mx_del_strarr(&sort->dirs);
    free(sort);
}
