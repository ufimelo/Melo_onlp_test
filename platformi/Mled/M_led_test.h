/***************************************************
    Melo Try onlp test
    This header file is used in:
        M_led_test.c
***************************************************/


#include <stdio.h>
#include <stdlib.h>

#define ONLP_CONFIG_INFO_STR_MAX 64
/**
 * All OIDs have user-level description strings:
 */
#define ONLP_OID_DESC_SIZE 128
#define ONLP_OID_TABLE_SIZE 128
#define ONLP_OID_TYPE_CREATE(_type, _id) ( ( (_type) << 24) | (_id))

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

typedef enum onlp_led_mode_e {
    ONLP_LED_MODE_OFF,
    ONLP_LED_MODE_ON,
    ONLP_LED_MODE_BLINKING,
    ONLP_LED_MODE_RED = 10,
    ONLP_LED_MODE_RED_BLINKING = 11,
    ONLP_LED_MODE_ORANGE = 12,
    ONLP_LED_MODE_ORANGE_BLINKING = 13,
    ONLP_LED_MODE_YELLOW = 14,
    ONLP_LED_MODE_YELLOW_BLINKING = 15,
    ONLP_LED_MODE_GREEN = 16,
    ONLP_LED_MODE_GREEN_BLINKING = 17,
    ONLP_LED_MODE_BLUE = 18,
    ONLP_LED_MODE_BLUE_BLINKING = 19,
    ONLP_LED_MODE_PURPLE = 20,
    ONLP_LED_MODE_PURPLE_BLINKING = 21,
    ONLP_LED_MODE_AUTO = 22,
    ONLP_LED_MODE_AUTO_BLINKING = 23,
    ONLP_LED_MODE_MAX  //add byMelo
} onlp_led_mode_t;

//Melo Add for messages
const char* led_mode_to_string(onlp_led_mode_t mode) {
    switch (mode) {
        case ONLP_LED_MODE_OFF:
            return "OFF";
        case ONLP_LED_MODE_ON:
            return "ON";
        case ONLP_LED_MODE_BLINKING:
            return "BLINKING";
        case ONLP_LED_MODE_RED:
            return "RED";
        case ONLP_LED_MODE_RED_BLINKING:
            return "RED_BLINKING";
        case ONLP_LED_MODE_ORANGE:
            return "ORANGE";
        case ONLP_LED_MODE_ORANGE_BLINKING:
            return "ORANGE_BLINKING";
        case ONLP_LED_MODE_YELLOW:
            return "YELLOW";
        case ONLP_LED_MODE_YELLOW_BLINKING:
            return "YELLOW_BLINKING";
        case ONLP_LED_MODE_GREEN:
            return "GREEN";
        case ONLP_LED_MODE_GREEN_BLINKING:
            return "GREEN_BLINKING";
        case ONLP_LED_MODE_BLUE:
            return "BLUE";
        case ONLP_LED_MODE_BLUE_BLINKING:
            return "BLUE_BLINKING";
        case ONLP_LED_MODE_PURPLE:
            return "PURPLE";
        case ONLP_LED_MODE_PURPLE_BLINKING:
            return "PURPLE_BLINKING";
        case ONLP_LED_MODE_AUTO:
            return "AUTO";
        case ONLP_LED_MODE_AUTO_BLINKING:
            return "AUTO_BLINKING";
        default:
            return "UNKNOWN";
    }
}


/* led_id */
enum onlp_led_id {
    ONLP_LED_SYS_GNSS = 1,
    ONLP_LED_SYS_SYNC,
    ONLP_LED_SYS_SYS,
    ONLP_LED_SYS_FAN,
    ONLP_LED_SYS_PWR,
    ONLP_LED_FLEXE_0,
    ONLP_LED_FLEXE_1,
    ONLP_LED_MAX
};

//For onlp_led_id cahnge to string (by Melo)
const char* led_id_to_string(enum onlp_led_id id){
    switch (id){
        case ONLP_LED_SYS_GNSS : return "ONLP_LED_SYS_GNSS";
        case ONLP_LED_SYS_SYNC: return "ONLP_LED_SYS_SYNC";
        case ONLP_LED_SYS_SYS : return "ONLP_LED_SYS_SYS";
        case ONLP_LED_SYS_FAN : return "ONLP_LED_SYS_FAN";
        case ONLP_LED_SYS_PWR : return "ONLP_LED_SYS_PWR";
        case ONLP_LED_FLEXE_0 : return "ONLP_LED_FLEXE_0";
        case ONLP_LED_FLEXE_1 : return "ONLP_LED_FLEXE_1";
        default: return "Unknown LED ID";
    }
}

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

/**
 * LED information structure.
 */
typedef struct onlp_led_info_s {
    /** Header */
    onlp_oid_hdr_t hdr;

    /** Status */
    uint32_t status;

    /** Capabilities */
    uint32_t caps;

    /** Current mode, if capable. */
    onlp_led_mode_t mode;

    /** Current char, if capable. */
    char character;

} onlp_led_info_t;



extern int onlp_ledi_info_get(onlp_oid_t id, onlp_led_info_t* rv);
extern int onlp_ledi_status_get(onlp_oid_t id, uint32_t* rv);
extern int onlp_ledi_hdr_get(onlp_oid_t id, onlp_oid_hdr_t* rv);
extern int onlp_ledi_set(onlp_oid_t id, int on_or_off);
extern int onlp_ledi_mode_set(onlp_oid_t id, onlp_led_mode_t mode);


// extern int onlp_psui_init(void);
extern int onlp_init(void);
extern int onlp_denit(void);