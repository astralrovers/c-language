#include "i482e_extern.h"

extern void ble_ack_pend(uint32_t wait_ms, uint32_t *err);
extern void ble_ack_post(void);
extern bool is_ble_cmd_timeout(uint32_t err);
extern int uart_read(uint8_t *ptr, uint16_t len);
extern void uart_write(uint8_t *buf, uint16_t len);
extern void ble_delay_ms(uint32_t ms);
extern uint32_t ble_current_time(void);
extern uint32_t ble_sec_tick(uint32_t sec);
extern void pull_ble_high(void);
extern void pull_ble_low(void);
extern bool ble_conn_ctrl_toggle(void);
extern bool ble_conn_display(void);
extern bool ble_conn_ctrl_high(void);
extern bool ble_conn_ctrl_low(void);

void at_ack_pend(uint32_t wait_ms, uint32_t *err)
{
    ble_ack_pend(wait_ms, err);
}

void at_ack_post(void)
{
    ble_ack_post();
}

bool is_at_cmd_timeout(uint32_t err)
{
    return is_ble_cmd_timeout(err);
}

bool i482e_conn_ctrl_toggle(void)
{
    return ble_conn_ctrl_toggle();
}

bool i482e_conn_display(void)
{
    return ble_conn_display();
}

bool i482e_conn_ctrl_high(void)
{
    return ble_conn_ctrl_high();
}

bool i482e_conn_ctrl_low(void)
{
    return ble_conn_ctrl_low();
}

void pull_i482e_high(void)
{
    pull_ble_high();
}

void pull_i482e_low(void)
{
    pull_ble_low();
}

void send_i482e_message(uint8_t *buf, uint32_t len)
{
    uart_write(buf, len);
}

int recv_i482e_message(uint8_t *buf, uint32_t len)
{
    return uart_read(buf, len);
}

void i482e_delay(uint32_t ms)
{
    ble_delay_ms(ms);
}

uint32_t i482e_current_time(void)
{
    return ble_current_time();
}

uint32_t i482e_sec_tick(uint32_t sec)
{
    return ble_sec_tick(sec);
}

uint32_t i482e_min_tick(uint32_t min)
{
    return 60*ble_sec_tick(min);
}
