#include "uls.h"

void mx_get_acl_xattr(t_lattrib **lattrib, int i) {
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
    if (xattr > 0)
        acl_xattr = '@';
    else if (acl != NULL)
        acl_xattr = '+';
    else
        acl_xattr = ' ';
    lattrib[i]->rights[9] = acl_xattr;
}
