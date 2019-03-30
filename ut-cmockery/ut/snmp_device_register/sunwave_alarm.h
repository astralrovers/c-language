#ifndef __SUNWAVE_ALARM_H__
#define __SUNWAVE_ALARM_H__
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>

#define ALARM_INFO_LEN      21
#define SITE_ID_LEN         41
#define ALARM_TYPE_LEN      100

#define STRMAX              1024
#define MIB_NODE            8

#define ALM_WARNING   0
#define ALM_MINOR     1
#define ALM_MAJOR     2
#define ALM_CRITICAL  3

typedef struct _ALM_INFO_
{
 /*注册初始化使用*/
#ifndef INVALID_ALARM_ID
#define INVALID_ALARM_ID    0xff
#endif
    long   almId;
    char  *alarmType;

 /*协议转换使用*/
    uint16_t idEn;
    uint16_t idSta;
} __attribute__ ((packed)) ALM_INFO;

typedef struct alarmTable_entry {
    long alarmIdIndex;
    long alarmSeverity;
    long alarmStat;
    char alarmType[ALARM_TYPE_LEN];
    size_t alarmType_len;
    int   valid;
    struct alarmTable_entry *next;
}alarmInfo_entry, *pAlarmInfo_entry;

typedef struct alarmTrap_entry 
{
/*兼容KR, 平台实际没有用这么多信息*/
    /* Index values */
    long alarmId;  //索引

    /* Column values */
    long alarmDevSubId;  //设备编号
    long alarmSeverity;  //告警等级
    long alarmStat;      //告警状态
    
    char alarmType[ALARM_TYPE_LEN];  //告警类型
    size_t alarmType_len;

    char alarmCtime[ALARM_INFO_LEN];  //告警产生时间
    size_t alarmCtime_len;

    char alarmMtime[ALARM_INFO_LEN];  //alarm recover time 
    size_t alarmMtime_len;

    char mdlType[ALARM_INFO_LEN];  //设备类型,C-HUB, E-HUB,HPRU
    size_t mdlType_len;
    
    char mdlID[ALARM_INFO_LEN];    //设备站点和编号,device ID and sub ID
    size_t mdlID_len;

    char mdlName[ALARM_INFO_LEN];  //设备位置location
    size_t mdlName_len;

    char mdlSiteId[SITE_ID_LEN];  //设备站点编号
    size_t mdlSiteId_len;
    
    char mdlSerial[ALARM_INFO_LEN]; //生产序列号
    size_t mdlSerial_len;

    char mdlpartNum[ALARM_INFO_LEN];  //product model
    size_t mdlpartNum_len;

    char softVer[10];
    size_t softVer_len;

    char hardVer[10];
    size_t hardVer_len;

    char router[10];
    size_t router_len;

}alarmTrap_Info, *palarmTrap_Info;

typedef struct listTrap_entry
{
    char devIp[10];
    size_t devIp_len;
    char mdlID[ALARM_INFO_LEN];   
    size_t mdlID_len;
    char Ctime[ALARM_INFO_LEN];  
    size_t Ctime_len;
}listTrap_Member, *plistTrap_Member;


#define ALARMTABLE_TIMEOUT  60

#define COLUMN_ALARMIDIndex		1
#define COLUMN_ALARMSEVERITY	2
#define COLUMN_ALARMSTAT		3
#define COLUMN_ALARMTPYE		4

#define COLUMN_ALARM_START     COLUMN_ALARMIDIndex
#define COLUMN_ALARM_END       COLUMN_ALARMTPYE

#define DEVLISTTABLE_TIMEOUT  60

/* column number definitions for table devListTable */
#define COLUMN_DEVINDEX         1   
#define COLUMN_DEVID		    2
#define COLUMN_DEVTYPE		    3
#define COLUMN_DEVCONNECTSTAT   4
#define COLUMN_DEVROUTE         5    
#define COLUMN_LOCATION         6    

#define INVALID_MOBILE_ID   0xffff

#ifdef SNMP_DEVICE_REGISTER
struct alarmTable_entry *alarmTable_createEntry(long alarmId, char *info, int dev_no);
struct alarmTable_entry *get_alarm_table_head(uint8_t dev_no);
void push_alarm_table_list(uint8_t dev_no, struct alarmTable_entry *entry);
bool set_trapinfo_of_mobile_id(uint16_t mobile_id, uint8_t devSubId, uint8_t *mibType, struct alarmTrap_entry  *trapInfo);

void sunwave_alarm_register(void);
void snmp_table_type_setup(void);
void first_data_point_handler_init(uint8_t cnt);

uint16_t get_mobile_id_of_alarm_id(uint8_t index, uint8_t colnum, uint8_t mibtype);
ALM_INFO *get_device_alarm_list_by_mibtype(uint8_t mibtype);
#endif

uint32_t calculation_alarm_list_len(ALM_INFO *alarm_table);
ALM_INFO *get_device_alarm_list_by_device_type(uint8_t device_type);
bool get_alarmid_name_of_device_type(uint16_t id, uint8_t device_type, char *name);

#endif
