#include "yksuls.h"

void mx_flag_a_l(t_flags *flags) {
    printf("FLAG -a and -l FUNCTION\n");
            // -----------
        printf("\n--switch_flags--\n");
        printf("%d\t", flags->switch_flags[0]);
        printf("%d\t", flags->switch_flags[1]);
        printf("%d\t\n\n", flags->switch_flags[2]);
        // -----------
}
