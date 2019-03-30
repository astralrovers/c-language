#ifdef UNIT_TESTING

#include <stdarg.h>
#include <stdio.h>
#include <stddef.h>
#include <setjmp.h>
#include <string.h>
#include <inttypes.h>
#include <google/cmockery.h>
#include "i482e_extern.h"
#include "i482e.h"

static struct i482e_cache_para _i482e_cache_para;
static char beacon_string[MAX_BEACON_LEN];

void ble_ack_pend(uint32_t wait_ms, uint32_t *err)
{
    check_expected(wait_ms);
    //check_expected(err);
}

void ble_ack_post(void){ }

bool is_ble_cmd_timeout(uint32_t err)
{
    check_expected(err);
    return (bool)mock();
}

int uart_read(uint8_t *ptr, uint16_t len)
{
    check_expected(ptr);
    check_expected(len);
    return (int)mock();
}

void uart_write(uint8_t *buf, uint16_t len)
{
    check_expected(buf);
    check_expected(len);
}

void ble_delay_ms(uint32_t ms)
{
    check_expected(ms);
}

uint32_t ble_current_time(void)
{
    return (uint32_t)mock();
}

uint32_t ble_sec_tick(uint32_t sec)
{
    check_expected(sec);
    return (uint32_t)mock();
}

void pull_ble_high(void){ }

void pull_ble_low(void){ }

bool ble_conn_ctrl_toggle(void)
{
    return (bool)mock();
}

bool ble_conn_display(void)
{
    return (bool)mock();
}

bool ble_conn_ctrl_high(void)
{
    return (bool)mock();
}

bool ble_conn_ctrl_low(void)
{
    return (bool)mock();
}

static void test_setup(void** state)
{
    sprintf((char *)_i482e_cache_para.inuse.NAME, "n2ru-st");
    sprintf((char *)_i482e_cache_para.inuse.PIN, "test");
    sprintf((char *)beacon_string, "%d,%d,%d,%s",
                            10, 20, -59,
                            "FDA50693A4E24FB1AFCFC6EB07647825");
    i482e_base_parameter_setup(&_i482e_cache_para.inuse);
    i482e_beacon_parameter_setup(beacon_string);
}

static void send_i482e_message_test(void** state)
{
    expect_string(uart_write, buf, "test");
    expect_value(uart_write, len, strlen("test"));
    send_i482e_message((uint8_t *)"test", strlen("test"));
}

static void recv_i482e_message_test(void** state)
{
    expect_string(uart_read, ptr, "test");
    expect_value(uart_read, len, strlen("test"));
    will_return(uart_read, strlen("test"));
    assert_int_equal(recv_i482e_message((uint8_t *)"test", strlen("test")), strlen("test"));
}

static void reset_soft_normal_need(void)
{
    uint32_t err = 0;
    expect_value(ble_delay_ms, ms, 500);

    expect_string(uart_write, buf, "AT+NAME=");
    expect_value(uart_write, len, strlen("AT+NAME="));
    expect_string(uart_write, buf, _i482e_cache_para.inuse.NAME);
    expect_value(uart_write, len, strlen((const char *)_i482e_cache_para.inuse.NAME));
    expect_value(ble_ack_pend, wait_ms, 1000);
    //expect_value(ble_ack_pend, err, &err);
    expect_value(is_ble_cmd_timeout, err, err);
    will_return(is_ble_cmd_timeout, false);
    expect_value(ble_delay_ms, ms, 500);

    expect_string(uart_write, buf, "AT+PIN=");
    expect_value(uart_write, len, strlen("AT+PIN="));
    expect_string(uart_write, buf, _i482e_cache_para.inuse.PIN);
    expect_value(uart_write, len, strlen((const char *)_i482e_cache_para.inuse.PIN));
    expect_value(ble_ack_pend, wait_ms, 1000);
    //expect_value(ble_ack_pend, err, &err);
    expect_value(is_ble_cmd_timeout, err, err);
    will_return(is_ble_cmd_timeout, false);
    expect_value(ble_delay_ms, ms, 500);

    expect_string(uart_write, buf, "AT+PIN?");
    expect_value(uart_write, len, strlen("AT+PIN?"));
    //expect_string(uart_write, buf, NONE);
    //expect_value(uart_write, len, strlen(NONE));
    expect_value(ble_ack_pend, wait_ms, 1000);
    //expect_value(ble_ack_pend, err, &err);
    expect_value(is_ble_cmd_timeout, err, err);
    will_return(is_ble_cmd_timeout, false);
    expect_value(ble_delay_ms, ms, 500);

    expect_string(uart_write, buf, "AT+NAME?");
    expect_value(uart_write, len, strlen("AT+NAME?"));
    //expect_string(uart_write, buf, NONE);
    //expect_value(uart_write, len, strlen(NONE));
    expect_value(ble_ack_pend, wait_ms, 1000);
    //expect_value(ble_ack_pend, err, &err);
    expect_value(is_ble_cmd_timeout, err, err);
    will_return(is_ble_cmd_timeout, false);
    expect_value(ble_delay_ms, ms, 500);
}

static void reset_i482e_soft_test(void** state)
{
    reset_soft_normal_need();
    reset_i482e_soft();
    assert_true(is_i482e_init_success());
}

static void reset_beacon_parameter_test(void** state)
{
    //reset_soft_normal_need();
    //reset_i482e_soft();
    //assert_true(is_i482e_init_success());

    expect_string(uart_write, buf, "AT+BEACON=");
    expect_value(uart_write, len, strlen("AT+BEACON="));
    expect_string(uart_write, buf, beacon_string);
    expect_value(uart_write, len, strlen((const char*)beacon_string));
    expect_value(ble_delay_ms, ms, 500);
    reset_beacon_parameter();
}

static void update_i482e_name_test(void** state)
{
    //reset_soft_normal_need();
    //reset_i482e_soft();
    //assert_true(is_i482e_init_success());

    expect_string(uart_write, buf, "AT+NAME=");
    expect_value(uart_write, len, strlen("AT+NAME="));
    expect_string(uart_write, buf, "n2ru-new-name");
    expect_value(uart_write, len, strlen("n2ru-new-name"));
    update_i482e_name((const uint8_t*)"n2ru-new-name");
}

uint8_t at_buf[AT_BUF_LEN];
static void poll_i482e_at_response_test(void** state)
{
    // recv error
    expect_string(uart_read, ptr, at_buf);
    expect_value(uart_read, len, AT_BUF_LEN);
    will_return(uart_read, -1);
    expect_value(ble_sec_tick, sec, 1);
    will_return(ble_sec_tick, 1000);
    expect_value(ble_delay_ms, ms, 1000);
    poll_i482e_at_response();

    // recv ok
    sprintf((char *)at_buf, AT_RESPONSE_OK);
    expect_string(uart_read, ptr, at_buf);
    expect_value(uart_read, len, AT_BUF_LEN);
    will_return(uart_read, strlen(AT_RESPONSE_OK));
    poll_i482e_at_response();

    sprintf((char *)at_buf, AT_IM_READY);
    expect_string(uart_read, ptr, at_buf);
    expect_value(uart_read, len, AT_BUF_LEN);
    will_return(uart_read, strlen(AT_IM_READY));
    poll_i482e_at_response();

    sprintf((char *)at_buf, AT_IM_SPP);
    expect_string(uart_read, ptr, at_buf);
    expect_value(uart_read, len, AT_BUF_LEN);
    will_return(uart_read, strlen(AT_IM_SPP));
    poll_i482e_at_response();

    // get name
    sprintf((char *)at_buf, "\r\n"AT_GET_NAME"n2ru-new-name\r\n\r\n\r\n");
    expect_string(uart_read, ptr, at_buf);
    expect_value(uart_read, len, AT_BUF_LEN);
    will_return(uart_read, strlen("\r\n"AT_GET_NAME"n2ru-new-name\r\n\r\n\r\n"));
    poll_i482e_at_response();
}

static void update_i482e_phy_status_test(void** state)
{
}

static void reset_i482e_phy_test(void** state)
{
    reset_i482e_phy();
}

static void open_i482e_phy_test(void** state)
{
    open_i482e_phy();
}

static void close_i482e_test(void** state)
{
    close_i482e();
    assert_false(i482e_current_alarm_status());
}

static void is_i482e_connected_test(void** state)
{
    will_return(ble_conn_display, false);
    assert_false(is_i482e_connected());
}

static void is_i482e_init_success_test(void** state)
{
    assert_true(is_i482e_init_success());
}

static void is_i482e_module_changed_test(void** state)
{
    assert_true(is_i482e_module_changed());
}

static void i482e_current_alarm_status_test(void** state)
{
    close_i482e();
    assert_false(i482e_current_alarm_status());
}

static void null_test(void** state)
{
}

int main(int argc, char** argv)
{
    UnitTest tests[] = {
        unit_test_setup_teardown(null_test, test_setup, NULL),
        unit_test_setup_teardown(send_i482e_message_test, test_setup, NULL),
        unit_test_setup_teardown(recv_i482e_message_test, test_setup, NULL),
        unit_test_setup_teardown(reset_i482e_soft_test, test_setup, NULL),
        unit_test_setup_teardown(reset_beacon_parameter_test, test_setup, NULL),
        unit_test_setup_teardown(update_i482e_name_test, test_setup, NULL),
        unit_test_setup_teardown(poll_i482e_at_response_test, test_setup, NULL),
        unit_test_setup_teardown(update_i482e_phy_status_test, test_setup, NULL),
        unit_test_setup_teardown(reset_i482e_phy_test, test_setup, NULL),
        unit_test_setup_teardown(open_i482e_phy_test, test_setup, NULL),
        unit_test_setup_teardown(close_i482e_test, test_setup, NULL),
        unit_test_setup_teardown(is_i482e_connected_test, test_setup, NULL),
        unit_test_setup_teardown(is_i482e_init_success_test, test_setup, NULL),
        unit_test_setup_teardown(i482e_current_alarm_status_test, test_setup, NULL),
        unit_test_setup_teardown(is_i482e_module_changed_test, test_setup, NULL),
    };
    return run_tests(tests);
}

#endif
