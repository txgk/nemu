#ifndef NM_FORM_H_
#define NM_FORM_H_

#include <nm_string.h>
#include <nm_vector.h>
#include <nm_ncurses.h>
#include <nm_usb_devices.h>

#include <form.h>
#include <pthread.h>

#define NM_FORM_EMPTY_MSG  "These fields cannot be empty:"
#define NM_FORM_VMNAME_MSG "This name is already used"

typedef FORM nm_form_t;
typedef FIELD nm_field_t;

typedef struct {
    nm_str_t driver;
    nm_str_t size;
} nm_vm_drive_t;

typedef struct {
    int form_len;
    int w_start_x;
    int w_cols;
    int w_rows;
    nm_window_t *form_window;
} nm_form_data_t;

typedef struct {
    nm_str_t driver;
    uint32_t count;
} nm_vm_ifs_t;

typedef struct {
    nm_str_t name;
    nm_usb_dev_t *device;
} nm_vm_usb_t;

typedef struct {
    uint32_t enable:1;
    uint32_t hostcpu_enable:1;
} nm_vm_kvm_t;

typedef struct {
    nm_str_t inst_path;
    nm_str_t mach;
    nm_str_t bios;
    nm_str_t kernel;
    nm_str_t cmdline;
    nm_str_t initrd;
    nm_str_t tty;
    nm_str_t socket;
    uint32_t installed:1;
} nm_vm_boot_t;

typedef struct {
    nm_str_t name;
    nm_str_t arch;
    nm_str_t cpus;
    nm_str_t memo;
    nm_str_t srcp;
    nm_str_t vncp;
    nm_vm_drive_t drive;
    nm_vm_ifs_t ifs;
    nm_vm_kvm_t kvm;
    uint32_t mouse_sync:1;
    uint32_t usb_enable:1;
} nm_vm_t;

typedef struct {
    int x;
    int y;
    const int *stop;
} nm_spinner_data_t;

nm_form_t *nm_post_form(nm_window_t *w, nm_field_t **field, int begin_x);
nm_form_t *nm_post_form__(nm_window_t *w, nm_field_t **field, int begin_x);
int nm_draw_form(nm_window_t *w, nm_form_t *form);
void nm_form_free(nm_form_t *form, nm_field_t **fields);
void nm_get_field_buf(nm_field_t *f, nm_str_t *res);
int nm_form_name_used(const nm_str_t *name);
void nm_form_get_last(uint64_t *mac, uint32_t *vnc);
void nm_form_update_last_mac(uint64_t mac);
void nm_form_update_last_vnc(uint32_t vnc);
int nm_print_empty_fields(const nm_vect_t *v);
const char *nm_form_select_drive(const nm_vect_t *drives);
void nm_vm_free(nm_vm_t *vm);
void nm_vm_free_boot(nm_vm_boot_t *vm);
void *nm_spinner(void *data);

extern const char *nm_form_yes_no[];
extern const char *nm_form_net_drv[];
extern const char *nm_form_drive_drv[];
extern const char *nm_form_macvtap[];

#define NM_FORM_MIN_LEN 30
#define NM_FORM_RATIO  0.80

#define nm_form_check_data(name, val, v)                      \
    {                                                         \
        if (val.len == 0)                                     \
            nm_vect_insert(&v, name, strlen(name) + 1, NULL); \
    }

#define nm_form_check_datap(name, val, v)                     \
    {                                                         \
        if (val->len == 0)                                    \
            nm_vect_insert(&v, name, strlen(name) + 1, NULL); \
    }

#define NM_INIT_VM_DRIVE { NM_INIT_STR, NM_INIT_STR }
#define NM_INIT_VM_IFS   { NM_INIT_STR, 0 }
#define NM_INIT_VM_USB   { NM_INIT_STR, NULL, 0 }
#define NM_INIT_VM_KVM   { 0, 0 }
#define NM_INIT_VM_BOOT  { NM_INIT_STR, NM_INIT_STR, NM_INIT_STR, \
                           NM_INIT_STR, NM_INIT_STR, NM_INIT_STR, \
                           NM_INIT_STR, NM_INIT_STR, 0 }
#define NM_INIT_SPINNER  { 0, 1, NULL }
#define NM_INIT_FORM_DATA { 0, 0, 0, 0, NULL }

#define NM_INIT_VM { NM_INIT_STR, NM_INIT_STR, NM_INIT_STR, \
                     NM_INIT_STR, NM_INIT_STR, NM_INIT_STR, \
                     NM_INIT_VM_DRIVE, NM_INIT_VM_IFS, \
                     NM_INIT_VM_KVM, 0, 0 }

#endif /* NM_FORM_H_ */
/* vim:set ts=4 sw=4 fdm=marker: */
