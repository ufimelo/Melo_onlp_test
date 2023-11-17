#include "M_psu_test.h"

int main()
{
    printf("[START] START M_fan_test!    \n");
    printf("START ONLP INITIALIZATION...    \n");
    // onlp_psui_init();
    onlp_init();
    printf("ONLP INITIALIZATION DONE!   \n");

    onlp_psu_info_t info = {0};

    printf("[START] START GET FAN INFO   \n");
    for(int psu_id = 1; psu_id <= ONLP_TOTAL_PSU_NUMBER; psu_id++){
        if(onlp_psui_info_get(ONLP_OID_TYPE_CREATE(ONLP_OID_TYPE_PSU, psu_id), &info) >= 0){
            printf(
                "************* PSU %d OID Header *************     \n"
                "ID             :   %u          \n"
                "Description    :   %s          \n"
                "POID           :   %u          \n"
                "COID           :   %s          \n"
                , psu_id, info.hdr.id, info.hdr.description, info.hdr.poid, info.hdr.coids
            );

            printf(
                "--------- PSU %d Other Info ---------    \n"
                "Model          :   %s                  \n"
                "Serial         :   %s                  \n"
                "Status         :   %u                  \n"
                "Caps           :   %u                  \n"
                "Vin            :   %d  (millivolts)    \n"
                "Vout           :   %d  (millivolts)    \n"
                "Iin            :   %d  (milliamps)     \n"
                "Iout           :   %d  (milliamps)     \n"
                "Pin            :   %d  (milliwatts)    \n"
                "Pout           :   %d  (milliwatts)    \n"
                , psu_id, info.model, info.serial, info.serial, info.caps,
                info.mvin, info.mvout, info.miin, info.miout, info.mpin, info.mpout);

            printf("Get PSU %d Info Done!   \n", psu_id);
            memset(&info, 0, sizeof(info));
        }
        else {
            printf("[FAILED] Failed To Get PSU %d INFO! \n", psu_id);
        }
    }
    printf("[DONE] Get PSU INFO Done!   \n");

    onlp_denit();
    return 0;
}



