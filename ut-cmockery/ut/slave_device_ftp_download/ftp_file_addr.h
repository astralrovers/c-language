#ifndef __FTP_ADDR_H__
#define __FTP_ADDR_H__
#include <inttypes.h>

struct download_ftp_file_addr {
    uint8_t ip[4];
    uint16_t port;
    char user[21];
    char passwd[21];
    char remote_dir[41];
    char remote_file_name[141];
    char local_file_path[181];
};

#endif  // __FTP_ADDR_H__
