#include <stdio.h>
#include <stdlib.h>

#define ONLP_TOTAL_PSU_NUMBER 2
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

typedef struct onlp_psu_info_t {
    /** OID Header */
    onlp_oid_hdr_t hdr;

    /* Model */
    char model[ONLP_CONFIG_INFO_STR_MAX];

    /* Serial Number */
    char serial[ONLP_CONFIG_INFO_STR_MAX];

    /* Status */
    uint32_t status;

    /* Capabilities */
    uint32_t caps;

    /* millivolts */
    int mvin;
    int mvout;

    /* milliamps */
    int miin;
    int miout;

    /* milliwatts */
    int mpin;
    int mpout;

} onlp_psu_info_t;


extern int onlp_psui_info_get(onlp_oid_t id, onlp_psu_info_t* info);
// extern int onlp_psui_init(void);
extern int onlp_init(void);
extern int onlp_denit(void);