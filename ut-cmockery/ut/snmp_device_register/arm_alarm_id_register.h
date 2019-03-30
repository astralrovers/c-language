#ifndef __ARM_ALARM_ID_REGISTER_H__
#define __ARM_ALARM_ID_REGISTER_H__

#ifdef ARM_ALARM_ID_REGISTER
#include "snmp_device_register.h"

void arm_alarm_id_init(uint8_t cnt);
void arm_alarm_id_setup(ST_DEVICE_BASE_INFO* device_list);
#endif

#endif
