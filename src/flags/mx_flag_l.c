#include "uls.h"

static void one_obj(char *obj, t_flags *flags, t_lattrib **lattrib);
static void get_attributes(t_lattrib **lattrib, struct stat sb, int i,
                            struct dirent *dir);
static void get_acl_xattr(t_lattrib **lattrib, int i);
static void total_blocks(t_flags *flags, t_lattrib **lattrib);

t_lattrib **mx_flag_l(t_flags *flags, t_sorted_odj *sort) {
    t_lattrib **lattrib = (t_lattrib **)malloc(sizeof(t_lattrib *) *
                            flags->num_dir_file);
    for (int i = 0; i < flags->num_dir_file; i++) {
        lattrib[i] = malloc(sizeof(t_lattrib));
    }
    if (flags->count_obj == 0) {
        one_obj(".", flags, lattrib);
    }
    return lattrib;
}

static void one_obj(char *obj, t_flags *flags, t_lattrib **lattrib) {
    DIR *d;
    struct stat sb;
    struct dirent *dir;
    int i = 0;

    d = opendir(obj);
        while ((dir = readdir(d)) != NULL)
            if (dir->d_name[0] != '.')
                flags->count_obj++;
    closedir(d);
    d = opendir(obj);
    while ((dir = readdir(d)) != NULL)
        if (dir->d_name[0] != '.') {
            lattrib[i]->name = mx_strdup(dir->d_name);
            stat(lattrib[i]->name, &sb);
            get_attributes(lattrib, sb, i, dir);
            get_acl_xattr(lattrib, i);
            i++;
        }
    closedir(d);
    mx_struct_sort(lattrib, flags);
// ./uls -l print output
    total_blocks(flags, lattrib);
    if (flags->switch_flags[0] == 0 && flags->switch_flags[1] == 1 &&
        flags->switch_flags[2] == 1 && flags->switch_flags[3] == 0 &&
        flags->switch_flags[4] == 0)
        mx_print_li_flag(lattrib, flags);
    if (flags->switch_flags[0] == 0 && flags->switch_flags[1] == 1 &&
        flags->switch_flags[2] == 0 && flags->switch_flags[3] == 0 &&
        flags->switch_flags[4] == 0)
        mx_print_l_flag(lattrib, flags);
}

static void get_attributes(t_lattrib **lattrib, struct stat sb, int i,
                            struct dirent *dir) {
    struct passwd *passwd; // get username

    mx_specify_type_file(sb, lattrib, i);
    mx_print_permissions_list(lattrib, sb, i);
    lattrib[i]->id = sb.st_ino;
    lattrib[i]->links = sb.st_nlink;
    passwd = getpwuid(sb.st_uid);
    lattrib[i]->user = mx_strdup(passwd->pw_name);
    lattrib[i]->group = sb.st_gid;
    lattrib[i]->size = sb.st_size;
    mx_time_modif(sb, lattrib, i);
    lattrib[i]->bl = sb.st_blocks;
}

static void get_acl_xattr(t_lattrib **lattrib, int i) {
    acl_t acl = NULL;
    acl_entry_t dummy;
    ssize_t xattr = 0;
    char acl_xattr;

    acl = acl_get_link_np(lattrib[i]->name, ACL_TYPE_EXTENDED);
    if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1) {
        acl_free(acl);
        acl = NULL;
    }
    xattr = listxattr(lattrib[i]->name, NULL, 0, XATTR_NOFOLLOW);
    if (xattr < 0)
        xattr = 0;
    if (xattr > 0)
        acl_xattr = '@';
    else if (acl != NULL)
        acl_xattr = '+';
    else
        acl_xattr = ' ';
    lattrib[i]->rights[9] = acl_xattr;
}

static void total_blocks(t_flags *flags, t_lattrib **lattrib) {
    int bl_sum = 0;
    for (int i = 0; i < flags->count_obj; i++) {
        bl_sum += lattrib[i]->bl;
    }
    mx_printstr("total ");
    mx_printint(bl_sum);
    mx_printchar('\n');
}
