#ifndef __I482E_H
#define __I482E_H
#include <inttypes.h>
#include <stdbool.h>

enum {
    NAME_SET = 0,
    NAME_GET,    
    GVER_GET,	 
    PIN_SET,     
    PIN_GET,     
    KEY_CLR,     
    IBEACON_SET, 
    TXPOWER_SET, 
    TXPOWER_GET, 
    REST_FACTYR  
};

#define AT_BUF_LEN 100
#define I482E_NAME_LEN 32
#define I482E_PIN_LEN 10
#define UUID_LEN    32
#define MAX_BEACON_LEN  50

enum {
    AT_NOT_COMPLETE_1 = 1,
    AT_SET_CMD,
    AT_NOT_COMPLETE_3,
    AT_GET_CMD,
};

#define AT_CMD_KEYWORD  '\r'
#define AT_RESPONSE_OK  "\r\nOK\r\n"
#define AT_IM_READY     "\r\nIM_READY\r\n"
#define AT_IM_SPP     "\r\nIM_SPP\r\n"
#define AT_POWER_START "\r\nIM_READY\r\n\r\nERROR\r\n"

#define AT_GET_NAME "+NAME:"
#define AT_GET_PIN  "+PIN:"
struct _IBEACON {
    uint32_t major;
    uint32_t minor;
    int tx_power;
    uint8_t uuid[UUID_LEN];
};

struct i482e_base_para {
    uint8_t NAME[I482E_NAME_LEN];
    uint8_t PIN[I482E_PIN_LEN];
    uint32_t tx_power;
};

struct i482e_cache_para {
    struct i482e_base_para inuse;
    uint8_t device_serial_number[21];
    uint8_t location[21];
};

struct st_unpacket {
	uint32_t len;
	uint8_t *data;
};

#define NONE "0"
void send_i482e_message(uint8_t *buf, uint32_t len);
int recv_i482e_message(uint8_t *buf, uint32_t len);

void i482e_init(void);
void i482e_base_parameter_setup(struct i482e_base_para *base_para);
void i482e_beacon_parameter_setup(const char *beacon);
void reset_i482e_soft(void);
void reset_beacon_parameter(void);

void update_i482e_name(const uint8_t *name);
void poll_i482e_at_response(void);
void update_i482e_phy_status(void);

void reset_i482e_phy(void);
void open_i482e_phy(void);
void close_i482e(void);

bool is_i482e_connected(void);
bool is_i482e_init_success(void);
bool is_i482e_module_changed(void);
bool i482e_current_alarm_status(void);

#endif
