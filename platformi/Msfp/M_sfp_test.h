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
#include <sys/time.h>
//#include <stdint.h>

typedef unsigned char uint8_t;

typedef enum onlp_status_e {
    ONLP_STATUS_OK = 0,
    ONLP_STATUS_E_GENERIC = -1,
    ONLP_STATUS_E_UNSUPPORTED = -10,
    ONLP_STATUS_E_MISSING = -11,
    ONLP_STATUS_E_INVALID = -12,
    ONLP_STATUS_E_INTERNAL = -13,
    ONLP_STATUS_E_PARAM = -14,
    ONLP_STATUS_E_I2C = -15,
} onlp_status_t;


/* Test funciton */
extern int onlp_sfpi_dom_read(int port, uint8_t data[256]);

extern int onlp_init(void);
extern int onlp_denit(void);