/***************************************************
    Melo Try onlp test
    This file should not be add in ONL prtoject
***************************************************/
#include "M_led_test.h"

// Use only for led mode set test
int invalid_modes[] = {1, 2, 10, 11, 12, 13, 20, 21, 22, 23};
int num_invalid_modes = sizeof(invalid_modes) / sizeof(invalid_modes[0]);
int is_invalid_mode = 0;


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


    //2. test onlp_ledi_mode_set() API
    for(int id = 1; id < ONLP_LED_MAX; id++)  //id represents where the LED location is (Melo's note)
    {
        printf("********************************** Start Check Set Mode [ID: %s] **********************************     \n", led_id_to_string(id));

        for(int mode = 0; mode < ONLP_LED_MODE_MAX; mode++){  //LED Mode is about the color and blinling status of the LED (Melo's note)
            
            //Skip mode that is not define in onlp_led_mode_e (by Melo)
            if(strcmp(led_mode_to_string(mode), "UNKNOWN") == 0){
                //printf("Skip not defined Mode: %d is %s\n", mode, led_mode_to_string(mode));
                continue;
            }
            
            if(onlp_ledi_mode_set(ONLP_OID_TYPE_CREATE(ONLP_OID_TYPE_LED, id), mode) >= 0){

                // print Set mode
                printf(
                    "------------ Set LED Mode to: %d [%s] ------------     \n"   // ONLP define (typedef enum onlp_led_mode_e) switch(case)
                    , mode, led_mode_to_string(mode)
                );

                // print former LED Info
                  printf(
                    "Former Status      :       %u (%s)          \n"
                    "Former Mode        :       %u (%s)          \n"
                    , info.status, led_status_to_string(info.status), info.mode, led_mode_to_string(info.mode)
                );

                //Get NEW LED Info
                memset(&info, 0, sizeof(info));
                if(onlp_ledi_info_get(ONLP_OID_TYPE_CREATE(ONLP_OID_TYPE_LED, id), &info) >= 0){
                    printf("Get LED Info Successed after setting mode       \n");
                }else{ 
                    printf("[Failed] Failed to Get LED info for [%s] after set LED mode = [%d]!       \n", led_id_to_string(id), mode);
                    break;
                }
                
                // print NEW LED Info
                printf(
                    "New Status         :       %u (%s)                                                                             \n"
                    "New Mode           :       %u (%s) (ONLP define API [typedef enum onlp_led_mode_e] switch(case) = %d)          \n"
                    , info.status, led_status_to_string(info.status), info.mode, led_mode_to_string(info.mode), mode
                );

                if(info.mode == mode){
                    printf("[Passed] Set [%s] to Mode [%s (%d)] PASS!      \n\n", led_id_to_string(id),led_mode_to_string(mode), mode);
                }
                else {
                    printf("[Warning] Set [%s] to Mode [%s (%d)], Can't be Changed !        \n\n", led_id_to_string(id),led_mode_to_string(mode), mode);
                }

            }else{
               
               // check if set mode is supported
               for(int i = 0; i < num_invalid_modes; i++){
                    if(mode == invalid_modes[i]){
                        is_invalid_mode = 1;
                        break;
                    }
               }

               if (!is_invalid_mode){
                    printf("Failed to Set [%s] to mode: [%d]!       \n", led_id_to_string(id), mode);
               }
            }
        }
    }

    onlp_denit();
    return 0;
}



