/***************************************************
    Melo Try onlp test
    This file should not be add in ONL prtoject
***************************************************/
#include "M_fan_test.h"


int main()
{
    printf("[START] START M_fan_test!    \n");

    printf("START ONLP INITIALIZATION...    \n");
    // onlp_psui_init();
    onlp_init();
    printf("ONLP INITIALIZATION DOWN!   \n");

    onlp_fan_info_t info = {0};

    printf("1. START GET FAN INFO   \n");
    for(int fan_id = 1; fan_id <= ONLP_TOTAL_FAN_NUMBER; fan_id++){
        printf("Get FAN %d Info...  \n", fan_id);

        if(onlp_fani_info_get(ONLP_OID_TYPE_CREATE(ONLP_OID_TYPE_FAN, fan_id), &info) >= 0){
            printf(
                "********* FAN %d OID Header *********     \n"
                "ID             :   %u          \n"
                "Description    :   %s          \n"
                "POID           :   %u          \n"
                "COID           :   %s          \n"
                , fan_id, info.hdr.id, info.hdr.description, info.hdr.poid, info.hdr.coids
            );

            printf(
                "********* FAN %d Other Info *********    \n"
                "Status         :   %u (%s)     \n"
                "Caps           :   %u          \n"
                "RPM            :   %u          \n"
                "Percentage     :   %d          \n"
                "Mode           :   %d (%s)     \n"
                "Model          :   %s          \n"
                "Serial No.     :   %s          \n"
                , info.status, fan_status_to_string(info.status), info.caps, info.rpm, info.percentage, info.mode, fan_mode_to_string(info.mode), info.model, info.serial
            );

            printf("Get FAN %d Info Done!   \n", fan_id);
            memset(&info, 0, sizeof(info));
        } 
        else {
            printf("[FAILED] Failed To Get FAN %d INFO! \n", fan_id);
        }
    }
    printf("[DONE] Get FAN INFO Done!   \n");

    onlp_denit();
    return 0;
}


