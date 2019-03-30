#ifndef __FTP_DOWNLOAD_FILE_H__
#define __FTP_DOWNLOAD_FILE_H__
#include <inttypes.h>
#include <stdio.h>
#include <stdbool.h>
#include "ftp_file_addr.h"
#include "ftp_protocol.h"

struct s_ftp{
    struct download_ftp_file_addr file_addr;
    struct s_ftp_control ftp_control;
    uint8_t dataIp[4];          // FTP数据IP
    uint16_t dataPort;          // FTP数据端口
    int32_t dataSock;           // FTP数据socket
    int32_t fileRest;           // 文件断点
    int32_t fileSize;           // 已下载文件的大小
    int32_t fileTotal;          // 下载文件的总大小
};

bool slave_ftp_init(void);
void slave_ftp_exit(void);
void slave_ftp_setup(struct download_ftp_file_addr *file_addr);

bool request_ftp_login(void);
bool request_ftp_file_size(void);
bool if_download_file_size_over_max(void);
void set_file_recv_breakpoint(void);
bool request_ftp_data_port(void);
bool create_ftp_data_link(void);
void request_ftp_file_data(void);
void close_ftp_data_link(void);
void close_ftp_contrl_link(void);
bool create_ftp_contrl_link(void);

void print_ftp_file_size(void);
bool if_file_size_correct(void);
char *get_local_ftp_file_path(void);
int32_t download_result(void);
void print_ftp_download_result(void);
bool if_too_many_ftp_users(void);

#endif
