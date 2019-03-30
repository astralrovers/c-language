#ifndef __SNMP_DEVICE_REGISTER_H__
#define __SNMP_DEVICE_REGISTER_H__

#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include "sunwave_alarm.h"
#include "sunwave_oid.h"

typedef struct {
    uint8_t mibtype;
    uint8_t device_type;
    char *alarm_name;
    char *device_name;
    void *oid_variable;
    ST_OID_MAP_ID *oid_mobileid;
    ALM_INFO *alarm_list;
}ST_DEVICE_BASE_INFO;

void snmp_device_init(uint8_t cnt);
void snmp_device_setup(uint32_t company_mibnode, ST_DEVICE_BASE_INFO* device_list);

ST_DEVICE_BASE_INFO *get_device_list(void);
uint8_t get_device_cnt(void);
uint32_t get_company_mibnode(void);

bool if_mibtype_registered(uint8_t mibtype);


#endif
