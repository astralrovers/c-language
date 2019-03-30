#include <stdio.h>
#include <stdbool.h>
#include "alarm_id_table.h"
#include "sunwave_alarm.h"

#ifndef INVALID_ALARM_ID
#define INVALID_ALARM_ID    0xff
#endif

ALM_INFO master_au_alarm_id[] = {	
    {ALM_POWER_DOWN,        "Power Interruption Alarm" ,    0x0201,   0x0301},
    {ALM_BATTERT_FAULT,     "Battery Failure Alarm",        0x0204,   0x0304},
    {ALM_LOCATION,          "Movement Alarm",               0x0205,   0x0305},
    {ALM_TEMP,              "Over-temperature Alarm",       0x0206,   0x0306}, 
    {ALM_PLL1_UNLOCLK,      "LO1 Unlocked Alarm",           0x0260,   0x0360},
    {ALM_PLL2_UNLOCLK,      "LO2 Unlocked Alarm",           0x0261,   0x0361},
    {ALM_PLL3_UNLOCLK,      "LO3 Unlocked Alarm",           0x0262,   0x0362},
    {ALM_PLL4_UNLOCLK,      "LO4 Unlocked Alarm",           0x0263,   0x0363},

    {ALM_OPT1_LIGHT,        "OP1 Transceiver Failure Alarm",    0x02A0,     0x03A0}, 
    {ALM_OPT2_LIGHT,        "OP2 Transceiver Failure Alarm",    0x02A1,     0x03A1},  
    {ALM_OPT3_LIGHT,        "OP3 Transceiver Failure Alarm",    0x02A2,     0x03A2}, 
    {ALM_OPT4_LIGHT,        "OP4 Transceiver Failure Alarm",    0x02A3,     0x03A3}, 
    {ALM_OPT5_LIGHT,        "OP5 Transceiver Failure Alarm",    0x02A6,     0x03A6},
    {ALM_OPT6_LIGHT,        "OP6 Transceiver Failure Alarm",    0x02A7,     0x03A7}, 
    {ALM_OPT7_LIGHT,        "OP-AU1 Transceiver Failure Alarm",    0x02A4,     0x03A4},
    {ALM_OPT8_LIGHT,        "OP-AU2 Transceiver Failure Alarm",    0x02A5,     0x03A5},

    {ALM_EXT_1,             "External Alarm 1",                  0x0220,     0x0320},
    {ALM_EXT_2,             "External Alarm 2",                  0x0221,     0x0321},    
    {ALM_EXT_3,             "External Alarm 3",                  0x0222,     0x0322},       
    {ALM_EXT_4,             "External Alarm 4",                  0x0223,     0x0323},      
    {ALM_DOOR,              "Open Case Alarm",                   0x0228,     0x0328},
    {ALM_ALC1_OUT,          "Module1 DL ALC Over Range Alarm",    0x0264,     0x0364},
    {ALM_ALC2_OUT,          "Module2 DL ALC Over Range Alarm",    0x0265,     0x0365},
    {ALM_ALC3_OUT,          "Module3 DL ALC Over Range Alarm",    0x0266,     0x0366},
    {ALM_ALC4_OUT,          "Module4 DL ALC Over Range Alarm",    0x0267,     0x0367},

    {CHAN1PORT1_DLINPOWERUNDER,             "Module1 Port1 DL Under Input-power Alarm",    0X0240,     0X0340},
    {CHAN1PORT2_DLINPOWERUNDER,             "Module1 Port2 DL Under Input-power Alarm",    0X0241,     0X0341},
    {CHAN1PORT3_DLINPOWERUNDER,             "Module1 Port3 DL Under Input-power Alarm",    0X0242,     0X0342},
    {CHAN1PORT4_DLINPOWERUNDER,             "Module1 Port4 DL Under Input-power Alarm",    0X0243,     0X0343},
    {CHAN1PORT1_DLINPOWEROVER,              "Module1 Port1 DL Over Input-power Alarm" ,    0X0244,     0X0344},
    {CHAN1PORT2_DLINPOWEROVER,              "Module1 Port2 DL Over Input-power Alarm" ,    0X0245,     0X0345},
    {CHAN1PORT3_DLINPOWEROVER,              "Module1 Port3 DL Over Input-power Alarm" ,    0X0246,     0X0346},
    {CHAN1PORT4_DLINPOWEROVER,              "Module1 Port4 DL Over Input-power Alarm" ,    0X0247,     0X0347},

    {CHAN2PORT1_DLINPOWERUNDER,             "Module2 Port1 DL Under Input-power Alarm",    0X0248,     0X0348},
    {CHAN2PORT2_DLINPOWERUNDER,             "Module2 Port2 DL Under Input-power Alarm",    0X0249,     0X0349},
    {CHAN2PORT3_DLINPOWERUNDER,             "Module2 Port3 DL Under Input-power Alarm",    0X024A,     0X034A},
    {CHAN2PORT4_DLINPOWERUNDER,             "Module2 Port4 DL Under Input-power Alarm",    0X024B,     0X034B},
    {CHAN2PORT1_DLINPOWEROVER,              "Module2 Port1 DL Over Input-power Alarm" ,    0X024C,     0X034C},
    {CHAN2PORT2_DLINPOWEROVER,              "Module2 Port2 DL Over Input-power Alarm" ,    0X024D,     0X034D},
    {CHAN2PORT3_DLINPOWEROVER,              "Module2 Port3 DL Over Input-power Alarm" ,    0X024E,     0X034E},
    {CHAN2PORT4_DLINPOWEROVER,              "Module2 Port4 DL Over Input-power Alarm" ,    0X024F,     0X034F},

    {CHAN3PORT1_DLINPOWERUNDER,             "Module3 Port1 DL Under Input-power Alarm",    0X0250,     0X0350},
    {CHAN3PORT2_DLINPOWERUNDER,             "Module3 Port2 DL Under Input-power Alarm",    0X0251,     0X0351},
    {CHAN3PORT3_DLINPOWERUNDER,             "Module3 Port3 DL Under Input-power Alarm",    0X0252,     0X0352},
    {CHAN3PORT4_DLINPOWERUNDER,             "Module3 Port4 DL Under Input-power Alarm",    0X0253,     0X0353},
    {CHAN3PORT1_DLINPOWEROVER,              "Module3 Port1 DL Over Input-power Alarm" ,    0X0254,     0X0354},
    {CHAN3PORT2_DLINPOWEROVER,              "Module3 Port2 DL Over Input-power Alarm" ,    0X0255,     0X0355},
    {CHAN3PORT3_DLINPOWEROVER,              "Module3 Port3 DL Over Input-power Alarm" ,    0X0256,     0X0356},
    {CHAN3PORT4_DLINPOWEROVER,              "Module3 Port4 DL Over Input-power Alarm" ,    0X0257,     0X0357},

    {CHAN4PORT1_DLINPOWERUNDER,             "Module4 Port1 DL Under Input-power Alarm",    0X0258,     0X0358},
    {CHAN4PORT2_DLINPOWERUNDER,             "Module4 Port2 DL Under Input-power Alarm",    0X0259,     0X0359},
    {CHAN4PORT3_DLINPOWERUNDER,             "Module4 Port3 DL Under Input-power Alarm",    0X025A,     0X035A},
    {CHAN4PORT4_DLINPOWERUNDER,             "Module4 Port4 DL Under Input-power Alarm",    0X025B,     0X035B},
    {CHAN4PORT1_DLINPOWEROVER,              "Module4 Port1 DL Over Input-power Alarm" ,    0X025C,     0X035C},
    {CHAN4PORT2_DLINPOWEROVER,              "Module4 Port2 DL Over Input-power Alarm" ,    0X025D,     0X035D},
    {CHAN4PORT3_DLINPOWEROVER,              "Module4 Port3 DL Over Input-power Alarm" ,    0X025E,     0X035E},
    {CHAN4PORT4_DLINPOWEROVER,              "Module4 Port4 DL Over Input-power Alarm" ,    0X025F,     0X035F},

    {ALM_BAND_CONF_FAIL,                    "Band Configuration Failure Alarm",            0X023A,     0X033A},
    {INVALID_ALARM_ID}
};

uint8_t master_alarm_num(void)
{
    return sizeof(master_au_alarm_id)/sizeof(master_au_alarm_id[0])-1;
}


/*alarm table of slave Au*/
ALM_INFO slave_au_alarm_id[] = {	
    {ALM_LOCATION  ,        "Movement Alarm"            ,    0x0205,     0x0305},
    {ALM_TEMP,              "Over-temperature Alarm"    ,    0x0206,     0x0306},   
    {ALM_SLV_LINK_FAIL,     "Link Alarm"                ,    0x020F,     0x030F},    
    {ALM_PLL1_UNLOCLK,      "LO1 Unlocked Alarm"        ,    0x0260,     0x0360},
    {ALM_PLL2_UNLOCLK,      "LO2 Unlocked Alarm"        ,    0x0261,     0x0361},
    {ALM_PLL3_UNLOCLK,      "LO3 Unlocked Alarm"        ,    0x0262,     0x0362},
    {ALM_PLL4_UNLOCLK,      "LO4 Unlocked Alarm"        ,    0x0263,     0x0363},

    {ALM_OPT1_LIGHT,        "OP1 Transceiver Failure Alarm",          0x02A0,     0x03A0},
    {ALM_DOOR,              "Open Case Alarm"          ,     0x0228,     0x0328},
    {ALM_EXT_1,             "External Alarm 1"          ,    0x0220,     0x0320},
    {ALM_EXT_2,             "External Alarm 2"          ,    0x0221,     0x0321},    
    {ALM_EXT_3,             "External Alarm 3"          ,    0x0222,     0x0322},       
    {ALM_EXT_4,             "External Alarm 4"          ,    0x0223,     0x0323},
    {ALM_ALC1_OUT,          "Module1 DL ALC Over Range Alarm" ,       0x0264,     0x0364},
    {ALM_ALC2_OUT,          "Module2 DL ALC Over Range Alarm" ,       0x0265,     0x0365},
    {ALM_ALC3_OUT,          "Module3 DL ALC Over Range Alarm" ,       0x0266,     0x0366},
    {ALM_ALC4_OUT,          "Module4 DL ALC Over Range Alarm" ,       0x0267,     0x0367},

    {CHAN1PORT1_DLINPOWERUNDER,             "Module1 Port1 DL Under Input-power Alarm",    0X0240,     0X0340},
    {CHAN1PORT2_DLINPOWERUNDER,             "Module1 Port2 DL Under Input-power Alarm",    0X0241,     0X0341},
    {CHAN1PORT3_DLINPOWERUNDER,             "Module1 Port3 DL Under Input-power Alarm",    0X0242,     0X0342},
    {CHAN1PORT4_DLINPOWERUNDER,             "Module1 Port4 DL Under Input-power Alarm",    0X0243,     0X0343},
    {CHAN1PORT1_DLINPOWEROVER,              "Module1 Port1 DL Over Input-power Alarm" ,    0X0244,     0X0344},
    {CHAN1PORT2_DLINPOWEROVER,              "Module1 Port2 DL Over Input-power Alarm" ,    0X0245,     0X0345},
    {CHAN1PORT3_DLINPOWEROVER,              "Module1 Port3 DL Over Input-power Alarm" ,    0X0246,     0X0346},
    {CHAN1PORT4_DLINPOWEROVER,              "Module1 Port4 DL Over Input-power Alarm" ,    0X0247,     0X0347},

    {CHAN2PORT1_DLINPOWERUNDER,             "Module2 Port1 DL Under Input-power Alarm",    0X0248,     0X0348},
    {CHAN2PORT2_DLINPOWERUNDER,             "Module2 Port2 DL Under Input-power Alarm",    0X0249,     0X0349},
    {CHAN2PORT3_DLINPOWERUNDER,             "Module2 Port3 DL Under Input-power Alarm",    0X024A,     0X034A},
    {CHAN2PORT4_DLINPOWERUNDER,             "Module2 Port4 DL Under Input-power Alarm",    0X024B,     0X034B},
    {CHAN2PORT1_DLINPOWEROVER,              "Module2 Port1 DL Over Input-power Alarm" ,    0X024C,     0X034C},
    {CHAN2PORT2_DLINPOWEROVER,              "Module2 Port2 DL Over Input-power Alarm" ,    0X024D,     0X034D},
    {CHAN2PORT3_DLINPOWEROVER,              "Module2 Port3 DL Over Input-power Alarm" ,    0X024E,     0X034E},
    {CHAN2PORT4_DLINPOWEROVER,              "Module2 Port4 DL Over Input-power Alarm" ,    0X024F,     0X034F},

    {CHAN3PORT1_DLINPOWERUNDER,             "Module3 Port1 DL Under Input-power Alarm",    0X0250,     0X0350},
    {CHAN3PORT2_DLINPOWERUNDER,             "Module3 Port2 DL Under Input-power Alarm",    0X0251,     0X0351},
    {CHAN3PORT3_DLINPOWERUNDER,             "Module3 Port3 DL Under Input-power Alarm",    0X0252,     0X0352},
    {CHAN3PORT4_DLINPOWERUNDER,             "Module3 Port4 DL Under Input-power Alarm",    0X0253,     0X0353},
    {CHAN3PORT1_DLINPOWEROVER,              "Module3 Port1 DL Over Input-power Alarm" ,    0X0254,     0X0354},
    {CHAN3PORT2_DLINPOWEROVER,              "Module3 Port2 DL Over Input-power Alarm" ,    0X0255,     0X0355},
    {CHAN3PORT3_DLINPOWEROVER,              "Module3 Port3 DL Over Input-power Alarm" ,    0X0256,     0X0356},
    {CHAN3PORT4_DLINPOWEROVER,              "Module3 Port4 DL Over Input-power Alarm" ,    0X0257,     0X0357},

    {CHAN4PORT1_DLINPOWERUNDER,             "Module4 Port1 DL Under Input-power Alarm",    0X0258,     0X0358},
    {CHAN4PORT2_DLINPOWERUNDER,             "Module4 Port2 DL Under Input-power Alarm",    0X0259,     0X0359},
    {CHAN4PORT3_DLINPOWERUNDER,             "Module4 Port3 DL Under Input-power Alarm",    0X025A,     0X035A},
    {CHAN4PORT4_DLINPOWERUNDER,             "Module4 Port4 DL Under Input-power Alarm",    0X025B,     0X035B},
    {CHAN4PORT1_DLINPOWEROVER,              "Module4 Port1 DL Over Input-power Alarm" ,    0X025C,     0X035C},
    {CHAN4PORT2_DLINPOWEROVER,              "Module4 Port2 DL Over Input-power Alarm" ,    0X025D,     0X035D},
    {CHAN4PORT3_DLINPOWEROVER,              "Module4 Port3 DL Over Input-power Alarm" ,    0X025E,     0X035E},
    {CHAN4PORT4_DLINPOWEROVER,              "Module4 Port4 DL Over Input-power Alarm" ,    0X025F,     0X035F},
    {INVALID_ALARM_ID}

};
/*alarm table of Eu*/
ALM_INFO slave_eu_alarm_id[] = {	
    {ALM_POWER_DOWN,        "Power Interruption Alarm",     0x0201,     0x0301},
    {ALM_LOCATION  ,        "Movement Alarm"          ,     0x0205,     0x0305},
    {ALM_TEMP,              "Over-temperature Alarm"  ,     0x0206,     0x0306},   
    {ALM_SLV_LINK_FAIL,     "Link Alarm"              ,     0x020F,     0x030F},    
    {ALM_OPT1_LIGHT,        "OP1 Transceiver Failure Alarm",     0x02A0,     0x03A0},
    {ALM_OPT2_LIGHT,        "OP2 Transceiver Failure Alarm",     0x02A1,     0x03A1},
    {ALM_OPT3_LIGHT,        "OP3 Transceiver Failure Alarm",     0x02A2,     0x03A2},
    {ALM_OPT4_LIGHT,        "OP4 Transceiver Failure Alarm",     0x02A3,     0x03A3},
    {ALM_OPT5_LIGHT,        "OP5 Transceiver Failure Alarm",     0x02A6,     0x03A6},
    {ALM_OPT6_LIGHT,        "OP6 Transceiver Failure Alarm",     0x02A7,     0x03A7},
    {ALM_OPT_IN,            "OP-slave Transceiver Failure Alarm",     0x02A8,     0x03A8},
    {ALM_OPT_OUT,           "OP-master Transceiver Failure Alarm"  ,     0x02A9,     0x03A9},
    {ALM_DOOR,              "Open Case Alarm"              ,     0x0228,     0x0328},
    {ALM_OPT_SWITCH,        "Optical Port Switch Alarm"    ,     0x0207,     0x0307},
    {INVALID_ALARM_ID}
};
/*alarm table of Ru*/
ALM_INFO slave_ru_alarm_id[] = {	
    {ALM_POWER_DOWN,        "Power Interruption Alarm"  ,       0x0201,     0x0301},
    {ALM_LOCATION  ,        "Movement Alarm"            ,       0x0205,     0x0305},
    {ALM_TEMP,              "Over-temperature Alarm"    ,       0x0206,     0x0306},   
    {ALM_SLV_LINK_FAIL,     "Link Alarm"                ,       0x020F,     0x030F},    
    {ALM_PLL1_UNLOCLK,      "LO1 Unlocked Alarm"        ,       0x0260,     0x0360},
    {ALM_PLL2_UNLOCLK,      "LO2 Unlocked Alarm"        ,       0x0261,     0x0361},
    {ALM_PLL3_UNLOCLK,      "LO3 Unlocked Alarm"        ,       0x0262,     0x0362},
    {ALM_PLL4_UNLOCLK,      "LO4 Unlocked Alarm"        ,       0x0263,     0x0363},

    {ALM_OPT_IN,            "OP-slave Transceiver Failure Alarm",      0x02A8,     0x03A8},   
    {ALM_OPT_OUT,           "OP-master Transceiver Failure Alarm",     0x02A9,     0x03A9},
    {ALM_DNOUTPWR1_HIGH,    "Module1 DL Over Output-power Alar",   0x0232,     0x0332},
    {ALM_DNOUTPWR2_HIGH,    "Module2 DL Over Output-power Alar",   0x0238,     0x0338},
    {ALM_DNOUTPWR3_HIGH,    "Module3 DL Over Output-power Alar",   0x023E,     0x033E},
    {ALM_DNOUTPWR4_HIGH,    "Module4 DL Over Output-power Alar",   0x026a,     0x036a},

    {ALM_DNOUTPWR1_LOW,     "Module1 DL Under Output-power Alarm",  0x0233,     0x0333},
    {ALM_DNOUTPWR2_LOW,     "Module2 DL Under Output-power Alarm",  0x0239,     0x0339},
    {ALM_DNOUTPWR3_LOW,     "Module3 DL Under Output-power Alarm",  0x023F,     0x033F},
    {ALM_DNOUTPWR4_LOW,     "Module4 DL Under Output-power Alarm",  0x026b,     0x036b},
    {ALM_DOOR,              "Open Case Alarm"          ,            0x0228,     0x0328},



    {ALM_ALC1_UL_OUT,       "Module1 UL ALC Over Range Alarm",      0x0264,     0x0364},
    {ALM_ALC2_UL_OUT,       "Module2 UL ALC Over Range Alarm",      0x0265,     0x0365},
    {ALM_ALC3_UL_OUT,       "Module3 UL ALC Over Range Alarm",      0x0266,     0x0366},
    {ALM_ALC4_UL_OUT,       "Module4 UL ALC Over Range Alarm",      0x0267,     0x0367},
    {ALM_OPT_SWITCH,        "Optical Port Switch Alarm"    ,     0x0207,     0x0307},
    {INVALID_ALARM_ID}

};

/*alarm table of HRu*/

ALM_INFO slave_hru_alarm_id[] = {	
    {ALM_POWER_DOWN,        "Power Interruption Alarm"  ,   0x0201,     0x0301},
    {ALM_LOCATION  ,        "Movement Alarm"            ,   0x0205,     0x0305},
    {ALM_TEMP,              "Over-temperature Alarm"    ,   0x0206,     0x0306},     

    {ALM_SLV_LINK_FAIL,     "Link Alarm"                ,   0x020F,     0x030F},    
    {ALM_PLL1_UNLOCLK,      "LO1 Unlocked Alarm"        ,   0x0260,     0x0360},
    {ALM_PLL2_UNLOCLK,      "LO2 Unlocked Alarm"        ,   0x0261,     0x0361},

    {ALM_OPT_IN,            "OP-slave Transceiver Failure Alarm", 0x02A8,     0x03A8},   
    {ALM_OPT_OUT,           "OP-master Transceiver Failure Alarm",  0x02A9,     0x03A9},
    {ALM_DNOUTPWR1_HIGH,    "Module1 DL Over Output-power Alarm",   0x0232,     0x0332},
    {ALM_DNOUTPWR2_HIGH,    "Module2 DL Over Output-power Alarm",   0x0238,     0x0338},
    {ALM_DNOUTPWR1_LOW,     "Module1 DL Under Output-power Alarm",  0x0233,     0x0333},
    {ALM_DNOUTPWR2_LOW,     "Module2 DL Under Output-power Alarm",  0x0239,     0x0339},
    {ALM_DOOR,              "Open Case Alarm"          ,        0x0228,     0x0328},

    {ALM_VSW1,              "Module1 VSWR Alarm"          ,        0x021E,     0x031E},
    {ALM_VSW2,              "Module2 VSWR Alarm"          ,        0x021F,     0x031F},
    {ALM_ALC1_UL_OUT,       "Module1 UL ALC Over Range Alarm",    0x0264,     0x0364},
    {ALM_ALC2_UL_OUT,       "Module2 UL ALC Over Range Alarm",    0x0265,     0x0365},

    {ALM_OPT_SWITCH,        "Optical Port Switch Alarm"    ,     0x0207,     0x0307},
    {INVALID_ALARM_ID}

};

/*alarm table of MRu*/

ALM_INFO slave_mru_alarm_id[] = {	
    {ALM_POWER_DOWN,        "Power Interruption Alarm"  ,    0x0201,     0x0301},
    {ALM_LOCATION  ,        "Movement Alarm"            ,    0x0205,     0x0305},
    {ALM_TEMP,              "Over-temperature Alarm"    ,    0x0206,     0x0306},     
    {ALM_SLV_LINK_FAIL,     "Link Alarm"                ,    0x020F,     0x030F},    
    {ALM_PLL1_UNLOCLK,      "LO1 Unlocked Alarm"        ,    0x0260,     0x0360},

    {ALM_OPT_IN,            "OP-slave Transceiver Failure Alarm",     0x02A8,     0x03A8},   
    {ALM_OPT_OUT,           "OP-master Transceiver Failure Alarm",    0x02A9,     0x03A9},
    {ALM_DNOUTPWR1_HIGH,    "Module1 DL Over Output-power Alarm",      0x0232,     0x0332},
    {ALM_DNOUTPWR1_LOW,     "Module1 DL Under Output-power Alarm",    0x0233,     0x0333},
    {ALM_DOOR,              "Open Case Alarm"          ,              0x0228,     0x0328},


    {ALM_VSW1,              "Module1 VSWR Alarm"          ,           0x021E,     0x031E},
    {ALM_ALC1_UL_OUT,       "Module1 UL ALC Over Range Alarm"  ,      0x0264,     0x0364},

    {ALM_OPT_SWITCH,        "Optical Port Switch Alarm"    ,     0x0207,     0x0307},
    {INVALID_ALARM_ID}

};
ALM_INFO slave_su_alarm_id[] = {	
    {ALM_LOCATION  ,        "Movement Alarm"            ,    0x0205,     0x0305},
    {ALM_TEMP,              "Over-temperature Alarm"    ,    0x0206,     0x0306},
    {ALM_SLV_LINK_FAIL,     "Link Alarm"                ,    0x020F,     0x030F},
    {ALM_PLL1_UNLOCLK,      "LO1 Unlocked Alarm"        ,       0x0260,     0x0360},
    {ALM_PLL2_UNLOCLK,      "LO2 Unlocked Alarm"        ,       0x0261,     0x0361},
    {ALM_PLL3_UNLOCLK,      "LO3 Unlocked Alarm"        ,       0x0262,     0x0362},
    {ALM_PLL4_UNLOCLK,      "LO4 Unlocked Alarm"        ,       0x0263,     0x0363},
    {ALM_OPT1_LIGHT,        "OP1 Transceiver Failure Alarm",    0x02A0,     0x03A0},
    {ALM_DOOR,              "Open Case Alarm"          ,              0x0228,     0x0328},

    {ALM_OPT_SWITCH,        "Optical Port Switch Alarm"    ,     0x0207,     0x0307},
    {ALM_OVER1_INPUT_POWER,	"Module1 Over Input-power Alarm",	0x0268,	0x0368},
    {ALM_OVER2_INPUT_POWER,	"Module2 Over Input-power Alarm",	0x0269,	0x0369},
    {ALM_OVER3_INPUT_POWER,	"Module3 Over Input-power Alarm",	0x026A,	0x036A},
    {ALM_OVER4_INPUT_POWER,	"Module4 Over Input-power Alarm",	0x026B,	0x036B},
    {ALM_GPS_LOSS,		"GPS Loss Alarm",				0x0284,	0x0384},
    {INVALID_ALARM_ID}
};
/*alarm table of XRu*/

ALM_INFO slave_xru_alarm_id[] = {	
    {ALM_POWER_DOWN,        "Power Interruption Alarm"  ,   0x0201,     0x0301},
    {ALM_LOCATION  ,        "Movement Alarm"            ,   0x0205,     0x0305},
    {ALM_TEMP,              "Over-temperature Alarm"    ,   0x0206,     0x0306},     

    {ALM_SLV_LINK_FAIL,     "Link Alarm"                ,   0x020F,     0x030F},    
    {ALM_PLL1_UNLOCLK,      "LO1 Unlocked Alarm"        ,   0x0260,     0x0360},
    {ALM_PLL2_UNLOCLK,      "LO2 Unlocked Alarm"        ,   0x0261,     0x0361},

    {ALM_OPT_IN,            "OP-slave Transceiver Failure Alarm", 0x02A8,     0x03A8},   
    {ALM_OPT_OUT,           "OP-master Transceiver Failure Alarm",  0x02A9,     0x03A9},
    {ALM_DNOUTPWR1_HIGH,    "Module1 DL Over Output-power Alarm",   0x0232,     0x0332},
    {ALM_DNOUTPWR2_HIGH,    "Module2 DL Over Output-power Alarm",   0x0238,     0x0338},
    {ALM_DNOUTPWR1_LOW,     "Module1 DL Under Output-power Alarm",  0x0233,     0x0333},
    {ALM_DNOUTPWR2_LOW,     "Module2 DL Under Output-power Alarm",  0x0239,     0x0339},
    {ALM_DOOR,              "Open Case Alarm"          ,        0x0228,     0x0328},

    {ALM_VSW1,              "Module1 VSWR Alarm"          ,        0x021E,     0x031E},
    {ALM_VSW2,              "Module2 VSWR Alarm"          ,        0x021F,     0x031F},
    {ALM_ALC1_UL_OUT,       "Module1 UL ALC Over Range Alarm",    0x0264,     0x0364},
    {ALM_ALC2_UL_OUT,       "Module2 UL ALC Over Range Alarm",    0x0265,     0x0365},

    {ALM_OPT_SWITCH,        "Optical Port Switch Alarm"    ,     0x0207,     0x0307},

    {ALM_XP_FAN_DEV_40W,        "Fan Device Loss Alarm"    ,     0x0270,     0x0370},
    /*
       {ALM_XP_FAN1_HDR_40W,        "Fan 1 Out Of Control Alarm"    ,     0x0271,     0x0371},
       {ALM_XP_FAN2_HDR_40W,        "Fan 2 Out Of Control Alarm"    ,     0x0272,     0x0372},
       {ALM_XP_EXTER1,        "External Alarm 1"    ,     0x0273,     0x0373},
       {ALM_XP_EXTER2,        "External Alarm 2"    ,     0x0274,     0x0374},
       {ALM_XP_EXTER3,        "External Alarm 3"    ,     0x0275,     0x0375},
       {ALM_XP_EXTER4,        "External Alarm 4"    ,     0x0276,     0x0376},
       {ALM_XP_EXTER5,        "External Alarm 5"    ,     0x0277,     0x0377},
       {ALM_XP_EXTER6,        "External Alarm 6"    ,     0x0278,     0x0378},
       {ALM_XP_EXTER7,        "External Alarm 7"    ,     0x0279,     0x0379},
       {ALM_XP_EXTER8,        "External Alarm 8"    ,     0x027A,     0x037A}
       */
    {INVALID_ALARM_ID}
};

ALM_INFO n2ru_alarm_id[] = {	
    {ALM_TEMP,              "Over-temperature Alarm",               0x0206,     0x0306},     
    {ALM_SLV_LINK_FAIL,     "Link Alarm",                           0x020F,     0x030F},    
    {ALM_OPT_IN,            "OP-slave Transceiver Failure Alarm",   0x02A8,     0x03A8},   
    {ALM_OPT_OUT,           "OP-master Transceiver Failure Alarm",  0x02A9,     0x03A9},
    {ALM_DNOUTPWR1_HIGH,    "Module1 DL Over Output-power Alar",    0x0232,     0x0332},
    {ALM_DNOUTPWR2_HIGH,    "Module2 DL Over Output-power Alar",    0x0238,     0x0338},
    {ALM_DNOUTPWR3_HIGH,    "Module3 DL Over Output-power Alar",    0x023E,     0x033E},
    {ALM_DNOUTPWR4_HIGH,    "Module4 DL Over Output-power Alar",    0x026a,     0x036a},
    {ALM_DNOUTPWR1_LOW,     "Module1 DL Under Output-power Alarm",  0x0233,     0x0333},
    {ALM_DNOUTPWR2_LOW,     "Module2 DL Under Output-power Alarm",  0x0239,     0x0339},
    {ALM_DNOUTPWR3_LOW,     "Module3 DL Under Output-power Alarm",  0x023f,     0x033f},
    {ALM_DNOUTPWR4_LOW,     "Module4 DL Under Output-power Alarm",  0x026b,     0x036b},
    {ALM_ALC1_UL_OUT,       "Module1 UL ALC Over Range Alarm",      0x0264,     0x0364},
    {ALM_ALC2_UL_OUT,       "Module2 UL ALC Over Range Alarm",      0x0265,     0x0365},
    {ALM_ALC3_UL_OUT,       "Module3 UL ALC Over Range Alarm",      0x0266,     0x0366},
    {ALM_ALC4_UL_OUT,       "Module4 UL ALC Over Range Alarm",      0x0267,     0x0367},
    {ALM_XP_FAN_DEV_40W,    "Fan Device Loss Alarm",                0x0270,     0x0370},
    {ALM_DNOUTPWR5_HIGH,    "Module5 DL Over Output-power Alar",    0x02be,     0x03be},
    {ALM_DNOUTPWR6_HIGH,    "Module6 DL Over Output-power Alar",    0x02bf,     0x03bf},
    {ALM_DNOUTPWR7_HIGH,    "Module7 DL Over Output-power Alar",    0x02c1,     0x03c1},
    {ALM_DNOUTPWR8_HIGH,    "Module8 DL Over Output-power Alar",    0x02c3,     0x03c3},
    {ALM_DNOUTPWR5_LOW,     "Module5 DL Under Output-power Alarm",  0x02b9,     0x03b9},
    {ALM_DNOUTPWR6_LOW,     "Module6 DL Under Output-power Alarm",  0x02ba,     0x03ba},
    {ALM_DNOUTPWR7_LOW,     "Module7 DL Under Output-power Alarm",  0x02bb,     0x03bb},
    {ALM_DNOUTPWR8_LOW,     "Module8 DL Under Output-power Alarm",  0x02bd,     0x03bd},
    {ALM_ALC5_UL_OUT,       "Module5 UL ALC Over Range Alarm",      0x029b,     0x039b},
    {ALM_ALC6_UL_OUT,       "Module6 UL ALC Over Range Alarm",      0x029c,     0x039c},
    {ALM_ALC7_UL_OUT,       "Module7 UL ALC Over Range Alarm",      0x029d,     0x039d},
    {ALM_ALC8_UL_OUT,       "Module8 UL ALC Over Range Alarm",      0x029e,     0x039e},
    {INVALID_ALARM_ID}
};

ALM_INFO h2ru_alarm_id[] = {	
    {ALM_POWER_DOWN,        "Power Interruption Alarm"  ,   0x0201,     0x0301},
    {ALM_LOCATION  ,        "Movement Alarm"            ,   0x0205,     0x0305},
    {ALM_TEMP,              "Over-temperature Alarm"    ,   0x0206,     0x0306},

    {ALM_SLV_LINK_FAIL,     "Link Alarm"                ,   0x020F,     0x030F},
    //    {ALM_PLL1_UNLOCLK,      "LO1 Unlocked Alarm"        ,   0x0260,     0x0360},
    //    {ALM_PLL2_UNLOCLK,      "LO2 Unlocked Alarm"        ,   0x0261,     0x0361},

    {ALM_OPT_IN,            "OP-slave Transceiver Failure Alarm", 0x02A8,     0x03A8},
    {ALM_OPT_OUT,           "OP-master Transceiver Failure Alarm",  0x02A9,     0x03A9},
    {ALM_DNOUTPWR1_HIGH,    "Module1 DL Over Output-power Alarm",   0x0232,     0x0332},
    {ALM_DNOUTPWR2_HIGH,    "Module2 DL Over Output-power Alarm",   0x0238,     0x0338},
    {ALM_DNOUTPWR1_LOW,     "Module1 DL Under Output-power Alarm",  0x0233,     0x0333},
    {ALM_DNOUTPWR2_LOW,     "Module2 DL Under Output-power Alarm",  0x0239,     0x0339},
    {ALM_DOOR,              "Open Case Alarm"          ,        0x0228,     0x0328},

    {ALM_VSW1,              "Module1 VSWR Alarm"          ,        0x021E,     0x031E},
    {ALM_VSW2,              "Module2 VSWR Alarm"          ,        0x021F,     0x031F},
    {ALM_ALC1_UL_OUT,       "Module1 UL ALC Over Range Alarm",    0x0264,     0x0364},
    {ALM_ALC2_UL_OUT,       "Module2 UL ALC Over Range Alarm",    0x0265,     0x0365},

    {ALM_OPT_SWITCH,        "Optical Port Switch Alarm"    ,     0x0207,     0x0307},
    {INVALID_ALARM_ID}
};
