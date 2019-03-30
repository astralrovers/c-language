#include "ftp_debug.h"
#include "ftp_protocol.h"

enum e_ftp_protocl {
    e_no_login          = 530,
    e_no_such_file      = 550,
    e_cmd_error         = 451,
    e_too_many_users    = 421,
};

void set_ftp_result(struct s_ftp_control *ftp, uint8_t result)
{
    ftp->result = result;
}

uint8_t get_ftp_result(struct s_ftp_control *ftp)
{
    return ftp->result;
}

char *get_ftp_cmd(struct s_ftp_control *ftp)
{
    return ftp->cmd;
}

int32_t *get_ftp_cmd_sock(struct s_ftp_control *ftp)
{
    return &(ftp->cmdSock);
}

bool ftp_send(struct s_ftp_control *ftp)
{
    _ftpdebug(1, DBG_SW(FtpDbg), "[FTP]发送:%s", ftp->cmd);
    if (send(ftp->cmdSock, ftp->cmd,
                strlen((char *)ftp->cmd), 0) < 0) {
        set_ftp_result(ftp, e_update_result_timeout);
        _ut_ftpdbg(e_update_result_timeout);
        return false;
    }
    return true;
}

bool ftp_recv(int32_t sock, struct s_ftp_control *ftp, int size, int32_t *len)
{
    if ((*len = recv(sock, ftp->cmd, size, 0)) == -1) {
        if (errno == EAGAIN) {
            set_ftp_result(ftp, e_update_result_timeout);
            _ftpdebug(1, e_update_result_timeout, "[FTP]远程通信超时\r\n");
        } else {
            set_ftp_result(ftp, e_update_result_link_fail);
            _ftpdebug(1, e_update_result_link_fail,
                        "[FTP]recv:%s\r\n", strerror(errno));
        }
        return false;
    } else if (*len == 0) {
        _ftpdebug(1, e_update_result_other_err,
                    "[FTP]FTP服务器断开TCP 连接\r\n");
        set_ftp_result(ftp, e_update_result_other_err);
        return false;
    }
    return true;
}

static bool get_ftp_ack(struct s_ftp_control *ftp, int32_t *ack)
{
    switch ((*ack = atol((char *)ftp->cmd))) {
        case e_no_login:
            set_ftp_result(ftp, e_update_result_ftp_login_fail);
            _ut_ftpdbg(e_update_result_ftp_login_fail);
            break;
        case e_no_such_file:
            set_ftp_result(ftp, e_update_result_crc_err);
            _ut_ftpdbg(e_update_result_crc_err);
            break;
        case e_cmd_error:
            set_ftp_result(ftp, e_update_result_other_err);
            _ut_ftpdbg(e_update_result_other_err);
            break;
        case e_too_many_users:
            set_ftp_result(ftp, e_update_too_many_user);
            _ut_ftpdbg(e_update_too_many_user);
            return false;
        default:
            break;
    }
    return true;
}

static bool if_ack_endmark_error(struct s_ftp_control *ftp, int32_t len)
{
    if ((*(ftp->cmd + len - 2) == '\r') &&
            (*(ftp->cmd + len - 1) == '\n')) {
        return false;
    }
    return true;
}

bool ftp_cmd_ack(struct s_ftp_control *ftp, int32_t ok)
{
    int32_t len;
    int32_t ack = -1;
    for ( ; ack != ok; ) {
        ack = -1;
        if (!ftp_recv(ftp->cmdSock, ftp, FTP_BUF_SIZE - 1, &len)) {
            return false;
        }
        *(ftp->cmd + len) = 0;  // add '\0' to end
        if (len < 2) { continue; }
        _ftpdebug(1, recv, "[FTP]接收:%s", ftp->cmd);
        if (if_ack_endmark_error(ftp, len)) { continue; }
        if (!get_ftp_ack(ftp, &ack)) { return false; }
    }
    return true;
}
