#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "update_inc.h"
#include "ftp_normal_update.h"

static uint16_t _wrong_crc = INVALID_CRC;
static uint16_t _wrong_packet = INVALID_CRC;
static uint16_t _new_crc_backup;
static struct s_slave_update *normal_update = NULL;

void ftp_normal_update_init(void)
{
    normal_update = (struct s_slave_update* )malloc(sizeof(struct s_slave_update));
    memset(normal_update, 0, sizeof(struct s_slave_update));
}

void ftp_normal_update_setup(uint16_t *current_crc, uint16_t *owned_crc,
                             uint8_t *version, uint8_t *dbg)
{
    normal_update->current_crc = current_crc;
    normal_update->owned_crc = owned_crc;
    normal_update->soft_version = version;
    normal_update->update_dbg_status = dbg;
    normal_update->update_result = 0;
}

void ftp_normal_update_exit(void)
{
    free(normal_update);
    normal_update = NULL;
}

void recording_wrong_packet(void)
{
    _wrong_packet = _new_crc_backup;
}

void recording_wrong_crc(void)
{
    _wrong_crc = _new_crc_backup;
}

static uint16_t get_slv_new_crc(void);

uint16_t get_backup_new_crc(void)
{
    return _new_crc_backup;
}

void set_backup_new_crc(void)
{
    _new_crc_backup = get_slv_new_crc();
}

static uint16_t get_slv_new_crc(void)
{
    return *(normal_update->owned_crc);
}

static uint16_t get_slv_old_crc(void)
{
    return *(normal_update->current_crc);
}

static bool if_new_crc_invalid(void)
{
    return (get_slv_new_crc() == INVALID_CRC);
}

static bool if_new_crc_not_change(void)
{
    return (get_slv_old_crc() == get_slv_new_crc());
}

static bool is_wrong_crc(void)
{
    return (get_slv_new_crc() == _wrong_crc);
}

static bool is_wrong_packet(void)
{
    return (get_slv_new_crc() == _wrong_packet);
}

static void set_slv_soft_version(uint8_t version)
{
    *(normal_update->soft_version) = version;
}

static bool is_update_dbg(void)
{
    return *(normal_update->update_dbg_status) ? true : false;
}

bool check_slv_need_update(void)
{
    if (if_new_crc_invalid() || if_new_crc_not_change() ||
         is_wrong_crc() || is_wrong_packet() ||
         is_update_dbg()) {
        if (if_new_crc_invalid()) {
            set_slv_soft_version(0);
        } else if (if_new_crc_not_change()) {
            set_slv_soft_version(1);
        } else {
            set_slv_soft_version(2); 
        }
        return false;
    }
    return true;
}
