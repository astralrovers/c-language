#ifndef __FTP_PROTOCOL_H__
#define __FTP_PROTOCOL_H__
#include <inttypes.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>

#include "ftp_config.h"

enum e_update_cmd {
    e_update_result_ok				= 0,
    e_update_result_self_break		= 1,
    e_update_result_omc_cancel		= 2,
    e_update_result_crc_err			= 3,
    e_update_result_save_fail		= 4,
    e_update_result_link_fail		= 5,
    e_update_result_timeout			= 6,
    e_update_result_ftp_timeout		= 7,
    e_update_result_ftp_login_fail	= 8,
    e_update_result_ftp_on			= 9,
    e_update_too_many_user          = 11,
    e_update_result_other_err		= 17,
};

struct s_ftp_control {
    int32_t cmdSock;			// FTP命令socket
    char cmd[FTP_BUF_SIZE];
    uint8_t result;             // 升级结果
};

bool ftp_send(struct s_ftp_control *ftp);
bool ftp_recv(int32_t sock, struct s_ftp_control *ftp, int size, int32_t *len);
bool ftp_cmd_ack(struct s_ftp_control *ftp, int32_t ok);
char *get_ftp_cmd(struct s_ftp_control *ftp);
int32_t *get_ftp_cmd_sock(struct s_ftp_control *ftp);
uint8_t get_ftp_result(struct s_ftp_control *ftp);
void set_ftp_result(struct s_ftp_control *ftp, uint8_t result);

#endif  // FTP_PROTOCOL_H_
