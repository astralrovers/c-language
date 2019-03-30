#ifndef __FTP_NORMAL_UPDATE_H__
#define __FTP_NORMAL_UPDATE_H__
#include <inttypes.h>
#include <stdbool.h>

struct s_slave_update {
    uint16_t *current_crc;
    uint16_t *owned_crc;
    uint8_t  *soft_version;
    uint8_t *update_dbg_status;
    uint8_t update_result;
};

void ftp_normal_update_init(void);
void ftp_normal_update_setup(uint16_t *current_crc, uint16_t *owned_crc,
                             uint8_t *version, uint8_t *dbg);
void ftp_normal_update_exit(void);

bool check_slv_need_update(void);
void set_backup_new_crc(void);
uint16_t get_backup_new_crc(void);
void recording_wrong_crc(void);
void recording_wrong_packet(void);

#endif  // FTP_NORMAL_UPDATE_H__
