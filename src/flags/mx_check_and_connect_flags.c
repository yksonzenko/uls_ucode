#include "uls.h"

void mx_check_and_connect_flags(t_flags *flags, t_sorted_odj *sort) {
    t_lattrib **lattrib = NULL;
    t_result *result_of_work_i = NULL;
// all flags: -a -l -i -h -p -1 -A -r -s

// flag -l
        if (flags->switch_flags[0] == 0 && flags->switch_flags[1] == 1 &&
            flags->switch_flags[2] == 0)
            lattrib = mx_flag_l(flags, sort);
// flags -i and -l
        if (flags->switch_flags[1] == 1 && flags->switch_flags[2] == 1)
            mx_flag_l(flags, sort);
// flags -h and -l
        if (flags->switch_flags[1] == 1 && flags->switch_flags[3] == 1) {
            mx_flag_h(lattrib, flags);
            mx_print_lh_flag(lattrib, flags);
        }
// flags -h
        if (flags->switch_flags[0] == 0 && flags->switch_flags[1] == 0 &&
            flags->switch_flags[2] == 0 && flags->switch_flags[3] == 1 &&
            flags->switch_flags[4] == 0)
            mx_print_root_files(flags);
// flags -l -i -h
        // if (flags->switch_flags[0] == 0 && flags->switch_flags[1] == 1 &&
        //     flags->switch_flags[2] == 1 && flags->switch_flags[3] == 1 &&
        //     flags->switch_flags[4] == 0)
        //     mx_print_flag_lih(flags, sort);
// flags -p
        if (flags->switch_flags[0] == 0 && flags->switch_flags[1] == 0 &&
            flags->switch_flags[2] == 0 && flags->switch_flags[3] == 0 &&
            flags->switch_flags[4] == 1)
            mx_flag_p(flags);
}
