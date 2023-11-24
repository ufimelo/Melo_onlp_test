/***************************************************
    Melo Try onlp test
    This header file is used in:
        M_led_test.c
***************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>  //for recognizeing unit32_t
#include "cjson/cJSON.h"  //for reading json file using cJSON library


#define ONLP_CONFIG_INFO_STR_MAX 64
/**
 * All OIDs have user-level description strings:
 */
#define ONLP_OID_DESC_SIZE 128
#define ONLP_OID_TABLE_SIZE 128
#define ONLP_OID_TYPE_CREATE(_type, _id) ( ( (_type) << 24) | (_id))


// Read configure information bu JASON (Melo)
int read_ufi_json(const char *filename){
     // open the file 
    FILE *fp = fopen(filename, "r"); 
    if (fp == NULL) { 
        printf("Error: Unable to open the file %s.\n", filename); 
        return 1; 
    } 
  
    // read the file contents into a string 
    char buffer[1024]; 
    int len = fread(buffer, 1, sizeof(buffer), fp); 
    fclose(fp); 
  
    // parse the JSON data 
    cJSON *json = cJSON_Parse(buffer); 
    if (json == NULL) { 
        const char *error_ptr = cJSON_GetErrorPtr(); 
        if (error_ptr != NULL) { 
            printf("Error: %s\n", error_ptr); 
        } 
        cJSON_Delete(json); 
        return 1; 
    } 
  
    // access the JSON data 
    cJSON *ufi_config = cJSON_GetObjectItemCaseSensitive(json, "platform"); 
    if (cJSON_IsString(ufi_config) && (ufi_config->valuestring != NULL)) { 
        printf("AA: %s\n", ufi_config->valuestring); 
    } 
  
    // delete the JSON object 
    cJSON_Delete(json); 
    return 0; 
}


// onlp_led_status
typedef enum onlp_led_status_e {
    ONLP_LED_STATUS_PRESENT = (1 << 0),
    ONLP_LED_STATUS_FAILED = (1 << 1),
    ONLP_LED_STATUS_ON = (1 << 2),
} onlp_led_status_t;
/* <auto.end.enum(tag:led).define> */

//Decode for info.status (by Melo)
const char* led_status_to_string(uint32_t status){
    static char result[256];
    result[0] = '\0';

    status & ONLP_LED_STATUS_PRESENT ? strcat(result, "Present, ") : 0;
    status & ONLP_LED_STATUS_FAILED ? strcat(result, "Absent. ") : 0;
    status & ONLP_LED_STATUS_ON ? strcat(result, "LED ON ") : 0;
    
    // Remove trailing space if any
    if (strlen(result) > 0 && result[strlen(result) - 1] == ' ') {
        result[strlen(result) - 1] = '\0';
    }

    return result;
}


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
        case ONLP_LED_MODE_OFF:                 return "LED OFF";
        case ONLP_LED_MODE_ON:                  return "LED ON";
        case ONLP_LED_MODE_BLINKING:            return "LED BLINKING";
        case ONLP_LED_MODE_RED:                 return "LED RED";
        case ONLP_LED_MODE_RED_BLINKING:        return "LED RED_BLINKING";
        case ONLP_LED_MODE_ORANGE:              return "LED ORANGE";
        case ONLP_LED_MODE_ORANGE_BLINKING:     return "LED ORANGE_BLINKING";
        case ONLP_LED_MODE_YELLOW:              return "LED YELLOW";
        case ONLP_LED_MODE_YELLOW_BLINKING:     return "LED YELLOW_BLINKING";
        case ONLP_LED_MODE_GREEN:               return "LED GREEN";
        case ONLP_LED_MODE_GREEN_BLINKING:      return "LED GREEN_BLINKING";
        case ONLP_LED_MODE_BLUE:                return "LED BLUE";
        case ONLP_LED_MODE_BLUE_BLINKING:       return "LED BLUE_BLINKING";
        case ONLP_LED_MODE_PURPLE:              return "LED PURPLE";
        case ONLP_LED_MODE_PURPLE_BLINKING:     return "LED PURPLE_BLINKING";
        case ONLP_LED_MODE_AUTO:                return "LED AUTO";
        case ONLP_LED_MODE_AUTO_BLINKING:       return "LED AUTO_BLINKING";
        default:                                return "UNKNOWN";
    }
}


/* led_id */
enum onlp_led_id {
    ONLP_LED_RESERVED  = 0,
    ONLP_LED_SYS_SYNC = 1,
    ONLP_LED_SYS_SYS,
    ONLP_LED_SYS_FAN,
    ONLP_LED_SYS_PSU_0,
    ONLP_LED_SYS_PSU_1,
    ONLP_LED_SYS_ID,
    ONLP_LED_MAX
};

//For onlp_led_id cahnge to string (by Melo)
const char* led_id_to_string(enum onlp_led_id id){
    switch (id){
        case ONLP_LED_RESERVED  :         return  "ONLP_LED_RESERVED";
        case ONLP_LED_SYS_SYNC  :         return  "ONLP_LED_SYS_SYNC";
        case ONLP_LED_SYS_SYS   :         return  "ONLP_LED_SYS_SYS";
        case ONLP_LED_SYS_FAN   :         return  "ONLP_LED_SYS_FAN";
        case ONLP_LED_SYS_PSU_0 :         return  "ONLP_LED_SYS_PSU_0";
        case ONLP_LED_SYS_PSU_1 :         return  "ONLP_LED_SYS_PSU_1";
        case ONLP_LED_SYS_ID    :         return  "ONLP_LED_SYS_ID";
        default                 :         return   "Unknown LED ID";
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