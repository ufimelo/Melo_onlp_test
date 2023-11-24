/***************************************************
    Melo Try onlp test
    This file should not be add in ONL prtoject
***************************************************/
#include "M_led_test.h"

int main()
{
    read_ufi_json();
    
    printf("[START] START M_led_test!        \n");

    printf("START ONLP INITIALIZATION...        \n");
    onlp_init();
    onlp_led_info_t info = {0};
    onlp_oid_hdr_t hdr = {0};
    unsigned int rv = 0;

    printf("START GET LED INFO!      \n");
    //1. onlp_ledi_info_get(ONLP_OID_TYPE_CREATE(ONLP_OID_TYPE_LED, ONLP_LED_SYS_SYS), &info);
    //onlp_ledi_status_get(ONLP_OID_TYPE_CREATE(ONLP_OID_TYPE_LED, ONLP_LED_SYS_SYS), &rv);
    //onlp_ledi_hdr_get(ONLP_OID_TYPE_CREATE(ONLP_OID_TYPE_LED, ONLP_LED_SYS_SYS), &hdr);
    //onlp_ledi_set(ONLP_OID_TYPE_CREATE(ONLP_OID_TYPE_LED, ONLP_LED_SYS_SYS), 1);
    //2. onlp_ledi_mode_set(ONLP_OID_TYPE_CREATE(ONLP_OID_TYPE_LED, ONLP_LED_SYS_SYS), ONLP_LED_MODE_YELLOW_BLINKING);


    //1. check onlp_ledi_info_get() API
    printf("**************************** Start Check Get LED Info ****************************      \n");
    for(int id = 1; id < ONLP_LED_MAX; id++)
    {
        
        memset(&info, 0, sizeof(info));

        if(onlp_ledi_info_get(ONLP_OID_TYPE_CREATE(ONLP_OID_TYPE_LED, id), &info) >= 0){
            printf(
                "------------ Get [%s] Info ------------    \n"
                "ID             :          %u               \n"
                "Description    :          %s               \n"
                "POID           :          %u               \n"
                "COID           :          %s               \n"
                , led_id_to_string(id), info.hdr.id, info.hdr.description, info.hdr.poid, info.hdr.coids
            );

            printf(
                "Status         :          %u (%s)          \n"
                "Caps           :          %u               \n"
                "Mode           :          %u (%s)          \n"
                "Character      :          %d               \n"
                , info.status, led_status_to_string(info.status), info.caps, info.mode, led_mode_to_string(info.mode), info.character, info.mode
            );
        }
        else{
            printf("[Failed] Failed to Get LED info for [%s]!\n", led_id_to_string(id));
        }
    }


}