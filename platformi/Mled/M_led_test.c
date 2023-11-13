/***************************************************
    Melo Try onlp test
    This file should not be add in ONL prtoject
***************************************************/
#include "M_led_test.h"


int main()
{
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
    

    //1. check onlp_ledi_info_get(ONLP_OID_TYPE_CREATE(ONLP_OID_TYPE_LED, ONLP_LED_SYS_SYS), &info);
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

    //2. check onlp_ledi_mode_set(ONLP_OID_TYPE_CREATE(ONLP_OID_TYPE_LED, ONLP_LED_SYS_SYS), ONLP_LED_MODE_YELLOW_BLINKING);
    /*enum onlp_led_id {
        ONLP_LED_RESERVED  = 0,
        ONLP_LED_SYS_SYNC = 1,
        ONLP_LED_SYS_SYS,
        ONLP_LED_SYS_FAN,
        ONLP_LED_SYS_PSU_0,
        ONLP_LED_SYS_PSU_1,
        ONLP_LED_SYS_ID,
        ONLP_LED_MAX
    };*/
    for(int id = 1; id < ONLP_LED_MAX; id++)  //id represents where the LED location is (Melo's note)
    {
        printf("**************************************** Start Check Set Mode [ID: %s] ****************************************     \n", led_id_to_string(id));

        /*typedef enum onlp_oid_type_e {
                ONLP_OID_TYPE_SYS = 1,
                ONLP_OID_TYPE_THERMAL = 2,
                ONLP_OID_TYPE_FAN = 3,
                ONLP_OID_TYPE_PSU = 4,
                ONLP_OID_TYPE_LED = 5,
                ONLP_OID_TYPE_MODULE = 6,
                ONLP_OID_TYPE_RTC = 7,
            } onlp_oid_type_t;*/
        for(int mode = 0; mode < ONLP_LED_MODE_MAX; mode++){  //LED Mode is about the color and blinling status of the LED (Melo's note)
            
            memset(&info, 0, sizeof(info));
            
            if(onlp_ledi_mode_set(ONLP_OID_TYPE_CREATE(ONLP_OID_TYPE_LED, id), mode) >= 0){
                
                //Skip mode that is not define in onlp_led_mode_e (by Melo)
                /*if(strcmp(led_mode_to_string(mode), "UNKNOWN") == 0){
                    //printf("Skip Mode: %s\n", led_mode_to_string(mode));
                    continue;
                }*/

                //Get LED Info
                if(onlp_ledi_info_get(ONLP_OID_TYPE_CREATE(ONLP_OID_TYPE_LED, id), &info) > 0){
                    continue;
                }else{ 
                    printf("[Failed] Failed to Get LED info for [%s] after set LED mode = [%d]!       \n", led_id_to_string(id), mode);
                }
                
                printf(
                    "------------ Set LED Mode to: %u [%s = ONLP define (typedef enum onlp_led_mode_e) switch(case) %d] ------------     \n"
                    , info.mode, led_mode_to_string(mode), mode
                );
                
                printf(
                    "Status             :       %u (%s)                                                                             \n"
                    "Caps               :       %u                                                                                  \n"
                    "Mode               :       %u (%s) (ONLP define API [typedef enum onlp_led_mode_e] switch(mode) = %d)          \n"
                    , info.status, led_status_to_string(info.status), info.caps, info.mode, led_mode_to_string(info.mode), mode
                );
            }else{
                printf("Failed to Set LED info for [%s]!       \n", led_id_to_string(id));
            }
        }
    }

    onlp_denit();
    return 0;
}



