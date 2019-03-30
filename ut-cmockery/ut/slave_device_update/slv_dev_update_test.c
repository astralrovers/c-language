#ifdef UNIT_TESTING

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <string.h>
#include <inttypes.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <google/cmockery.h>
#include "ftp_normal_update.h"
#include "ftp_webkey_update.h"
#include "update_inc.h"

static uint16_t normal_old_crc = 0x1024;
static uint16_t normal_new_crc = 0x1023;
static uint8_t  normal_soft_version = 0;
static uint8_t  normal_dbg = 0;

static void normal_init(void **state)
{
    ftp_normal_update_init();
}

static void normal_exit(void **state)
{
    ftp_normal_update_exit();
}

static void normal_setup(void)
{
    ftp_normal_update_setup(&normal_old_crc, &normal_new_crc,
                            &normal_soft_version, &normal_dbg);
}

static void test_check_slv_need_update(void **state)
{
    normal_setup();
    assert_true(check_slv_need_update());
    assert_int_equal(normal_soft_version, 0);

    normal_new_crc = 0x1024;
    assert_false(check_slv_need_update());
    assert_int_equal(normal_soft_version, 1);

    normal_new_crc = INVALID_CRC;
    assert_false(check_slv_need_update());
    assert_int_equal(normal_soft_version, 0);

    normal_new_crc = 0x1023;
    normal_dbg = 1;
    assert_false(check_slv_need_update());
    assert_int_equal(normal_soft_version, 2);
}

static void test_get_backup_new_crc(void** state)
{
    normal_setup();
    set_backup_new_crc();
    assert_int_equal(get_backup_new_crc(), normal_new_crc);
}

static void test_recording_wrong_packet(void** state)
{
    normal_setup();
    recording_wrong_packet();
    assert_false(check_slv_need_update());
}

static void test_recording_wrong_crc(void** state)
{
    normal_setup();
    recording_wrong_crc();
    assert_false(check_slv_need_update());
}

#define WEBKEY  "webkey.name"
static bool link_st = true;
static uint16_t webkey_new_crc = 0x1024;
static uint16_t webkey_old_crc = 0x1023;
static char webkey_name[20] = WEBKEY;

static void webkey_init(void ** state)
{
    webkey_update_init();
}

static void webkey_exit(void **state)
{
    webkey_update_exit();
}

static void webkey_setup()
{
    webkey_update_setup(&link_st, &webkey_old_crc, &webkey_new_crc, webkey_name);
}

static void test_check_web_file_need_update(void **state)
{
    webkey_setup();
    assert_true(check_web_file_need_update());

    link_st = false;
    assert_false(check_web_file_need_update());

    link_st = true;
    webkey_new_crc = INVALID_CRC;
    assert_false(check_web_file_need_update());

    webkey_old_crc = webkey_new_crc;
    assert_false(check_web_file_need_update());
}

static void create_webkey(void)
{
    system("touch "WEBKEY);
    system("echo \" hello world\" >> "WEBKEY);
    sync();
}

static void test_save_webkey_crc(void **state)
{
    webkey_setup();
    save_webkey_crc();
    assert_int_equal(webkey_new_crc, webkey_old_crc);
}

static int32_t del_webkey_success(void)
{
    return access(WEBKEY, F_OK);
}

static void test_del_webkey(void **state)
{
    webkey_setup();
    webkey_new_crc = INVALID_CRC;
    create_webkey();
    check_web_file_need_update();
    assert_int_equal(del_webkey_success(), -1);
}

static void unit_test_null(void **state)
{
    //TODO
}

int main(int argc, char** argv)
{
    UnitTest tests[] = {
        unit_test_setup_teardown(unit_test_null, NULL, NULL),
        unit_test_setup_teardown(test_check_slv_need_update,
                                    normal_init, normal_exit),
        unit_test_setup_teardown(test_get_backup_new_crc,
                                    normal_init, normal_exit),
        unit_test_setup_teardown(test_recording_wrong_packet,
                                    normal_init, normal_exit),
        unit_test_setup_teardown(test_recording_wrong_crc,
                                    normal_init, normal_exit),
        unit_test_setup_teardown(test_check_web_file_need_update,
                                    webkey_init, webkey_exit),
        unit_test_setup_teardown(test_save_webkey_crc,
                                    webkey_init, webkey_exit),
        unit_test_setup_teardown(test_del_webkey,
                                    webkey_init, webkey_exit),
    };
    return run_tests(tests);
}

#endif
