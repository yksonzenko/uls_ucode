#include "uls.h"

// void mx_get_acl_xattr(t_lattrib **lattrib, int i) {
void mx_get_acl_xattr(char *name, t_lattrib **lattrib, int i) {
    acl_t acl = NULL;
    acl_entry_t dummy;
    ssize_t xattr = 0;

    acl = acl_get_file(name, ACL_TYPE_EXTENDED);
    if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1) {
        acl_free(acl);
        acl = NULL;
    }
    xattr = listxattr(name, NULL, 0, XATTR_NOFOLLOW);
    if (xattr > 0)
        lattrib[i]->rights[9] = '@';
    else if (acl != NULL)
        lattrib[i]->rights[9] = '+';
    else
        lattrib[i]->rights[9] = ' ';
    // lattrib[i]->rights[9] = acl_xattr;
    // acl_t acl;
    // ssize_t xattr;
    // // char acl_xattr;

    // if ((xattr = listxattr(lattrib[i]->name, NULL, 0, XATTR_NOFOLLOW)) > 0)
    //     lattrib[i]->rights[9] = '@';
    // if ((acl = acl_get_file(lattrib[i]->name, ACL_TYPE_EXTENDED)) != (acl_t)NULL) {
    //     acl_free(acl);
    //     lattrib[i]->rights[9] = '+';
    // }
    // else
    //     lattrib[i]->rights[9] = ' ';
}
