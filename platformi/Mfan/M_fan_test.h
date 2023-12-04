/***************************************************
    Melo Try onlp test
    This header file is used in:
        M_fan_test.c
***************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>  //for using memset(), strcat(), strlen()
#include <stdarg.h>
#include <time.h>

#define ONLP_CONFIG_INFO_STR_MAX 64

// printf with timestamp (Melo)
void t_printf(const char* format, ...) {
    time_t timer;
    char buffer[26];
    struct tm* tm_info;

    // 取得時間戳記
    timer = time(NULL);
    tm_info = localtime(&timer);

    // 格式化時間
    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);

    // 印出時間戳記
    printf("[%s] ", buffer);

    // 使用可變引數列表處理訊息
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    printf("\n");
}


//read config file
void readConfigFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[256];

    while (fgets(line, sizeof(line), file)) {
        // Ignore comments and empty lines
        if (line[0] == '#' || line[0] == '\n') {
            continue;
        }

        // Parse each line and extract configuration data
        char *key = strtok(line, "=");
        char *value = strtok(NULL, "=");

        // Remove leading and trailing whitespaces from key and value
        key = strtok(key, " \t\n\r");
        value = strtok(value, " \t\n\r");

        // Process key and value as needed
        printf("Key: %s, Value: %s\n", key, value);
    }

    fclose(file);
}




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
    MMMAX = 5
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
        case ONLP_FAN_MODE_INVALID:
            return "INVALID";
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

//FAN status
typedef enum onlp_fan_status_e {
    ONLP_FAN_STATUS_PRESENT = (1 << 0),
    ONLP_FAN_STATUS_FAILED = (1 << 1),
    ONLP_FAN_STATUS_B2F = (1 << 2),
    ONLP_FAN_STATUS_F2B = (1 << 3),
} onlp_fan_status_t;

//Decode for info.status (by Melo)
const char* fan_status_to_string(uint32_t status){
    static char result[256];
    result[0] = '\0';

    status & ONLP_FAN_STATUS_PRESENT ? strcat(result, "Present, ") : 0;
    status & ONLP_FAN_STATUS_FAILED ? strcat(result, "Absent, ") : 0;
    status & ONLP_FAN_STATUS_B2F ? strcat(result, "B2F ") : 0;
    status & ONLP_FAN_STATUS_F2B ? strcat(result, "F2B ") : 0;

    // Remove trailing space if any
    if (strlen(result) > 0 && result[strlen(result) - 1] == ' ') {
        result[strlen(result) - 1] = '\0';
    }

    return result;
}

// In fani.h but in fan.h (Melo)
extern int onlp_fani_info_get(onlp_oid_t id, onlp_fan_info_t* rv);
// extern int onlp_psui_init(void);
extern int onlp_init(void);
extern int onlp_denit(void);