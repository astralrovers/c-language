#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "update_inc.h"
#include "ftp_webkey_update.h"

static struct s_webkey_update *webkey_update = NULL;
static bool delete_flag = true;

static bool if_webkey_exist(void)
{
    struct stat state;
    FILE *file;
    if ((access(webkey_update->webkey_name, F_OK) == -1) ||
        (stat((char *)webkey_update->webkey_name, &state) == -1)) {
        return false;
    }
    if (state.st_size == 0) { return false; }
    if ((file = fopen(webkey_update->webkey_name, "r")) == NULL) {
        return false;
    }
    fclose(file);
    return true;
}

static bool is_master_link_ok(void)
{
    return *(webkey_update->link_status);
}

static uint16_t get_webkey_old_crc(void)
{
    return *(webkey_update->current_crc);
}

void save_webkey_crc(void)
{
    *(webkey_update->current_crc) = *(webkey_update->owned_crc);
}
 
static uint16_t get_webkey_new_crc(void)
{
    return *(webkey_update->owned_crc);
}

void set_webkey_can_del(void)
{
    delete_flag = true;
}

static void set_webkey_can_not_del(void)
{
    delete_flag = false;
}

static bool if_webkey_can_del(void)
{
    return delete_flag;
}

static bool if_webkey_not_change(void)
{
    return (get_webkey_old_crc() == get_webkey_new_crc());
}

static bool if_new_webkey_invalid(void)
{
    return (get_webkey_new_crc() == INVALID_CRC);
}

static void delete_webkey(void)
{
    remove(webkey_update->webkey_name);
    sync();
}

bool check_web_file_need_update(void)
{
    if (!is_master_link_ok()) { return false; }
    if (if_new_webkey_invalid() && if_webkey_can_del() && if_webkey_exist()) {
        delete_webkey();
        set_webkey_can_not_del();
    }
    if (if_webkey_not_change() || if_new_webkey_invalid()) {
        return false;
    }
    return true;
}

void webkey_update_init(void)
{
    webkey_update = (struct s_webkey_update* )malloc(sizeof(struct s_webkey_update));
    memset(webkey_update, 0, sizeof(struct s_webkey_update));
}

void webkey_update_setup(bool* link_st, uint16_t *current_crc,
                         uint16_t *owned_crc, const char *path)
{
    webkey_update->link_status = link_st;
    webkey_update->current_crc = current_crc;
    webkey_update->owned_crc = owned_crc;
    webkey_update->webkey_name = path;
}

void webkey_update_exit(void)
{
    if (!webkey_update) { return; }
    free(webkey_update); webkey_update = NULL;
}
