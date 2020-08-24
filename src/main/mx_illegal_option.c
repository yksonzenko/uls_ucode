#include "yksuls.h"

void mx_illegal_option(char *not_flag) {
    mx_printerr(ILLEGAL_OPT);
    mx_printerr(not_flag);
    mx_printerr("\n");
    mx_printerr(INVALID_USAGE);
    mx_printerr("\n");
    exit(1);
}
