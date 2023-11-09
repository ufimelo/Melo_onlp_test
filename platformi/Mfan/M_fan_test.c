//Melo Try onlp test
//This file should not be add in ONL prtoject

#include <stdio.h>
#include <stdlib.h>

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
    printf("Start M_fan_test");

    printf("Start onlp initialization...");
    // onlp_psui_init();
    onlp_init();
    printf("onlp initialization down!");

    onlp_fan_info_t info = {0};

    printf("Start Get fan Info");
    printf("Get Fan 1 Info");
    onlp_fani_info_get(ONLP_OID_TYPE_CREATE(ONLP_OID_TYPE_FAN, 1), &info);
    printf(
        "Status: %d\n
        Caps:   %d\n
        Mode:   %d\n
        RPM:    %d\n
        Percentage: %d\n", status, caps, mode, rpm, percentage
    );

    printf("Get Fan 2 Info");
    onlp_fani_info_get(ONLP_OID_TYPE_CREATE(ONLP_OID_TYPE_FAN, 2), &info);


    onlp_denit();
    return 0;
}


