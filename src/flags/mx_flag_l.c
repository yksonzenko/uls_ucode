#include "yksuls.h"

static void one_obj(char *obj, t_flags *flags, t_lattrib **lattrib);

void mx_flag_l(t_flags *flags, t_sorted_odj *sort) {
    t_lattrib **lattrib = (t_lattrib **)malloc(sizeof(t_lattrib *) * 10);
    for (int i = 0; i < 10; i++)
        lattrib[i] = malloc(sizeof(t_lattrib));
    mx_printstr("\nid    bl ftype rights  links   user    group   size    time full     name\n\n");
    if (flags->count_obj == 0) {
        one_obj(".", flags, lattrib);
    }
}

static void one_obj(char *obj, t_flags *flags, t_lattrib **lattrib) {
    DIR *d;
    struct stat sb;
    struct dirent *dir;

    d = opendir(obj);
        while ((dir = readdir(d)) != NULL)
            if (dir->d_name[0] != '.')
                flags->count_obj++;
    closedir(d);
    d = opendir(obj);
    while ((dir = readdir(d)) != NULL) {
        if (dir->d_name[0] != '.') {
            char *string = mx_strdup(dir->d_name);
            stat(string , &sb);
    // mx_specify_type_file(sb);
    for (int i = 0; i < flags->count_obj; i++)
        mx_print_permissions_list(lattrib, sb);
    // mx_printstr(lattrib[0]->rights);
    // mx_printchar('\t');



// // id flag -i
//             lattrib->id = mx_strdup(dir->d_ino);
//             mx_printint(lattrib->id);
//             // mx_printint(dir->d_ino);
//             mx_printchar('\t');
// // bl flag -s
//             mx_printint(sb.st_blocks);
//             mx_printchar(' ');
// // rights
//             mx_specify_type_file(sb);
//             mx_print_permissions_list(lattrib, sb);
// // end rights
//             char buff[100];
//             ssize_t lxattr = listxattr(string, buff, 100, 0);
//             if (lxattr > 0)
//                 mx_printchar('@');
//             mx_printchar('\t');
//             // ssize_t gxattr = getxattr();
//             mx_printint(sb.st_nlink);
//             mx_printchar('\t');
//             struct passwd *pwd;
//             pwd = getpwuid(sb.st_uid);
//             mx_printstr(pwd->pw_name);
//             mx_printchar('\t');
//             mx_printint(sb.st_gid);
//             mx_printchar('\t');
//             mx_printint(sb.st_size);
//             mx_printchar('\t');
//             char *time = ctime(&sb.st_mtime);
//             time[mx_strlen(time) - 1] = '\0';
//             mx_printstr(time);
//             mx_printchar('\t');
//             mx_printstr(dir->d_name);
//             mx_printchar('\n');
        }
    }
    mx_specify_type_file(sb);
    mx_print_strarr(&lattrib[0]->rights, "\n");
}
