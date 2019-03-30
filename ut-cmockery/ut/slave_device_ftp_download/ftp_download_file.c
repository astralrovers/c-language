#include "ftp_debug.h"
#include "ftp_protocol.h"
#include "ftp_download_file.h"

extern int32_t create_ftp_tcp_connect(uint8_t *ip, uint32_t port,
                                      uint32_t send_time, uint32_t recv_time);
extern int32_t Str2Ip(uint8_t *ip, const uint8_t *str,
                      uint32_t start, uint32_t mid, uint32_t stop);
extern int32_t StrToDigit(const uint8_t *str, uint8_t c,
                          uint32_t n, uint32_t end, uint32_t *err);

enum e_ftp_cmd {
    e_ftp_control_start         = 1,
    e_ftp_control_continue      = 2,
    e_ftp_control_cancel        = 3,
    e_ftp_control_stop          = 4,
    e_ftp_too_many_user         = 11,
    e_ftp_update_timeout        = 20,
};

enum e_ftp_cmd_ack {
    e_ftp_retr_ack              = 150,
    e_ftp_type_i_ack            = 200,
    e_ftp_file_size_ack         = 213,
    e_ftp_server_ready_ack      = 220,
    e_ftp_pasv_ack              = 227,
    e_ftp_pass_ack              = 230,
    e_ftp_cwd_ack               = 250,
    e_ftp_user_ack              = 331,
    e_ftp_rest_ack              = 350,
};

static uint8_t update_rate;
static struct s_ftp *ftp = NULL;

bool slave_ftp_init(void)
{
    if (ftp) { return false; }
    ftp = (struct s_ftp *)malloc(sizeof(struct s_ftp));
    memset(ftp, 0, sizeof(struct s_ftp));
    return true;
}

void slave_ftp_exit(void)
{
    if (!ftp) { return; }
    free(ftp);
    ftp = NULL;
}

void slave_ftp_setup(struct download_ftp_file_addr *file_addr)
{
    if (!file_addr || !ftp) { return; }
    memcpy((uint8_t *)ftp, (uint8_t *)file_addr,
            sizeof(struct download_ftp_file_addr));
#ifndef UNIT_TESTING
    _ftpdebug(1, (FtpDbg), "[FTP]连接服务器%u.%u.%u.%u,%u\r\n",
                                  ftp->file_addr.ip[0],
                                  ftp->file_addr.ip[1],
                                  ftp->file_addr.ip[2],
                                  ftp->file_addr.ip[3],
                                  ftp->file_addr.port);
    _ftpdebug(1, (FtpDbg), "[FTP]下载文件名:%s\r\n",
                                  ftp->file_addr.local_file_path);
#endif
}

static struct s_ftp_control *ftp_ctl(void)
{
    return &(ftp->ftp_control);
}

static char *ftp_cmd(void)
{
    return get_ftp_cmd(ftp_ctl());
}

static int32_t get_ctl_sock(void)
{
    return *(get_ftp_cmd_sock(ftp_ctl()));
}

static bool set_ctl_sock(int32_t sock)
{
    *(get_ftp_cmd_sock(ftp_ctl())) = sock;
    return (sock == -1);
}

static void get_ftp_data_port(void)
{
    uint32_t err;
    ftp->dataPort = StrToDigit((uint8_t *)ftp_cmd(), ',', 4, ',', &err) * 256
        + StrToDigit((uint8_t *)ftp_cmd(), ',', 5, 0, &err);
}

static void get_ftp_data_ip(void)
{
    Str2Ip(ftp->dataIp, (uint8_t *)ftp_cmd(), '(', ',', ',');
}

bool create_ftp_contrl_link(void)
{
    if (set_ctl_sock(create_ftp_tcp_connect(
                    ftp->file_addr.ip, ftp->file_addr.port, 5, 5))) {
        _ftpdebug(1, ftp_link_error, "[FTP]连接服务器失败\r\n");
        return false;
    }
    _ftpdebug(1, 1, "[FTP]control link success sock = [%d]\n", get_ctl_sock());
    return true;
}

static bool create_ftp_data_sock(void)
{
    if ((ftp->dataSock = create_ftp_tcp_connect(ftp->dataIp, ftp->dataPort,
                                            5, e_ftp_update_timeout)) == -1) {
        _ftpdebug(1, (FtpDbg), "[FTP]连接数据服务器失败\r\n");
        set_ftp_result(ftp_ctl(), e_update_result_link_fail);
        return false;
    }
    return true;
}

bool create_ftp_data_link(void)
{
    _ftpdebug(1, (FtpDbg), "[FTP]data addr:%s\n", ftp_cmd());
    get_ftp_data_ip();
    get_ftp_data_port();
    return create_ftp_data_sock();
}

bool request_ftp_data_port(void)
{
    strcpy(ftp_cmd(), "TYPE I\r\n");
    if (!ftp_send(ftp_ctl()) ||
            !ftp_cmd_ack(ftp_ctl(), e_ftp_type_i_ack)) {
        return false;
    }
    strcpy(ftp_cmd(), "PASV\r\n");
    if (!ftp_send(ftp_ctl()) ||
            !ftp_cmd_ack(ftp_ctl(), e_ftp_pasv_ack)) {
        return false;
    }
    return true;
}

void close_ftp_data_link(void)
{
    close(ftp->dataSock);
    ftp->dataSock = -1;
}

void close_ftp_contrl_link(void)
{
    close(get_ctl_sock());	//关闭ftp 数据socket
    set_ctl_sock(-1);
}

static const uint8_t MAX_PROGRESS_BAR = 100;

static bool if_file_recv_over(uint32_t rate)
{
    return (rate == MAX_PROGRESS_BAR);
}

static void set_file_recv_over(void)
{
    update_rate = MAX_PROGRESS_BAR;
}

void set_file_recv_breakpoint(void)
{
    printf("file_size = [%d], reset_size = [%d], total_size = [%d]\n",
            ftp->fileSize, ftp->fileRest, ftp->fileTotal);
    if (ftp->fileRest >= ftp->fileTotal) {
        /* re-download */
        ftp->fileRest = 0;
        ftp->fileSize = 0;
    }
    if (!ftp->fileTotal) { return; }
    update_rate = ftp->fileRest * MAX_PROGRESS_BAR / ftp->fileTotal;
}

static bool update_download_progress_bar(int32_t len, uint32_t *rate)
{
    ftp->fileSize += len;
    *rate = ftp->fileSize * MAX_PROGRESS_BAR / ftp->fileTotal;
    if (*rate > update_rate) {
        _ftpdebug(0, (FtpDbg), "[FTP]升级进度%u%%\r\n", *rate);
        if (!if_file_recv_over(*rate)) {
            update_rate = *rate;
        } else {
            if (if_file_recv_over(*rate)) {
                update_rate = MAX_PROGRESS_BAR - 1;
            } else {
                set_ftp_result(ftp_ctl(), e_update_result_other_err);
            }
            return true;
        }
    }
    return false;
}

static FILE *open_ftp_file(void)
{
    FILE *file;
    if ((file = fopen(ftp->file_addr.local_file_path, "w+")) == NULL) {
        _ftpdebug(1, (FtpDbg), "[FTP]打开文件失败\r\n");
        set_ftp_result(ftp_ctl(), e_update_result_save_fail);
        return NULL;
    }
    return file;
}

static uint32_t write_ftp_file(FILE *file)
{
    int32_t len;
    uint32_t rate;
    for (rate = 0; ; ) {
        if (!ftp_recv(ftp->dataSock, ftp_ctl(), FTP_BUF_SIZE, &len)) {
            break;
        }
        if (len > 0) {
            fseek(file, ftp->fileSize, SEEK_SET);
            fwrite(ftp->ftp_control.cmd, 1, len, file);
            if (update_download_progress_bar(len, &rate)) {
                break;
            }
        }
    }
    return rate;
}

static void save_ftp_file(FILE *file, uint32_t rate)
{
    if (fclose(file) == -1) {
        _ftpdebug(1, (FtpDbg), "[FTP]关闭文件失败\r\n");
        set_ftp_result(ftp_ctl(), e_update_result_save_fail);
    } else if (truncate(ftp->file_addr.local_file_path, ftp->fileSize) == -1) {
        _ftpdebug(1, (FtpDbg), "[FTP]保存文件失败\r\n");
        set_ftp_result(ftp_ctl(), e_update_result_save_fail);
    } else if (if_file_recv_over(rate)) {
        set_file_recv_over();
    }
}

static void download_ftp_file(void)
{
    FILE *file;
    uint32_t rate;

    if (NULL == (file = open_ftp_file())) { return; }
    rate = write_ftp_file(file);
    save_ftp_file(file, rate);
}

bool request_ftp_login(void)
{
    if (!ftp_cmd_ack(ftp_ctl(), e_ftp_server_ready_ack)) { return false; }
    sprintf(ftp_cmd(), "USER %s\r\n", ftp->file_addr.user);
    if (!ftp_send(ftp_ctl()) ||
            !ftp_cmd_ack(ftp_ctl(), e_ftp_user_ack)) {
        return false;
    }
    sprintf(ftp_cmd(), "PASS %s\r\n", ftp->file_addr.passwd);
    if (!ftp_send(ftp_ctl()) ||
            !ftp_cmd_ack(ftp_ctl(), e_ftp_pass_ack)) {
        return false;
    }
    return true;
}

bool request_ftp_file_size(void)
{
    if(strlen(ftp->file_addr.remote_dir))
    {
        sprintf(ftp_cmd(), "CWD %s\r\n", ftp->file_addr.remote_dir);
        if (!ftp_send(ftp_ctl()) || !ftp_cmd_ack(ftp_ctl(), e_ftp_cwd_ack)) {
            return false;
        }
    }
    sprintf(ftp_cmd(), "REST %d\r\n", ftp->fileRest);
    if (!ftp_send(ftp_ctl()) || !ftp_cmd_ack(ftp_ctl(), e_ftp_rest_ack)) {
        return false;
    }
    sprintf(ftp_cmd(), "SIZE %s\r\n", ftp->file_addr.remote_file_name);
    if (!ftp_send(ftp_ctl()) || !ftp_cmd_ack(ftp_ctl(), e_ftp_file_size_ack)) {
        return false;
    }
    return true;
}

void request_ftp_file_data(void)
{
    sprintf(ftp_cmd(), "RETR %s\r\n", ftp->file_addr.remote_file_name);
    if (ftp_send(ftp_ctl()) && ftp_cmd_ack(ftp_ctl(), e_ftp_retr_ack)) {
        set_ftp_result(ftp_ctl(), e_update_result_ftp_on);
        download_ftp_file();
    }
}

bool if_download_file_size_over_max(void)
{
    uint32_t err;
    if ((ftp->fileTotal = StrToDigit((uint8_t *)ftp_cmd(), ' ', 1, 0, &err)) <= 0) {
        set_ftp_result(ftp_ctl(), e_update_result_crc_err);
        return true;
    }
    if (ftp->fileTotal > MAX_DOWNLOAD_FILE_SIZE) {
        _ftpdebug(1, (FtpDbg), "文件大小超过%d\r\n", MAX_DOWNLOAD_FILE_SIZE);
        set_ftp_result(ftp_ctl(), e_update_result_self_break);
        return true;
    }
    return false;
}

/***********************************************************/
void print_ftp_file_size(void)
{
    _ftpdebug(1, (FtpDbg),"ftp->fileSize=%d, ftp->fileTotal=%d\n",
                         ftp->fileSize,ftp->fileTotal);
}

bool if_file_size_correct(void)
{
    return (ftp->fileSize == ftp->fileTotal);
}

char *get_local_ftp_file_path(void)
{
    return ftp->file_addr.local_file_path;
}

void print_ftp_download_result(void)
{
    _ftpdebug(1, (FtpDbg), "[FTP]文件下载结果%d\r\n",
                get_ftp_result(ftp_ctl()));
}

int32_t download_result(void)
{
    return get_ftp_result(ftp_ctl());
}

bool if_too_many_ftp_users(void)
{
    if (download_result() == e_ftp_too_many_user) {
        _ftpdebug(1, (FtpDbg), "[FTP]接入的客户端太多,等待下次接入\r\n");
        return true;
    }
    return false;
}
