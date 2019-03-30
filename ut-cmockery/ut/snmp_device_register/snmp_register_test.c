#ifdef UNIT_TESTING

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <string.h>
#include <inttypes.h>
#include <google/cmockery.h>
#include "snmp_device_register.h"
#include "sunwave_normal.h"
#include "sunwave_alarm.h"
#include "arm_alarm_id_register.h"
#include "sunwave_oid.h"
#include "sunwave_slave_device_list.h"
#include "table/alarm_id_table.h"

#define FACTORY_ID_OID              {4,1,1}
#define DEV_MODEL_OID               {4,1,2}
#define DEV_SRRIAL_OID              {4,1,3}
#define ARM_VER_OID                 {4,1,4}
#define FPGA_VER_OID                {4,1,5}
#define SITE_ID_OID                 {4,1,6}
#define DEV_ID_OID                  {4,1,7}
#define DEV_LOCATION                {4,1,8}
#define DEV_SITE                    {4,1,9}
#define DEV_TIME_OID                {4,1,10}
#define SITE_REPORT_OID             {4,1,14}
#define DEV_TEMP_MAX_OID            {5,5,1}
#define ROUTE_ADD_OID               {5,5,2}
#define TEMP_HIGH_THR_OID           {2,2,1}
#define LIGHT_SERIAL_NUM_1			{4,1,16}
#define LIGHT_SERIAL_NUM_2			{4,1,17}

ST_OID_MAP_ID test_master_au_oid_map_mobile_id[] = {
    /* common */
    /*******************************************************/
	{FACTORY_ID_OID,            0x0029,     20},
	{DEV_SRRIAL_OID,            0x0005,     20},  
	{ARM_VER_OID,               0x000A,     20},    
	{FPGA_VER_OID,              0x0021,     20},    
	{SITE_ID_OID,               0x0101,     4},     
	{DEV_ID_OID ,               0x0102,     1},     
	{DEV_TIME_OID,              0x0150,     7},     
	{DEV_MODEL_OID,             0x0004,     20},  
	{DEV_LOCATION,              0x0023,     20},
	{DEV_SITE,                  0x0024,     40},
	{SITE_REPORT_OID,           0x0b09,     1},
	{DEV_TEMP_MAX_OID,          0x0501,     1},
	{ROUTE_ADD_OID,             0x0873,     4},   
	{TEMP_HIGH_THR_OID,         0x0451,     1},
	{LIGHT_SERIAL_NUM_1,	    0x0A96,	    16},
	{LIGHT_SERIAL_NUM_2,	    0x0A97,	    16},

    {INVALID_OID}
};

ALM_INFO test_master_au_alarm_id[] = {	
    {ALM_POWER_DOWN,        "Power Interruption Alarm" ,    0x0201,   0x0301},
    {ALM_BATTERT_FAULT,     "Battery Failure Alarm",        0x0204,   0x0304},
    {ALM_LOCATION,          "Movement Alarm",               0x0205,   0x0305},
    {ALM_TEMP,              "Over-temperature Alarm",       0x0206,   0x0306}, 
    {ALM_PLL1_UNLOCLK,      "LO1 Unlocked Alarm",           0x0260,   0x0360},
    {ALM_PLL2_UNLOCLK,      "LO2 Unlocked Alarm",           0x0261,   0x0361},
    {ALM_PLL3_UNLOCLK,      "LO3 Unlocked Alarm",           0x0262,   0x0362},
    {ALM_PLL4_UNLOCLK,      "LO4 Unlocked Alarm",           0x0263,   0x0363},

    {ALM_OPT1_LIGHT,        "OP1 Transceiver Failure Alarm",    0x02A0,     0x03A0}, 
    {ALM_OPT2_LIGHT,        "OP2 Transceiver Failure Alarm",    0x02A1,     0x03A1},  
    {ALM_OPT3_LIGHT,        "OP3 Transceiver Failure Alarm",    0x02A2,     0x03A2}, 
    {ALM_OPT4_LIGHT,        "OP4 Transceiver Failure Alarm",    0x02A3,     0x03A3}, 
    {ALM_OPT5_LIGHT,        "OP5 Transceiver Failure Alarm",    0x02A6,     0x03A6},
    {ALM_OPT6_LIGHT,        "OP6 Transceiver Failure Alarm",    0x02A7,     0x03A7}, 
    {ALM_OPT7_LIGHT,        "OP-AU1 Transceiver Failure Alarm",    0x02A4,     0x03A4},
    {ALM_OPT8_LIGHT,        "OP-AU2 Transceiver Failure Alarm",    0x02A5,     0x03A5},

    {ALM_EXT_1,             "External Alarm 1",                  0x0220,     0x0320},
    {ALM_EXT_2,             "External Alarm 2",                  0x0221,     0x0321},    
    {ALM_EXT_3,             "External Alarm 3",                  0x0222,     0x0322},       
    {ALM_EXT_4,             "External Alarm 4",                  0x0223,     0x0323},      
    {ALM_DOOR,              "Open Case Alarm",                   0x0228,     0x0328},
    {ALM_ALC1_OUT,          "Module1 DL ALC Over Range Alarm",    0x0264,     0x0364},
    {ALM_ALC2_OUT,          "Module2 DL ALC Over Range Alarm",    0x0265,     0x0365},
    {ALM_ALC3_OUT,          "Module3 DL ALC Over Range Alarm",    0x0266,     0x0366},
    {ALM_ALC4_OUT,          "Module4 DL ALC Over Range Alarm",    0x0267,     0x0367},

    {CHAN1PORT1_DLINPOWERUNDER,             "Module1 Port1 DL Under Input-power Alarm",    0X0240,     0X0340},
    {CHAN1PORT2_DLINPOWERUNDER,             "Module1 Port2 DL Under Input-power Alarm",    0X0241,     0X0341},
    {CHAN1PORT3_DLINPOWERUNDER,             "Module1 Port3 DL Under Input-power Alarm",    0X0242,     0X0342},
    {CHAN1PORT4_DLINPOWERUNDER,             "Module1 Port4 DL Under Input-power Alarm",    0X0243,     0X0343},
    {CHAN1PORT1_DLINPOWEROVER,              "Module1 Port1 DL Over Input-power Alarm" ,    0X0244,     0X0344},
    {CHAN1PORT2_DLINPOWEROVER,              "Module1 Port2 DL Over Input-power Alarm" ,    0X0245,     0X0345},
    {CHAN1PORT3_DLINPOWEROVER,              "Module1 Port3 DL Over Input-power Alarm" ,    0X0246,     0X0346},
    {CHAN1PORT4_DLINPOWEROVER,              "Module1 Port4 DL Over Input-power Alarm" ,    0X0247,     0X0347},

    {CHAN2PORT1_DLINPOWERUNDER,             "Module2 Port1 DL Under Input-power Alarm",    0X0248,     0X0348},
    {CHAN2PORT2_DLINPOWERUNDER,             "Module2 Port2 DL Under Input-power Alarm",    0X0249,     0X0349},
    {CHAN2PORT3_DLINPOWERUNDER,             "Module2 Port3 DL Under Input-power Alarm",    0X024A,     0X034A},
    {CHAN2PORT4_DLINPOWERUNDER,             "Module2 Port4 DL Under Input-power Alarm",    0X024B,     0X034B},
    {CHAN2PORT1_DLINPOWEROVER,              "Module2 Port1 DL Over Input-power Alarm" ,    0X024C,     0X034C},
    {CHAN2PORT2_DLINPOWEROVER,              "Module2 Port2 DL Over Input-power Alarm" ,    0X024D,     0X034D},
    {CHAN2PORT3_DLINPOWEROVER,              "Module2 Port3 DL Over Input-power Alarm" ,    0X024E,     0X034E},
    {CHAN2PORT4_DLINPOWEROVER,              "Module2 Port4 DL Over Input-power Alarm" ,    0X024F,     0X034F},

    {CHAN3PORT1_DLINPOWERUNDER,             "Module3 Port1 DL Under Input-power Alarm",    0X0250,     0X0350},
    {CHAN3PORT2_DLINPOWERUNDER,             "Module3 Port2 DL Under Input-power Alarm",    0X0251,     0X0351},
    {CHAN3PORT3_DLINPOWERUNDER,             "Module3 Port3 DL Under Input-power Alarm",    0X0252,     0X0352},
    {CHAN3PORT4_DLINPOWERUNDER,             "Module3 Port4 DL Under Input-power Alarm",    0X0253,     0X0353},
    {CHAN3PORT1_DLINPOWEROVER,              "Module3 Port1 DL Over Input-power Alarm" ,    0X0254,     0X0354},
    {CHAN3PORT2_DLINPOWEROVER,              "Module3 Port2 DL Over Input-power Alarm" ,    0X0255,     0X0355},
    {CHAN3PORT3_DLINPOWEROVER,              "Module3 Port3 DL Over Input-power Alarm" ,    0X0256,     0X0356},
    {CHAN3PORT4_DLINPOWEROVER,              "Module3 Port4 DL Over Input-power Alarm" ,    0X0257,     0X0357},

    {CHAN4PORT1_DLINPOWERUNDER,             "Module4 Port1 DL Under Input-power Alarm",    0X0258,     0X0358},
    {CHAN4PORT2_DLINPOWERUNDER,             "Module4 Port2 DL Under Input-power Alarm",    0X0259,     0X0359},
    {CHAN4PORT3_DLINPOWERUNDER,             "Module4 Port3 DL Under Input-power Alarm",    0X025A,     0X035A},
    {CHAN4PORT4_DLINPOWERUNDER,             "Module4 Port4 DL Under Input-power Alarm",    0X025B,     0X035B},
    {CHAN4PORT1_DLINPOWEROVER,              "Module4 Port1 DL Over Input-power Alarm" ,    0X025C,     0X035C},
    {CHAN4PORT2_DLINPOWEROVER,              "Module4 Port2 DL Over Input-power Alarm" ,    0X025D,     0X035D},
    {CHAN4PORT3_DLINPOWEROVER,              "Module4 Port3 DL Over Input-power Alarm" ,    0X025E,     0X035E},
    {CHAN4PORT4_DLINPOWEROVER,              "Module4 Port4 DL Over Input-power Alarm" ,    0X025F,     0X035F},

    {ALM_BAND_CONF_FAIL,                    "Band Configuration Failure Alarm",            0X023A,     0X033A},
    {INVALID_ALARM_ID}
};

void netsnmp_scalar_register(uint8_t dev_no)
{
    return ;
}

void netsnmp_alarm_register(uint8_t dev_no)
{
    return ;
}

uint8_t get_slave_device_type(uint8_t device_id)
{
    return 0;
}

struct test_variable3 {
#define r__     1
#define w__     2
#define rw_     3
    uint16_t type;
    uint8_t oid[3];
};

#define TEST_INVALID_OID_VAR    {0xff, 0xff, 0xff}
struct test_variable3 test_oid_variable3[] = {
    {r__, {1, 1, 2}},
    {r__, {1, 1, 3}},
    {r__, {1, 1, 4}},
    {r__, {1, 1, 5}},
    {r__, {1, 1, 6}},
    {r__, {1, 1, 7}},
    {r__, {1, 1, 8}},
    {r__, {1, 1, 9}},
    {r__, {1, 1, 10}},
    {r__, {1, 1, 11}},
    {.oid = TEST_INVALID_OID_VAR}
};
#define ARRAY_SIZE_TEST_OID_VAR (sizeof(test_oid_variable3)/ \
                                 sizeof(test_oid_variable3[0])-1)

size_t sum_test_oid_variable3_len(struct test_variable3* oid_variable)
{
    size_t i = 0;
    uint8_t invalid[] = TEST_INVALID_OID_VAR;
    for (i = 0; memcmp(oid_variable[i].oid, invalid, sizeof(invalid)); i++);
    return i;
}

static ST_DEVICE_BASE_INFO device_list[] = {
    /* master au 必须写到第一个位置, 其他设备也必须按顺序写，序号不能中断, 小于255 */
    {1, 252, "alarmTable", "Master AU",
        test_oid_variable3, test_master_au_oid_map_mobile_id, test_master_au_alarm_id},
};

static uint8_t get_device_num(void)
{
    return sizeof(device_list)/sizeof(device_list[0]);
}

static void test_setup(void** state)
{
    snmp_device_init(get_device_num());
    snmp_device_setup(0, device_list);
}

static void test_exit(void** state)
{

}

extern uint8_t master_alarm_num(void);
static void calculation_alarm_list_len_test(void** state)
{
    assert_int_equal(
                calculation_alarm_list_len(device_list[0].alarm_list),
                master_alarm_num());
}

static void if_mibtype_registered_test(void** state)
{
    assert_true(if_mibtype_registered(1));
}

static void is_master_devid_test(void** state)
{
    assert_true(is_master_devid(0));
    assert_false(is_master_devid(2));
}

static void if_mibtype_match_device_test(void** state)
{
    assert_true(if_mibtype_match_device(1, 0));
    assert_false(if_mibtype_match_device(1, 2));
}

static void get_device_name_test(void** state)
{
    char name[20] = {'\0'};
    get_device_name(1, name);
    assert_string_equal(name, "Master AU");
    bzero(name, sizeof(name));
    get_device_name(2, name);
    assert_string_equal(name, "Undefined module");
}

#define ARRAY_SIZE_ALARM    (sizeof(test_master_au_alarm_id)/ \
                                sizeof(test_master_au_alarm_id[0]) - 1)

void get_mobile_id_of_alarm_id_test(void** state)
{
    int i = 0;
    for (i = 0; i < ARRAY_SIZE_ALARM; i++) {
        assert_int_equal(get_mobile_id_of_alarm_id(
                            test_master_au_alarm_id[i].almId,
                            COLUMN_ALARMSTAT, 1),
                         test_master_au_alarm_id[i].idSta);
        assert_int_equal(get_mobile_id_of_alarm_id(
                            test_master_au_alarm_id[i].almId,
                            COLUMN_ALARMSEVERITY, 1),
                         test_master_au_alarm_id[i].idEn);
    }
    assert_int_equal(get_mobile_id_of_alarm_id(
                        test_master_au_alarm_id[0].almId,
                        10, 1),
                     INVALID_MOBILE_ID);
    assert_int_equal(get_mobile_id_of_alarm_id(
                        INVALID_ALARM_ID,
                        COLUMN_ALARMSEVERITY, 1),
                     INVALID_MOBILE_ID);
    assert_int_equal(get_mobile_id_of_alarm_id(
                        test_master_au_alarm_id[0].almId,
                        COLUMN_ALARMSEVERITY, 2),
                     INVALID_MOBILE_ID);
}

static void set_trapinfo_of_mobile_id_test(void** state)
{
    int i = 0;
    uint8_t master_mib;
    struct alarmTrap_entry trap;
    for (i = 0; i < ARRAY_SIZE_ALARM; i++) {
        bzero(&trap, sizeof(trap));
        assert_true(set_trapinfo_of_mobile_id(
                        test_master_au_alarm_id[i].idSta,
                        0, &master_mib, &trap));
    }
}

static void get_device_alarm_list_by_device_type_test(void** state)
{
    assert_int_equal(get_device_alarm_list_by_device_type(252), 
                     device_list[0].alarm_list);
}

static void get_alarmid_name_of_device_type_test(void** state)
{
    int i = 0;
    char name[100] = {'\0'};
    for (i = 0; i < ARRAY_SIZE_ALARM; i++) {
        bzero(name, sizeof(name));
        assert_true(get_alarmid_name_of_device_type(
                        test_master_au_alarm_id[i].idSta,
                        252, name));
        assert_string_equal(name, test_master_au_alarm_id[i].alarmType);
    }
}

#define ARRAY_SIZE_OID_MOBILEID (sizeof(test_master_au_oid_map_mobile_id)/ \
                                 sizeof(test_master_au_oid_map_mobile_id[0])-1)


static void calculation_oid_mapping_mobileid_len_test(void** state)
{
    assert_int_equal(calculation_oid_mapping_mobileid_len(
                        device_list[0].oid_mobileid),
                     ARRAY_SIZE_OID_MOBILEID);
}

static void get_device_oid_mobileid_list_by_mibtype_test(void** state)
{
    assert_int_equal(get_device_oid_mobileid_list_by_mibtype(1),
                     device_list[0].oid_mobileid);
}

static void get_mobileid_of_oid_test(void** state)
{
    int i = 0;
    uint8_t len;
    uint16_t mobile_id;
    for (i = 0; i < ARRAY_SIZE_OID_MOBILEID; i++) {
        assert_true(get_mobileid_of_oid(
                            1,
                            device_list[0].oid_mobileid[i].oid,
                            &len, &mobile_id));
        assert_int_equal(mobile_id, device_list[0].oid_mobileid[i].id);
        assert_int_equal(len, device_list[0].oid_mobileid[i].len);
    }
}

static void sum_test_oid_variable3_len_test(void** state)
{
    assert_int_equal(sum_test_oid_variable3_len(
                        (struct test_variable3* )device_list[0].oid_variable),
                     ARRAY_SIZE_TEST_OID_VAR);
}

int main(int argc, char** argv)
{
    UnitTest tests[] = {
        unit_test_setup_teardown(if_mibtype_registered_test,
                                 test_setup, test_exit),
        unit_test_setup_teardown(is_master_devid_test,
                                 NULL, NULL),
        unit_test_setup_teardown(if_mibtype_match_device_test,
                                 test_setup, test_exit),
        unit_test_setup_teardown(get_device_name_test,
                                 test_setup, test_exit),
        unit_test_setup_teardown(calculation_alarm_list_len_test,
                                 test_setup, test_exit),
        unit_test_setup_teardown(get_mobile_id_of_alarm_id_test,
                                 test_setup, test_exit),
        unit_test_setup_teardown(set_trapinfo_of_mobile_id_test,
                                 test_setup, test_exit),
        unit_test_setup_teardown(get_device_alarm_list_by_device_type_test,
                                 test_setup, test_exit),
        unit_test_setup_teardown(get_alarmid_name_of_device_type_test,
                                 test_setup, test_exit),
        unit_test_setup_teardown(calculation_oid_mapping_mobileid_len_test,
                                 test_setup, test_exit),
        unit_test_setup_teardown(get_device_oid_mobileid_list_by_mibtype_test,
                                 test_setup, test_exit),
        unit_test_setup_teardown(get_mobileid_of_oid_test,
                                 test_setup, test_exit),
        unit_test_setup_teardown(sum_test_oid_variable3_len_test,
                                 test_setup, test_exit),
    };
    return run_tests(tests);
}

#endif
