/***************************************************
    Melo Try onlp test
    This file should not be add in ONL prtoject
***************************************************/
#include "M_sfp_test.h"
#include "config.h"
#define SFP_PORT_MAX_NUM    2
#define QSFP_PORT_MAX_NUM    32


int main()
{
    uint8_t data[256] = {0};
    
    /* Normal Case */
    for(int port=QSFP_PORT_MAX_NUM+1; port<=QSFP_PORT_MAX_NUM+SFP_PORT_MAX_NUM; port++)
    {
        if(onlp_sfpi_dom_read(port, data) < 0)
        {
            printf("[FAILED] Port= %d is QSFP, QSFP not support onlp_sfpi_dom_read()\n");
        }
        else
        {
            printf("[PASSED] Port= %d is SFP, SFP shall support onlp_sfpi_dom_read()\n");
        }
    }

    /* Error Case */
    for(int port=1; port<=QSFP_PORT_MAX_NUM; port++)
    {
        if(onlp_sfpi_dom_read(port, data) < 0)
        {
            printf("[PASSED] Port= %d is QSFP, QSFP not support onlp_sfpi_dom_read() is correct\n");
        } 
        else
        {
            printf("[FAILED] Port= %d is QSFP, QSFP shall not support onlp_sfpi_dom_read() but here seems to support\n");
        }
    }
}