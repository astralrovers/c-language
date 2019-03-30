#include "snmp_device_register.h"
#include "sunwave_normal.h"
#include "sunwave_alarm.h"

#define INVALID_DEVICE_NO   0xff

static uint8_t g_device_cnt = INVALID_DEVICE_NO;
static ST_DEVICE_BASE_INFO *g_device_list = NULL;
static uint32_t g_company_mibnode;

uint32_t get_company_mibnode(void)
{
    return g_company_mibnode;
}

uint8_t get_device_cnt(void)
{
    return g_device_cnt;
}

ST_DEVICE_BASE_INFO *get_device_list(void)
{
    return g_device_list;
}

bool if_mibtype_registered(uint8_t mibtype)
{
    int i = 0;
    for (i = 0; i < g_device_cnt; i++) {
        if (mibtype == g_device_list[i].mibtype) { return true; }
    }
    return false;
}

void snmp_device_init(uint8_t cnt)
{
    g_device_cnt = cnt;
}

void snmp_device_setup(uint32_t company_mibnode,
                       ST_DEVICE_BASE_INFO* device_list)
{
    g_company_mibnode = company_mibnode;
    g_device_list = device_list;
}

#ifdef SNMP_DEVICE_REGISTER

static void sunwave_slave_device_list_register(void)
{
    //TODO
}

static void sunwave_table_type_register(void)
{
    snmp_table_type_setup();
    sunwave_alarm_register();
    sunwave_slave_device_list_register();
}

void register_device(void)
{
    sunwave_scalar_register();
    sunwave_table_type_register();
}
#endif
