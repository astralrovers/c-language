#ifndef __SUNWAVE_OID_H__
#define __SUNWAVE_OID_H__
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>

#define OID_NAME_LEN      3
#define SUNWAVE_OID_LEN   9         // sunwaveMau_variables_oid bytes

/******* 通用类型 ****************/
#define MIBINTEGER      1
#define MIBSTRING       2
#define MIBIPADDRESS    3

#define MIBTRAPIP       20   
#define MIBTRAPORT      21
#define MIBTRAP2IP      23  

/*** 单个类型需要特殊处理的 *****/
#define MIBTIMESTR      4
#define MIBSITEID       5
#define MIBUPDATERES    6
#define MIBRUPAPWR      7
#define MIBCAPACITY     8
#define MIBINT8S        9
#define MIBCAPACITYGRP  10
#define CHANMAPSTR      12

/*** 以下类型无需转移动协议 *****/
#define MIBSLVNUM      22

#define INVALID_OID {0xff, 0xff, 0xff}

typedef struct
{
	uint8_t oid[OID_NAME_LEN];
	uint16_t id;             
	uint8_t len;            
}__attribute__ ((packed)) ST_OID_MAP_ID;


#ifdef SNMP_DEVICE_REGISTER
size_t calculation_oid_mapping_mobileid_len(ST_OID_MAP_ID *oid_mobileid);
ST_OID_MAP_ID *get_device_oid_mobileid_list_by_mibtype(uint8_t mibtype);
bool get_mobileid_of_oid(uint8_t mibtype, uint8_t *name,
                         uint8_t *len, uint16_t *mobile_id);
#endif

#endif
