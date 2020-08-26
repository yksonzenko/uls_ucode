#include "yksuls.h"


void mx_flag_l(t_flags *flags) {
    // printf("FLAG -l FUNCTION\n");
	DIR *d;
    struct stat sb;
    struct dirent *dir;
    mx_printstr("\nid    bl ftype rights  links   user    group   size    time full     name\n\n");
    if (flags->argc == 2) {
    d = opendir(".");
    while ((dir = readdir(d)) != NULL) {
        if (dir->d_name[0] != '.') {
            char *string = mx_strdup(dir->d_name);
            stat(string , &sb);
            mx_printint(dir->d_ino);
            mx_printchar('\t');
            mx_printint(sb.st_blocks);
            mx_printchar(' ');
            switch (sb.st_mode & S_IFMT) {
                case S_IFBLK:  mx_printchar('b'); break; /*block device*/
                case S_IFCHR:  mx_printchar('c'); break; /*character device*/
                case S_IFDIR:  mx_printchar('d'); break; /*directory*/
                case S_IFIFO:  mx_printchar('p'); break; /*named pipe (fifo)*/
                case S_IFLNK:  mx_printchar('l'); break; /*symlink*/
                case S_IFREG:  mx_printchar('-'); break; /*regular file*/
                case S_IFSOCK: mx_printchar('s'); break; /*socket*/
                default:       mx_printchar('?'); break; /**/
            }
            char rights[] = "---------";
            int mode = sb.st_mode;
            if ((mode & 0000400) == 0000400)
                rights[0] = 'r';
            if ((mode & 0000200) == 0000200)
                rights[1] = 'w';
            if ((mode & 0000100) == 0000100)
                rights[2] = 'x';
            if ((mode & 0000040) == 0000040)
                rights[3] = 'r';
            if ((mode & 0000020) == 0000020)
                rights[4] = 'w';
            if ((mode & 0000010) == 0000010)
                rights[5] = 'x';
            if ((mode & 0000004) == 0000004)
                rights[6] = 'r';
            if ((mode & 0000002) == 0000002)
                rights[7] = 'w';
            if ((mode & 0000001) == 0000001)
                rights[8] = 'x';
            if ((mode & 0004000) == 0004000)
                rights[2] = 's';
            if ((mode & 0002000) == 0002000)
                rights[5] = 's';
            if ((mode & 0001000) == 0001000)
                rights[6] = 't';
            mx_printstr(rights);
            char buff[100];
            ssize_t lxattr = listxattr(string, buff, 100, 0);
            if (lxattr > 0)
                mx_printchar('@');
            mx_printchar('\t');
            // ssize_t gxattr = getxattr();
            mx_printint(sb.st_nlink);
            mx_printchar('\t');
            struct passwd *pwd;
            pwd = getpwuid(sb.st_uid);
            mx_printstr(pwd->pw_name);
            mx_printchar('\t');
            mx_printint(sb.st_gid);
            mx_printchar('\t');
            mx_printint(sb.st_size);
            mx_printchar('\t');
            char *time = ctime(&sb.st_mtime);
            time[mx_strlen(time) - 1] = '\0';
            mx_printstr(time);
            mx_printchar('\t');
            mx_printstr(dir->d_name);
            mx_printchar('\n');
        }
    }
    }
    // system("leaks uls");
}
    // system("leaks uls");
