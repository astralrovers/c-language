#ifdef ARM_ALARM_ID_REGISTER
#include "arm_alarm_id_register.h"

void arm_alarm_id_init(uint8_t cnt)
{
    snmp_device_init(cnt);
}

void arm_alarm_id_setup(ST_DEVICE_BASE_INFO* device_list)
{
    snmp_device_setup(0, device_list);
}

#endif
