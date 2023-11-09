//Melo Try onlp test
//This file should not be add in ONL prtoject

#include <stdio.h>
#include <stdlib.h>
#include <string.h>  //for using memset()

#define ONLP_CONFIG_INFO_STR_MAX 64
/**
 * All OIDs have user-level description strings:
 */
#define ONLP_OID_DESC_SIZE 128
#define ONLP_OID_TABLE_SIZE 128
#define ONLP_OID_TYPE_CREATE(_type, _id) ( ( (_type) << 24) | (_id))


//Not in fan.h (Melo)
/** onlp_oid_type */
typedef enum onlp_oid_type_e {
    ONLP_OID_TYPE_SYS = 1,
    ONLP_OID_TYPE_THERMAL = 2,
    ONLP_OID_TYPE_FAN = 3,
    ONLP_OID_TYPE_PSU = 4,
    ONLP_OID_TYPE_LED = 5,
    ONLP_OID_TYPE_MODULE = 6,
    ONLP_OID_TYPE_RTC = 7,
} onlp_oid_type_t;
/* <auto.end.enum(tag:oid).define> */



typedef unsigned int uint32_t;

typedef uint32_t onlp_oid_t;
typedef char onlp_oid_desc_t[ONLP_OID_DESC_SIZE];
typedef onlp_oid_t onlp_oid_table_t[ONLP_OID_TABLE_SIZE];

//Not in fan.h (Melo)S
/**
 * All OID objects contain this header as the first member.
 */
typedef struct onlp_oid_hdr_s {
    /** The OID */
    onlp_oid_t id;
    /** The description of this object. */
    onlp_oid_desc_t description;
    /** The parent OID of this object. */
    onlp_oid_t poid;
    /** The children of this OID */
    onlp_oid_table_t coids;
} onlp_oid_hdr_t;


//In fan.h but not in fani.h (Melo)
typedef enum onlp_fan_mode_e {
    ONLP_FAN_MODE_OFF,
    ONLP_FAN_MODE_SLOW,
    ONLP_FAN_MODE_NORMAL,
    ONLP_FAN_MODE_FAST,
    ONLP_FAN_MODE_MAX,
    ONLP_FAN_MODE_LAST = ONLP_FAN_MODE_MAX,
    ONLP_FAN_MODE_COUNT,
    ONLP_FAN_MODE_INVALID = -1,
} onlp_fan_mode_t;

//Melo Add
const char* fan_mode_to_string(onlp_fan_mode_t mode) {
    switch (mode) {
        case ONLP_FAN_MODE_OFF:
            return "OFF";
        case ONLP_FAN_MODE_SLOW:
            return "SLOW";
        case ONLP_FAN_MODE_NORMAL:
            return "NORMAL";
        case ONLP_FAN_MODE_FAST:
            return "FAST";
        case ONLP_FAN_MODE_MAX:
            return "MAX";
        default:
            return "UNKNOWN";
    }
}


//In fan.h but not in fani.h (Melo)
typedef struct onlp_fan_info_s {
    /** OID Header */
    onlp_oid_hdr_t hdr;

    /* Status */
    uint32_t status;

    /* Capabilities */
    uint32_t caps;

    /* Current fan speed, in RPM, if available */
    int rpm;

    /* Current fan percentage, if available */
    int percentage;

    /* Current fan mode, if available  */
    onlp_fan_mode_t mode;

    /* Model (if applicable) */
    char model[ONLP_CONFIG_INFO_STR_MAX];

    /* Serial Number (if applicable) */
    char serial[ONLP_CONFIG_INFO_STR_MAX];

} onlp_fan_info_t;


// In fani.h but in fan.h (Melo)
extern int onlp_fani_info_get(onlp_oid_t id, onlp_fan_info_t* rv);
// extern int onlp_psui_init(void);
extern int onlp_init(void);
extern int onlp_denit(void);
int main()
{
    printf("START M_fan_test\n");

    printf("START ONLP INITIALIZATION...\n");
    // onlp_psui_init();
    onlp_init();
    printf("ONLP INITIALIZATION DOWN!\n");

    onlp_fan_info_t info = {0};

    printf("START GET FAN INFO\n");
    for(int fan_id = 1; fan_id <= 2; fan_id++){
        printf("Get FAN %d Info...\n", fan_id);

        if(onlp_fani_info_get(ONLP_OID_TYPE_CREATE(ONLP_OID_TYPE_FAN, fan_id), &info) >= 0){
            printf(
                "*********FAN %d OID Header*********\n"
                "ID: %u\n"
                "Description: %s\n"
                "POID: %u\n"
                "COID: %s\n",
                fan_id, info.hdr.id, info.hdr.description, info.hdr.poid, info.hdr.coids
            );

            printf(
                "Status: %u\n"
                "Caps:   %u\n"
                "RPM:    %u\n"
                "Percentage: %d\n"
                "Mode:   %d (%s)\n"
                "Model:    %s\n"
                "Serial No.: %s\n", 
                info.status, info.caps, info.rpm, info.percentage, info.mode, fan_mode_to_string(info.mode), info.model, info.serial
            );

            printf("Get FAN %d Info done!\n", fan_id);
            memset(&info, 0, sizeof(info));
        } 
        else {
            printf("[FAILED!] Failed To Get FAN %d INFO\n", fan_id);
        }
    }
    printf("[DONE] Get FAN INFO Done!]\n");

    onlp_denit();
    return 0;
}


