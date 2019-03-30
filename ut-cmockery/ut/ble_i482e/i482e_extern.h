#ifndef __I482E_EXTERN_H__
#define __I482E_EXTERN_H__

#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>

bool i482e_conn_ctrl_toggle(void);
bool i482e_conn_display(void);
bool i482e_conn_ctrl_high(void);
bool i482e_conn_ctrl_low(void);
void pull_i482e_high(void);
void pull_i482e_low(void);
void send_i482e_message(uint8_t *buf, uint32_t len);
int recv_i482e_message(uint8_t *buf, uint32_t len);
void i482e_delay(uint32_t ms);
uint32_t i482e_current_time(void);
uint32_t i482e_sec_tick(uint32_t sec);
uint32_t i482e_min_tick(uint32_t min);
void at_ack_pend(uint32_t wait_ms, uint32_t *err);
void at_ack_post(void);
bool is_at_cmd_timeout(uint32_t err);

#endif
