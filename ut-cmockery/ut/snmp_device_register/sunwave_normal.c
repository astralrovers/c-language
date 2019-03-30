#include <string.h>
#include "sunwave_normal.h"
#include "snmp_device_register.h"
#ifdef SNMP_DEVICE_REGISTER

#define MASTER_AU_DEVICE_NO     0

bool is_master_devid(uint8_t devId)
{
    return (devId == MASTER_AU_DEVICE_NO);
}

uint8_t get_master_au_device_no(void)
{
    return MASTER_AU_DEVICE_NO;
}

uint8_t get_master_au_device_type(void)
{
    ST_DEVICE_BASE_INFO *device_list = get_device_list();
    return device_list[0].device_type;
}

uint8_t get_master_mibtype(void)
{
    ST_DEVICE_BASE_INFO *device_list = get_device_list();
    return device_list[0].mibtype;
}

static bool is_master_au_mibtype(uint8_t mibType)
{
    ST_DEVICE_BASE_INFO *device_list = get_device_list();
    return (mibType == device_list[0].mibtype);
}

static bool is_slave_mibtype(uint8_t mibType)
{
    int i = 0;
    ST_DEVICE_BASE_INFO *device_list = get_device_list();
    uint8_t dev_cnt = get_device_cnt();
    for (i = 1; i < dev_cnt; i++) {
        if (mibType == device_list[i].mibtype) { return true; }
    }
    return false;
}

static bool is_master_au_dev(uint8_t mibType, uint8_t devId)
{
    return (is_master_devid(devId) && is_master_au_mibtype(mibType)) ? true : false;
}

static bool is_slave_dev(uint8_t mibType, uint8_t devId)
{
    return (!is_master_devid(devId) && is_slave_mibtype(mibType)) ? true : false;
}

static bool check_slavetype_match_mibtype(uint8_t mibType, uint8_t devId)
{
    int i = 0;
    uint8_t slave_type = get_slave_device_type(devId);
    ST_DEVICE_BASE_INFO *device_list = get_device_list();
    uint8_t dev_cnt = get_device_cnt();
    for (i = 1; i < dev_cnt; i++) {
        if ((slave_type == device_list[i].device_type) &&
            ((mibType == device_list[i].mibtype))) {
            return true;
        }
    }
    return false;
}

bool if_mibtype_match_device(uint8_t mibtype, uint8_t devid)
{
    if (is_master_au_dev(mibtype, devid)) {
        return true;
    } else if (!is_slave_dev(mibtype, devid)) {
        return false;
    } else {
        return check_slavetype_match_mibtype(mibtype, devid);
    }
}

void get_device_name(uint8_t mibtype, char *device_name)
{
    ST_DEVICE_BASE_INFO *device_list = get_device_list();
    uint8_t dev_cnt = get_device_cnt();
    int i = 0;
    for (i = 0; i < dev_cnt; i++) {
        if (mibtype == device_list[i].mibtype) {
            strcpy(device_name, device_list[i].device_name);
            return;
        }
    }
	strcpy(device_name, "Undefined module");
}


extern void netsnmp_scalar_register(uint8_t dev_no);
void sunwave_scalar_register(void)
{
    int i = 0;
    uint8_t dev_cnt = get_device_cnt();
    for (i = 0; i < dev_cnt; i++) {
        netsnmp_scalar_register(i);
    }
}
#endif
