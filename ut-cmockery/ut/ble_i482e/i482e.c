#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "i482e.h"
#include "i482e_extern.h"

static struct i482e_base_para _i482e_base_para;
static char _beacon[MAX_BEACON_LEN];
static bool at_init_state = false;
static bool at_over_time = false;
static bool i482e_module_change = false;
static bool i482e_current_status = true;

static void set_i482e_current_status_alarm(void);
static bool if_replaced_i482e_module(uint8_t *i482e_name, uint8_t new_name_len);
static void save_i482e_pin(uint8_t *i482e_pin);
static void save_i482e_name(const uint8_t *name);

void reset_i482e_phy(void)
{
    pull_i482e_high();
    pull_i482e_low();
}

void open_i482e_phy(void)
{
    pull_i482e_low();
}

static void close_i482e_phy(void)
{
    pull_i482e_high();
}

void close_i482e(void)
{
    set_i482e_current_status_alarm();
    close_i482e_phy();
}

static void set_at_over_time(void)
{
    at_over_time = true;
}

static void reset_at_over_time(void)
{
    at_over_time = false;
}

static bool is_at_over_time(void)
{
    return at_over_time;
}

bool is_i482e_module_changed(void)
{
    return i482e_module_change;
}

static void set_i482e_module_changed(void)
{
    i482e_module_change = true;
}

static void clear_i482e_module_changed(void)
{
    i482e_module_change = false;
}

bool i482e_current_alarm_status(void)
{
    return i482e_current_status;
}

static void set_i482e_current_status_alarm(void)
{
    i482e_current_status = false;
}

static void clear_i482e_current_status_alarm(void)
{
    i482e_current_status = true;
}

static bool uart_write_at_cmd(uint8_t cmd_type, const char *at_cmd)
{
    uint8_t len = strlen(at_cmd);
    switch (cmd_type) {
        case NAME_SET:
            send_i482e_message((uint8_t*)("AT+NAME="),strlen("AT+NAME="));
            send_i482e_message((uint8_t*)at_cmd,len);
            break;
        case NAME_GET:
            send_i482e_message((uint8_t*)("AT+NAME?"),strlen("AT+NAME?"));
            break;
        case GVER_GET:
            send_i482e_message((uint8_t*)("AT+GVER"),strlen("AT+GVER"));
            break;
        case PIN_SET:
            send_i482e_message((uint8_t*)("AT+PIN="),strlen("AT+PIN="));
            send_i482e_message((uint8_t*)at_cmd,len);
            break;
        case PIN_GET:
            send_i482e_message((uint8_t*)("AT+PIN?"),strlen("AT+PIN?"));
            break;
        case KEY_CLR:
            send_i482e_message((uint8_t*)("AT+CLEARLINKKEY"),strlen("AT+CLEARLINKKEY"));
            break;
        case IBEACON_SET:
            send_i482e_message((uint8_t*)("AT+BEACON="),strlen("AT+BEACON="));
            send_i482e_message((uint8_t*)at_cmd,len);
            break;
        case TXPOWER_SET:
            send_i482e_message((uint8_t*)("AT+TXPOWER="),strlen("AT+TXPOWER="));
            send_i482e_message((uint8_t*)at_cmd,len);
            break;
        case TXPOWER_GET:
            send_i482e_message((uint8_t*)("AT+TXPOWER?"),strlen("AT+TXPOWER?"));
            break;
        case REST_FACTYR:
            send_i482e_message((uint8_t*)("AT+FACTORYRESET"),strlen("AT+FACTORYRESET"));
            break;
        default:
            printf("no such at cmd\r\n");
            return false;
    }
    return true;
}

static bool is_i482e_not_initializing(void)
{
    return is_i482e_init_success();
}

static bool wait_i482e_init_at_cmd_back(void)
{
    uint32_t err = 0;
    at_ack_pend(1000, &err);
    return is_at_cmd_timeout(err) ? false : true;
}

static void at_cmd_send_success(void)
{
    printf("at cmd ack succsess\r\n");
    clear_i482e_current_status_alarm();
    reset_at_over_time();
}

static void at_cmd_send_failed(void)
{
    printf("at cmd timeout, re-send\r\n");
}

#define AT_RESEND_TIMES 9
static void if_need_reset_i482e(uint8_t send_times)
{
    if (send_times % AT_RESEND_TIMES) { return ; }
    printf("at cmd timeout of 3 times, reset i482e\r\n");
    set_i482e_current_status_alarm();
    set_at_over_time();
    reset_i482e_phy();
}

static bool i482e_at_cmd_send(uint8_t cmd_type, const char *at_cmd)
{
    uint8_t re_send_times = 1;
    for (; re_send_times <= AT_RESEND_TIMES; re_send_times++) {
        if (!uart_write_at_cmd(cmd_type, at_cmd)) { return false; }
        if (is_i482e_not_initializing()) { return true; }
        if (wait_i482e_init_at_cmd_back()) {
            at_cmd_send_success();
            return true;
        } else {
            at_cmd_send_failed();
        }
        if_need_reset_i482e(re_send_times);
    }
    printf("i482e not installed or damaged!\r\n");
    return false;
}

bool is_i482e_connected(void)
{
    return i482e_conn_display() ? true : false;
}

static void disconnect_i482e(void)
{
    i482e_conn_ctrl_toggle();
}

bool is_i482e_init_success(void)
{
    return at_init_state;
}

void set_i482e_init_success(void)
{
    at_init_state = true;
}

static bool if_can_disconnect_i482e(void)
{
    printf("i482e is connected, nedd discinnect\r\n");
    uint8_t num= 10;
    while (num) {
        disconnect_i482e();
        i482e_delay((2000));
        if (!is_i482e_connected()) {
            printf("disconnected\r\n");
            return true;
        }
        num--;
    }
    printf("i482e can not disconnect, reset i482e phy\r\n");
    set_i482e_current_status_alarm();
    reset_i482e_phy();
    return false;
}

/* 
 * 查找字符c出现的次数，并返回首次出现的位置
 * */
void *strnc(char *str, char c, uint32_t len, uint8_t *ch)
{
    char *p = str;
    char *addr = NULL;
    uint8_t i;
    uint8_t j = 0;
    *ch = 0;
    for (i = 0; i < len; i++) {
        if (*p++ == c) {
            *ch += 1;
            if (j == 0) {
                j++;
                addr = p-1;
            }
        }
    }
    if (*ch == 0) { return NULL; }
    return addr;
}

static bool if_at_response_ok(const char *str)
{
    if (!strncmp(AT_RESPONSE_OK, str, strlen(AT_RESPONSE_OK))) {
        printf("response ok\r\n");
        clear_i482e_current_status_alarm();
        if (!is_i482e_init_success()) {
            at_ack_post();
        }
        return true;
    }
    return false;
}

static bool if_at_im_ready(const char *str)
{
    if (!strncmp(AT_IM_READY, (const char*)str, strlen(AT_IM_READY))) {
        printf("i482e disconnected or reseted\r\n");
        clear_i482e_current_status_alarm();
        return true;
    }
    return false;
}

static bool if_at_im_spp(const char *str)
{
    if (!strncmp(AT_IM_SPP, (const char*)str, strlen(AT_IM_SPP))) {
        printf("i482e is connected\r\n");
        return true;
    }
    return false;
}

uint8_t *str_chr_num(const uint8_t *str, uint8_t c, uint32_t n)
{
	if (n && c && str) {
		for ( ; *str; str++) {
			if (*str == c) {
				if (--n == 0) {
					return (uint8_t *)str;
				}
			}
		}
	}
	return NULL;
}

static bool if_at_get_cmd_complete(const char *str)
{
    if (str_chr_num((const uint8_t*)str, '\n', 4) && strstr(str, "\r\n")) {
        printf("get cmd\r\n");
        return true;
    }
    return false;
}

static bool if_at_get_cmd_not_complete(const char *str)
{
    if (str_chr_num((const uint8_t*)str, '\n', 3)) {
        return true;
    }
    return false;
}

static bool if_at_power_start_cmd(const char *str)
{
    if (strncmp(AT_POWER_START, str, strlen(AT_POWER_START)) == 0) {
        printf("start cmd\r\n");
        return true;
    }
    return false;
}

static void unpack_i482e_name(uint8_t * cmd_start, uint8_t *cmd_end)
{
    uint8_t len_name;
    uint8_t i482e_name[I482E_NAME_LEN];
    len_name = (uint8_t)((size_t)cmd_end - (size_t)cmd_start + 1 - strlen(AT_GET_NAME));
    len_name = (sizeof(i482e_name) > len_name) ? len_name : sizeof(i482e_name);
    memset(i482e_name,0,sizeof(i482e_name));
    memcpy(i482e_name, cmd_start+strlen(AT_GET_NAME), len_name);
    printf("get i482e-name is :%s\r\n", i482e_name);
    /* 
     * 轮询设备名时，若设备名更改，说明换了蓝牙模块，
     * 需要重新初始化，第一次上电初始化时，不进行设备名对比
     * */
    if (is_i482e_init_success()) {
        if (if_replaced_i482e_module(i482e_name, len_name)) {
            set_i482e_current_status_alarm();
            set_i482e_module_changed();
            save_i482e_name(i482e_name);
        } else {
            clear_i482e_current_status_alarm();
            reset_at_over_time();
        }
    } else {
        at_ack_post();
    }
}

static void unpack_i482e_pin(uint8_t * cmd_start, uint8_t *cmd_end)
{
    uint8_t len_pin;
    uint8_t pin[I482E_PIN_LEN] = {'\0'};
    memset(pin, 0, sizeof(pin));
    len_pin = (uint8_t)((size_t)cmd_end - (size_t)cmd_start + 1 - strlen(AT_GET_PIN));
    len_pin = (sizeof(pin) > len_pin) ? len_pin : sizeof(pin);
    memcpy(pin, cmd_start+strlen(AT_GET_PIN), len_pin);
    printf("ge i482e pin is %s\r\n", pin);
    save_i482e_pin(pin);
    at_ack_post();
}

static bool if_at_get_i482e_name(uint8_t * cmd_start)
{
    if (memcmp(cmd_start, AT_GET_NAME, strlen(AT_GET_NAME))) { return false; }
    return true;
}

static bool if_at_get_i482e_pin(uint8_t * cmd_start)
{
    if (memcmp(cmd_start, AT_GET_PIN, strlen(AT_GET_PIN))) { return false; }
    return true;
}

static void if_get_cmd_currect(char *str)
{
    uint8_t *cmd_start;
    uint8_t *cmd_end;

    cmd_start = (uint8_t*)(str+2);
    cmd_end = str_chr_num((const uint8_t *)str, AT_CMD_KEYWORD, 2) - 1;

    if (if_at_get_i482e_name(cmd_start)) {
        unpack_i482e_name(cmd_start, cmd_end);
    } else if (if_at_get_i482e_pin(cmd_start)) {
        unpack_i482e_pin(cmd_start, cmd_end);
    }
}

static uint8_t *get_at_key_word_num(struct st_unpacket *unpack, uint8_t *num)
{
    return strnc((char*)unpack->data, AT_CMD_KEYWORD, unpack->len, num);
}

static bool i482e_at_cmd_unpack(struct st_unpacket *unpack)
{
    uint8_t *start;
    uint8_t at_keyword_num = 0;
    start = unpack->data;
    if (!(start = get_at_key_word_num(unpack, &at_keyword_num))) {
        printf("%s, can not unpack at\n", __func__);
        return false;
    } else {
        switch (at_keyword_num) {
            case AT_NOT_COMPLETE_1 :
            case AT_NOT_COMPLETE_3 :
                break;
            case AT_SET_CMD :
                printf("at cmd maybe set\r\n");
                if (if_at_response_ok((const char*)start)) {
                    return true;
                } else if(if_at_im_ready((const char*)start)) {
                    return true;
                } else if (if_at_im_spp((const char*)start)) {
                    return true;
                } else {
                    break;
                }
            case AT_GET_CMD :
                printf("at cmd maybe get\r\n");
                if (if_at_get_cmd_complete((const char*)start)) {
                    if (!if_at_power_start_cmd((const char*)start)) {
                        if_get_cmd_currect((char *)start);
                    }
                } else if(if_at_get_cmd_not_complete((const char*)start)) {
                    break;
                }
                return true;
            default:
                return true;
        }
        printf("接收%d个r，继续接收\r\n", at_keyword_num);
        return false;
    }
}

static void recv_at_message(void)
{
#ifdef UNIT_TESTING
    int32_t at_message_total_len = 0;
    extern uint8_t at_buf[];
    uint8_t max_at_len = AT_BUF_LEN;
#else
    static int32_t at_message_total_len = 0;
    uint8_t at_buf[AT_BUF_LEN];
    uint8_t max_at_len = sizeof(at_buf);
#endif
    int32_t get_len = 0; 
    uint8_t *at_ptr;
    int32_t at_len;
    struct st_unpacket atpack;
    at_ptr = at_buf;
    for (;;) {
#ifdef UNIT_TESTING
        get_len = AT_BUF_LEN;
#else
        get_len = sizeof(at_buf) - (at_ptr - at_buf);
#endif
        if ((at_len = (recv_i482e_message(at_ptr, get_len))) == -1) {
            i482e_delay(i482e_sec_tick(1));
            printf("recv at cmd error\n");
            break;
        }
        if (!at_len) { break; }
        at_len += at_ptr - at_buf;
        atpack.data = at_buf;
        atpack.len = at_len;
        at_message_total_len = atpack.len;
        if (at_message_total_len >= max_at_len) {
            at_message_total_len = 0;
            break;
        }
        if (i482e_at_cmd_unpack(&atpack)) { break; }
        at_ptr = at_buf + atpack.len;
    }
}

void poll_i482e_at_response(void)
{
    recv_at_message();
}

bool reset_i482e_default_base_parameter(void)
{
    bool err = false;
    i482e_delay((500));
    printf("set i482e name*******\r\n\r\n");
    err = i482e_at_cmd_send(NAME_SET, (const char*)_i482e_base_para.NAME);
    i482e_delay((500));

    if (err) {
        printf("set i482e pin************\r\n\r\n");
        err = i482e_at_cmd_send(PIN_SET, (const char*)_i482e_base_para.PIN);
        i482e_delay((500));
    } else {
        printf("set i482e name failed\r\n");
        return false;
    }
    if (err) {
        printf("get i482e pin***********\r\n\r\n");
        err = i482e_at_cmd_send(PIN_GET, NONE);
        i482e_delay((500));
    } else {
        printf("set i482e pin failed\r\n");
        return false;
    }
    if (err) {
        printf("get i482e name*********\r\n\r\n");
        err = i482e_at_cmd_send(NAME_GET, NONE);
        i482e_delay((500));
    } else {
        printf("get i482e pin failed\r\n");
        return false;
    }
    if (!err) {
        printf("get i482e name failed\r\n");
        return false;
    }
    return true;
}

void reset_beacon_parameter(void)
{
    bool err = false;
    printf("set beacon info*********\r\n\r\n");
    err = i482e_at_cmd_send(IBEACON_SET, _beacon);
    i482e_delay((500));
    if (!err) {
        printf("set beacon info failed\r\n");
    }
}

static void save_i482e_name(const uint8_t *name)
{
    memcpy(_i482e_base_para.NAME, name, strlen((const char*)name));
}

static void send_at_name_cmd(void)
{
    i482e_at_cmd_send(NAME_SET, (const char*)_i482e_base_para.NAME);
}

void update_i482e_name(const uint8_t *name)
{
    save_i482e_name(name);
    send_at_name_cmd();
}

static bool if_replaced_i482e_module(uint8_t *i482e_name, uint8_t new_name_len)
{
    uint8_t old_name_len;
    old_name_len = strlen((const char*)_i482e_base_para.NAME);
    old_name_len = (new_name_len < old_name_len) ? old_name_len : new_name_len;
    if (memcmp(i482e_name, (const char*)_i482e_base_para.NAME, old_name_len)) {
        printf("new name = [%s], old name=[%s]\n", i482e_name, _i482e_base_para.NAME);
        return true;
    }
    return false;
}

void update_i482e_phy_status(void)
{
    static uint32_t atpolltime = 0; //蓝牙发送查询命令时间
    static uint8_t atpollflag = 0; //蓝牙发送查询命令标志
    static uint32_t atrectime = 0; //蓝牙返回命令记录时间
    static uint32_t atchktime = 0; //蓝牙返回命令查询时间
    printf("OSTimeGet,atpolltime is %d,%d\r\n", i482e_current_time(), atpolltime);
    if (atpollflag) {
        atchktime = i482e_current_time();
        if (atchktime - atrectime < i482e_sec_tick(10)) {
            if (!is_at_over_time()) {
                atrectime = atchktime;
                clear_i482e_current_status_alarm();
                atpollflag = 0;
            }
        } else {
            atrectime = atchktime;
            set_i482e_current_status_alarm();
            atpollflag = 0;
            printf("bluetooth is outline\r\n");
            reset_i482e_phy();//复位重启，解决可能出现的死机问题
        }
    }
    if (i482e_current_time() - atpolltime > i482e_min_tick(3)) //3分钟发送一次设备名查询命令解决模块死机问题和热插拔问题
    {
        printf("check hot swap***********\r\n\r\n");
        i482e_at_cmd_send(NAME_GET, NONE);
        atpollflag = 1; //已发送查询命令
        set_at_over_time();
        atpolltime = i482e_current_time();//轮回时间
        atrectime = i482e_current_time();//记录该命令发送时间
        atchktime = atrectime;//返回命令查询时间
    }
}

static void save_i482e_pin(uint8_t *i482e_pin)
{
    memcpy(_i482e_base_para.PIN, i482e_pin, sizeof(_i482e_base_para.PIN));
}

void i482e_beacon_parameter_setup(const char *beacon)
{
    memcpy(_beacon, beacon, sizeof(_beacon));
}

void i482e_base_parameter_setup(struct i482e_base_para *base_para)
{
    memcpy(&_i482e_base_para, base_para, sizeof(struct i482e_base_para));
}

void reset_i482e_soft(void)
{
    clear_i482e_module_changed();
    if (reset_i482e_default_base_parameter()) {
        set_i482e_init_success();
        printf("set_i482e_init_success\r\n");
    }
}

void i482e_init(void)
{
    if (!is_i482e_connected() || if_can_disconnect_i482e()) {
        reset_i482e_soft();
    }
}
