#include "yksuls.h"

void mx_time_modif(struct stat sb, t_lattrib **lattrib, int i) {
    time_t mytime = time(NULL);
    char * time_str = ctime(&mytime);
    time_str[strlen(time_str)-1] = '\0';
    printf("Current Time : %s\n", time_str);
}
