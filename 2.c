#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <getopt.h>
#include <grp.h>
#include <pwd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sysexits.h>
#include <time.h>
#include <unistd.h>

static char* global_dir = ".";

struct Options
{
    bool using_a;
    bool using_d;
    bool using_h;
    bool using_i;
    bool using_l;
    bool using_p;
    bool using_Q;
    bool using_R;
    bool using_S;
    bool using_t;
    bool using_U;
};
