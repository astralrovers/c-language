#ifdef UNIT_TESTING

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <string.h>
#include <inttypes.h>
#include <stdlib.h>
#include <google/cmockery.h>
#include "ftp_download_file.h"

int32_t create_ftp_tcp_connect(uint8_t *ip, uint32_t port,
                                      uint32_t send_time, uint32_t recv_time)
{
    //check_expected(ip);
    check_expected(port);
    check_expected(send_time);
    check_expected(recv_time);
    return (int32_t)mock();
}

int32_t Str2Ip(uint8_t *ip, const uint8_t *str,
                      uint32_t start, uint32_t mid, uint32_t stop)
{
    //check_expected(ip);
    //check_expected(str);
    check_expected(start);
    check_expected(mid);
    check_expected(stop);
    return (int32_t)mock();
}

int32_t StrToDigit(const uint8_t *str, uint8_t c,
                          uint32_t n, uint32_t end, uint32_t *err)
{
    //check_expected(str);
    check_expected(c);
    check_expected(n);
    check_expected(end);
    //check_expected(err);
    return (int32_t)mock();
}

static struct download_ftp_file_addr *file_addr = NULL;
#define malloc_file_addr() \
        (struct download_ftp_file_addr* )malloc( \
                    sizeof(struct download_ftp_file_addr))
#define free_file_addr() \
        free(file_addr); \
        file_addr = NULL
#define alloc_file_addr() \
        file_addr = malloc_file_addr()

static void test_file_addr(void)
{
    file_addr->ip[0] = 127;
    file_addr->ip[1] = 0;
    file_addr->ip[2] = 0;
    file_addr->ip[3] = 1;
    file_addr->port = 21;
    sprintf(file_addr->user, "ubuntu");
    sprintf(file_addr->passwd, "ubuntu");
    sprintf(file_addr->remote_dir, "/home/ubuntu/");
    sprintf(file_addr->remote_file_name, "/home/ubuntu/test.zip");
    sprintf(file_addr->local_file_path, "/home/windows/test.zip");
}

static void test_init(void **state)
{
    alloc_file_addr();
    test_file_addr();
    slave_ftp_init();
}

static void test_exit(void **state)
{
    slave_ftp_exit();
    free_file_addr();
}

static void test_create_ftp_control_link(void** state)
{
    slave_ftp_setup(file_addr);
    expect_value(create_ftp_tcp_connect, port, 21);
    expect_value(create_ftp_tcp_connect, send_time, 5);
    expect_value(create_ftp_tcp_connect, recv_time, 5);
    will_return(create_ftp_tcp_connect, 12345);
    assert_true(create_ftp_contrl_link());
}

static void test_if_download_file_size_over_max(void** state)
{
    slave_ftp_setup(file_addr);
    expect_value(StrToDigit, c, ' ');
    expect_value(StrToDigit, n, 1);
    expect_value(StrToDigit, end, 0);
    will_return(StrToDigit, 1024);
    assert_false(if_download_file_size_over_max());

    expect_value(StrToDigit, c, ' ');
    expect_value(StrToDigit, n, 1);
    expect_value(StrToDigit, end, 0);
    will_return(StrToDigit, 0);
    assert_true(if_download_file_size_over_max());
    assert_int_equal(download_result(), 3);

    expect_value(StrToDigit, c, ' ');
    expect_value(StrToDigit, n, 1);
    expect_value(StrToDigit, end, 0);
    will_return(StrToDigit, 30*1024*1024);
    assert_true(if_download_file_size_over_max());
    assert_int_equal(download_result(), 1);
}

static void test_request_ftp_file_data(void **state)
{
    slave_ftp_setup(file_addr);
    request_ftp_file_data();
    assert_int_equal(download_result(), 6);
}

static void test_request_ftp_file_size(void **state)
{
    slave_ftp_setup(file_addr);
    assert_false(request_ftp_file_size());
    assert_int_equal(download_result(), 6);
}

static void test_request_ftp_login(void **state)
{
    slave_ftp_setup(file_addr);
    assert_false(request_ftp_login());
    assert_int_equal(download_result(), 5);
}

static void test_set_file_recv_breakpoint(void **state)
{
    slave_ftp_setup(file_addr);
    set_file_recv_breakpoint();
    assert_true(if_file_size_correct());
}

static void test_create_data_link(void **state)
{
    slave_ftp_setup(file_addr);
    expect_value(Str2Ip, start, '(');
    expect_value(Str2Ip, mid, ',');
    expect_value(Str2Ip, stop, ',');
    will_return(Str2Ip, 0);

    expect_value(StrToDigit, c, ',');
    expect_value(StrToDigit, n, 4);
    expect_value(StrToDigit, end, ',');
    will_return(StrToDigit, 1);

    expect_value(StrToDigit, c, ',');
    expect_value(StrToDigit, n, 5);
    expect_value(StrToDigit, end, 0);
    will_return(StrToDigit, 1);

    expect_value(create_ftp_tcp_connect, port, 1*256+1);
    expect_value(create_ftp_tcp_connect, send_time, 5);
    expect_value(create_ftp_tcp_connect, recv_time, 20);
    will_return(create_ftp_tcp_connect, 12345);
    assert_true(create_ftp_data_link());
}

static void test_request_ftp_data_port(void **state)
{
    slave_ftp_setup(file_addr);
    assert_false(request_ftp_data_port());
    assert_int_equal(download_result(), 6);
}

static void test_get_local_ftp_file_path(void **state)
{
    slave_ftp_setup(file_addr);
    assert_string_equal(get_local_ftp_file_path(), file_addr->local_file_path);
}

static void test_if_too_many_ftp_users(void **state)
{
    slave_ftp_setup(file_addr);
    assert_false(if_too_many_ftp_users());
}

static void unit_test_null(void **state)
{
    //TODO
}

int main(int argc, char** argv)
{
    UnitTest tests[] = {
        unit_test_setup_teardown(unit_test_null, NULL, NULL),
        unit_test_setup_teardown(test_create_ftp_control_link,
                                    test_init, test_exit),
        unit_test_setup_teardown(test_if_download_file_size_over_max,
                                    test_init, test_exit),
        unit_test_setup_teardown(test_request_ftp_file_data,
                                    test_init, test_exit),
        unit_test_setup_teardown(test_request_ftp_file_size,
                                    test_init, test_exit),
        unit_test_setup_teardown(test_request_ftp_login,
                                    test_init, test_exit),
        unit_test_setup_teardown(test_set_file_recv_breakpoint,
                                    test_init, test_exit),
        unit_test_setup_teardown(test_create_data_link,
                                    test_init, test_exit),
        unit_test_setup_teardown(test_request_ftp_data_port,
                                    test_init, test_exit),
        unit_test_setup_teardown(test_get_local_ftp_file_path,
                                    test_init, test_exit),
        unit_test_setup_teardown(test_if_too_many_ftp_users,
                                    test_init, test_exit),

    };
    return run_tests(tests);
}

#endif
