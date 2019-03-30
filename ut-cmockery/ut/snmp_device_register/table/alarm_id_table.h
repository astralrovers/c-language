#ifndef _ALARM_ID_TABLE_H
#define _ALARM_ID_TABLE_H
#include <inttypes.h>

/***********alarmTable**********************/
/*alarm Id*/

#define ALM_POWER_DOWN      1
#define ALM_BATTERT_FAULT   2
#define ALM_LOCATION        3
#define ALM_TEMP            4
#define ALM_SIG_FAULT       5
#define ALM_SLV_LINK_FAIL   6
#define ALM_PLL1_UNLOCLK    7
#define ALM_PLL2_UNLOCLK    8
#define ALM_PLL3_UNLOCLK    9
#define ALM_PLL4_UNLOCLK    10


//18~19 KR机型使用

#define ALM_OPT1_LIGHT      20
#define ALM_OPT2_LIGHT      21
#define ALM_OPT3_LIGHT      22
#define ALM_OPT4_LIGHT      23
#define ALM_OPT5_LIGHT      24
#define ALM_OPT6_LIGHT      25
#define ALM_OPT7_LIGHT      26
#define ALM_OPT8_LIGHT      27
#define ALM_OPT_IN          28
#define ALM_OPT_OUT         29
#define ALM_DNOUTPWR1_HIGH  30 
#define ALM_DNOUTPWR2_HIGH  31
#define ALM_DNOUTPWR3_HIGH  32
#define ALM_DNOUTPWR4_HIGH  33
#define ALM_DNOUTPWR1_LOW   34
#define ALM_DNOUTPWR2_LOW   35
#define ALM_DNOUTPWR3_LOW   36
#define ALM_DNOUTPWR4_LOW   37

#define ALM_EXT_1           38
#define ALM_EXT_2           39
#define ALM_EXT_3           40
#define ALM_EXT_4           41
#define ALM_EXT_5           42
#define ALM_EXT_6           43
#define ALM_DOOR            44

#define ALM_ALC1            45
#define ALM_ALC2            46
#define ALM_ALC3            47
#define ALM_ALC4            48

#define ALM_VSW1            49
#define ALM_VSW2            50

#define ALM_ALC1_OUT        51
#define ALM_ALC2_OUT        52
#define ALM_ALC3_OUT        53
#define ALM_ALC4_OUT        54

#define CHAN1PORT1_DLINPOWERUNDER       55
#define CHAN1PORT2_DLINPOWERUNDER       56
#define CHAN1PORT3_DLINPOWERUNDER       57
#define CHAN1PORT4_DLINPOWERUNDER       58
#define CHAN1PORT1_DLINPOWEROVER        59
#define CHAN1PORT2_DLINPOWEROVER        60
#define CHAN1PORT3_DLINPOWEROVER        61
#define CHAN1PORT4_DLINPOWEROVER        62

#define CHAN2PORT1_DLINPOWERUNDER       63
#define CHAN2PORT2_DLINPOWERUNDER       64
#define CHAN2PORT3_DLINPOWERUNDER       65
#define CHAN2PORT4_DLINPOWERUNDER       66
#define CHAN2PORT1_DLINPOWEROVER        67
#define CHAN2PORT2_DLINPOWEROVER        68
#define CHAN2PORT3_DLINPOWEROVER        69
#define CHAN2PORT4_DLINPOWEROVER        70

#define CHAN3PORT1_DLINPOWERUNDER       71
#define CHAN3PORT2_DLINPOWERUNDER       72
#define CHAN3PORT3_DLINPOWERUNDER       73
#define CHAN3PORT4_DLINPOWERUNDER       74
#define CHAN3PORT1_DLINPOWEROVER        75
#define CHAN3PORT2_DLINPOWEROVER        76
#define CHAN3PORT3_DLINPOWEROVER        77
#define CHAN3PORT4_DLINPOWEROVER        78

#define CHAN4PORT1_DLINPOWERUNDER       79
#define CHAN4PORT2_DLINPOWERUNDER       80
#define CHAN4PORT3_DLINPOWERUNDER       81
#define CHAN4PORT4_DLINPOWERUNDER       82
#define CHAN4PORT1_DLINPOWEROVER        83
#define CHAN4PORT2_DLINPOWEROVER        84
#define CHAN4PORT3_DLINPOWEROVER        85
#define CHAN4PORT4_DLINPOWEROVER        86

#define ALM_OPT_SWITCH                  87

//87~90 KR机型使用

#define ALM_ALC1_UL_OUT             91
#define ALM_ALC2_UL_OUT             92
#define ALM_ALC3_UL_OUT             93
#define ALM_ALC4_UL_OUT             94

#define ALM_BAND_CONF_FAIL          95
//SU机型
#define ALM_OVER1_INPUT_POWER	    96
#define ALM_OVER2_INPUT_POWER	    97
#define ALM_OVER3_INPUT_POWER	    98
#define ALM_OVER4_INPUT_POWER	    99
#define ALM_GPS_LOSS				100

//XPRU机型
#define ALM_XP_FAN_DEV_40W		    101

#define ALM_XP_FAN1_HDR_40W			102
#define ALM_XP_FAN2_HDR_40W			103

/* XPRU外部告警预留
#define ALM_XP_EXTER1				104
#define ALM_XP_EXTER2				105
#define ALM_XP_EXTER3				106
#define ALM_XP_EXTER4				107
#define ALM_XP_EXTER5				108
#define ALM_XP_EXTER6				109
#define ALM_XP_EXTER7				110
#define ALM_XP_EXTER8				111
*/
/* N2-RU */
#define ALM_DNOUTPWR5_HIGH          112
#define ALM_DNOUTPWR6_HIGH          113
#define ALM_DNOUTPWR7_HIGH          114
#define ALM_DNOUTPWR8_HIGH          115
#define ALM_DNOUTPWR5_LOW           116
#define ALM_DNOUTPWR6_LOW           117
#define ALM_DNOUTPWR7_LOW           118
#define ALM_DNOUTPWR8_LOW           119
#define ALM_ALC5_UL_OUT             120
#define ALM_ALC6_UL_OUT             121
#define ALM_ALC7_UL_OUT             122
#define ALM_ALC8_UL_OUT             123


#endif
