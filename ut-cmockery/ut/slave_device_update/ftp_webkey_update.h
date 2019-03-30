#ifndef __FTP_WEBKEY_UPDATE_H__
#define __FTP_WEBKEY_UPDATE_H__
#include <inttypes.h>
#include <stdbool.h>

struct s_webkey_update {
    const bool *link_status;
    uint16_t *current_crc;
    uint16_t *owned_crc;
    const char *webkey_name;
};

void webkey_update_init(void);
void webkey_update_setup(bool* link_st, uint16_t *current_crc,
                         uint16_t *owned_crc, const char *path);
void webkey_update_exit(void);
bool check_web_file_need_update(void);
void save_webkey_crc(void);
void set_webkey_can_del(void);

#endif  // __FTP_WEBKEY_UPDATE_H__
