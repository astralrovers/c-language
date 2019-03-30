#ifndef __SUNWAVE_NORMAL_H__
#define __SUNWAVE_NORMAL_H__
#ifdef SNMP_DEVICE_REGISTER
#include <stdbool.h>
#include <inttypes.h>

extern uint8_t get_slave_device_type(uint8_t device_id);
bool is_master_devid(uint8_t devId);
bool if_mibtype_match_device(uint8_t mibtype, uint8_t devid);
uint8_t get_master_mibtype(void);
uint8_t get_master_au_device_no(void);
uint8_t get_master_au_device_type(void);
void get_device_name(uint8_t mibtype, char *device_name);
void sunwave_scalar_register(void);
#endif

#endif
