#include <string.h>
#include <stdlib.h>
#include "sunwave_alarm.h"
#include "sunwave_normal.h"
#include "snmp_device_register.h"
#ifdef SNMP_DEVICE_REGISTER

static struct alarmTable_entry** alarm_table_head = NULL;

void first_data_point_handler_init(uint8_t cnt)
{
    alarm_table_head = malloc(cnt*sizeof(struct alarmTable_entry*));
    int i = 0 ;
    for (i = 0; i < cnt; i++) {
        *(alarm_table_head+i) = NULL;
    }
}

void first_data_point_handler_exit(uint8_t cnt)
{
    free(alarm_table_head);
}

void push_alarm_table_list(uint8_t dev_no, struct alarmTable_entry *entry)
{
    if (!entry) { return ; }
    entry->next = *(alarm_table_head + dev_no);
    *(alarm_table_head+dev_no) = entry;
}

struct alarmTable_entry *get_alarm_table_head(uint8_t dev_no)
{
    return *(alarm_table_head+dev_no);
}

struct alarmTable_entry *alarmTable_createEntry(long alarmId,
                                                char *info,
                                                int dev_no) 
{
	struct alarmTable_entry *entry;

	entry = calloc(1, sizeof(struct alarmTable_entry));
	if (!entry) { return NULL; }
	entry->alarmIdIndex = alarmId;
	strcpy(entry->alarmType, info);
	entry->alarmType_len = strlen(info);
    push_alarm_table_list(dev_no, entry);
	return entry;
}

ALM_INFO *get_device_alarm_list_by_mibtype(uint8_t mibtype)
{
    ST_DEVICE_BASE_INFO *device_list = get_device_list();
    uint8_t device_cnt = get_device_cnt();
    int i = 0;
    for (i = 0; i < device_cnt; i++) {
        if (device_list[i].mibtype == mibtype) {
            return device_list[i].alarm_list;
        }
    }
    return NULL;
}

uint16_t get_mobile_id_of_alarm_id(uint8_t index,
                                   uint8_t colnum,
                                   uint8_t mibtype)
{
	int i;
	uint8_t len = 0;
	ALM_INFO *ptr = get_device_alarm_list_by_mibtype(mibtype);
    if (!ptr) { return INVALID_MOBILE_ID; }
    len = calculation_alarm_list_len(ptr);
	for (i = 0; i < len; i++) {
		if (ptr[i].almId == index) {
			/*colnum for which item of one alarm*/
			switch (colnum) {
				case COLUMN_ALARMSTAT:         
					return ptr[i].idSta;
				case COLUMN_ALARMSEVERITY:
					return ptr[i].idEn;
				default:
					break;
			}
		}
	}
    return INVALID_MOBILE_ID;
}

bool set_trapinfo_of_mobile_id(uint16_t mobile_id,
                               uint8_t devSubId,
                               uint8_t *mibType,
                               struct alarmTrap_entry *trapInfo)
{
	int i;
	uint8_t len = 0;
    uint8_t slave_type = 0;
	ALM_INFO *ptr = NULL;
    ST_DEVICE_BASE_INFO *device_list = get_device_list();
    uint8_t dev_cnt = get_device_cnt();

	trapInfo->alarmDevSubId = devSubId;
    if (is_master_devid(devSubId)) {
        *mibType = device_list[0].mibtype;
        ptr = device_list[0].alarm_list;
    } else {
        slave_type = get_slave_device_type(devSubId);
        for (i = 1; i < dev_cnt; i++) {
            if (slave_type == device_list[i].device_type) {
                *mibType = device_list[i].mibtype;
                ptr = device_list[i].alarm_list;
                break;
            }
        }
	}
    if (!ptr) { return false; }
    len = calculation_alarm_list_len(ptr);
	for (i = 0; i < len; i++) {
		if (ptr[i].idSta == mobile_id) {
			trapInfo->alarmId = ptr[i].almId;
            printf("alarm_id = [0x%.4X], alarm_type = [%s]\n", ptr[i].idSta, ptr[i].alarmType);
			memcpy(trapInfo->alarmType,
                   ptr[i].alarmType,
                   strlen(ptr[i].alarmType));
			return true;
		}
	}
	return false;
}

void snmp_table_type_setup(void)
{
    first_data_point_handler_init(get_device_cnt());
}

extern void netsnmp_alarm_register(uint8_t dev_no);
void sunwave_alarm_register(void)
{
    int i = 0;
    uint8_t dev_cnt = get_device_cnt();
    for (i = 0; i < dev_cnt; i++) {
        netsnmp_alarm_register(i);
    }
}
#endif

uint32_t calculation_alarm_list_len(ALM_INFO *alarm_table)
{
    int i = 0;
    if (!alarm_table) { return 0; }
    for (i = 0; alarm_table[i].almId != INVALID_ALARM_ID; i++);
    return i;
}

ALM_INFO *get_device_alarm_list_by_device_type(uint8_t device_type)
{
    ST_DEVICE_BASE_INFO *device_list = get_device_list();
    uint8_t device_cnt = get_device_cnt();
    int i = 0;
    for (i = 0; i < device_cnt; i++) {
        if (device_list[i].device_type == device_type) {
            return device_list[i].alarm_list;
        }
    }
    return NULL;
}

bool get_alarmid_name_of_device_type(uint16_t id, uint8_t device_type, char *name)
{
    if (!name) { return false; }
    ALM_INFO *alarm_list = get_device_alarm_list_by_device_type(device_type);
    if (!alarm_list) { return false; }
    int i = 0;
    uint8_t len = calculation_alarm_list_len(alarm_list);
    for (i = 0; i < len; i++) {
        if (alarm_list[i].idSta == id) {
            strcpy(name, alarm_list[i].alarmType);
            return true;
        }
    }
    return false;
}
