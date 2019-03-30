#include <stdio.h>
#include <string.h>
#include "sunwave_oid.h"
#include "snmp_device_register.h"
#ifdef SNMP_DEVICE_REGISTER

#ifndef MAP_END
#define MAP_END 0xffff
#endif

size_t calculation_oid_mapping_mobileid_len(ST_OID_MAP_ID  *oid_mobileid)
{
    int i = 0;
    uint8_t end_oid[] = INVALID_OID;
    if (!oid_mobileid) { return 0; }
    for (i = 0; memcmp(oid_mobileid[i].oid, end_oid, sizeof(end_oid)); i++);
    return i;
}

ST_OID_MAP_ID *get_device_oid_mobileid_list_by_mibtype(uint8_t mibtype)
{
    ST_DEVICE_BASE_INFO *device_list = get_device_list();
    uint8_t device_cnt = get_device_cnt();
    int i = 0;
    for (i = 0; i < device_cnt; i++) {
        if (device_list[i].mibtype == mibtype) {
            return device_list[i].oid_mobileid;
        }
    }
    return NULL;
}

bool get_mobileid_of_oid(uint8_t mibtype, uint8_t *name,
                         uint8_t *len, uint16_t *mobile_id)
{
    int i = 0;
    ST_OID_MAP_ID *oid_mobileid = get_device_oid_mobileid_list_by_mibtype(mibtype);
    if (!oid_mobileid) { return false; }
    size_t mobileid_num = calculation_oid_mapping_mobileid_len(oid_mobileid);

    for (i = 0; i < mobileid_num; i++) {
        if (!memcmp(oid_mobileid[i].oid, name, sizeof(uint8_t)*3)) {
            *len = oid_mobileid[i].len;
            *mobile_id = oid_mobileid[i].id;
            return true;
        }
    }
	return false;
}
#endif
