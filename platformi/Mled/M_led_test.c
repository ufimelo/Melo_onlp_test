/***************************************************
    Melo Try onlp test
    This file should not be add in ONL prtoject
***************************************************/
#include "M_led_test.h"


int main()
{
    printf("START M_led_test\n");

    printf("START ONLP INITIALIZATION...\n");
    onlp_init();
    onlp_led_info_t info = {0};
    onlp_oid_hdr_t hdr = {0};
    unsigned int rv = 0;

    printf("START GET LED INFO\n");
    onlp_ledi_info_get(ONLP_OID_TYPE_CREATE(ONLP_OID_TYPE_LED, ONLP_LED_SYS_SYS), &info);
    //onlp_ledi_status_get(ONLP_OID_TYPE_CREATE(ONLP_OID_TYPE_LED, ONLP_LED_SYS_SYS), &rv);
    //onlp_ledi_hdr_get(ONLP_OID_TYPE_CREATE(ONLP_OID_TYPE_LED, ONLP_LED_SYS_SYS), &hdr);
    //onlp_ledi_set(ONLP_OID_TYPE_CREATE(ONLP_OID_TYPE_LED, ONLP_LED_SYS_SYS), 1);
    onlp_ledi_mode_set(ONLP_OID_TYPE_CREATE(ONLP_OID_TYPE_LED, ONLP_LED_SYS_SYS), ONLP_LED_MODE_YELLOW_BLINKING);
    
    //onlp_led_id id;

    //1
    for(int id = 1; id < ONLP_LED_MAX; id++)
    {
        if(onlp_ledi_info_get(ONLP_OID_TYPE_CREATE(ONLP_OID_TYPE_LED, id), &info) >= 0){
            printf(
                "********* %s *********\n"
                "ID: %u\n"
                "Description: %s\n"
                "POID: %u\n"
                "COID: %s\n",
                led_id_to_string(id), info.hdr.id, info.hdr.description, info.hdr.poid, info.hdr.coids
            );

            printf(
                "Status: %u\n"
                "Caps:   %u\n"
                "Mode:    %u (%s)\n"
                "Character: %d\n",
                info.status, info.caps, info.mode, led_mode_to_string(info.mode), info.character, info.mode
            );
        }
        else{
        printf("Failed to get LED info for %s\n", led_id_to_string(id));
        }
    }

    //2
    enum led_mode_to_string mode;
    for(int id = 1; id < ONLP_LED_MAX; id++)
    {
        printf("Start Check LED set Mode");
        printf("**************************** Start Check [%s] set Mode ****************************\n", led_id_to_string(id));
        for(mode = ONLP_LED_MODE_OFF; mode < ONLP_LED_MODE_MAX; mode++){
            if(onlp_ledi_mode_set(ONLP_OID_TYPE_CREATE(ONLP_OID_TYPE_LED, id), mode), &info) >= 0){
                printf(
                    "********* %s *********\n"
                    "ID: %u\n"
                    "Description: %s\n",
                    //"POID: %u\n"
                    //"COID: %s\n",
                    led_mode_to_string(mode), info.hdr.id, info.hdr.description/*, info.hdr.poid, info.hdr.coids*/
                );

                printf(
                    "Status: %u\n"
                    "Caps:   %u\n"
                    "Mode:    %u (%s)\n",
                    //"Character: %d\n",
                    info.status, info.caps, info.mode, led_mode_to_string(info.mode)/*, info.character*/
                );
            }
            else{
                printf("Failed to get LED info for %s\n", led_id_to_string(id));
            }
        }
    }

    onlp_denit();
    return 0;
}



