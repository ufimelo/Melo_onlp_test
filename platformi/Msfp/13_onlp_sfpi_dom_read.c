#include <stdio.h>
#include <stdint.h>
#include "M_sfp_test.h"

#define SFP_PORT_MAX_NUM    2
#define QSFP_PORT_MAX_NUM    32

int main() {
    uint8_t data[256] = {0};
    int rc = -1;
    
    onlp_init();
    printf("Initialization done\n");

    /* Normal Case */
    for (int port = 33; port < (33+SFP_PORT_MAX_NUM); port++) {
        rc = onlp_sfpi_dom_read(port, data);
        if (rc < 0) {                           
            printf("[FAILED] Port= %d is QSFP, QSFP not supported by onlp_sfpi_dom_read()\n", port);
        } else {
            printf("[PASSED] Port= %d is SFP, SFP supported by onlp_sfpi_dom_read()\n", port);
        }
    }

    /* Error Case - QSFP */
    for (int port = 1; port <= QSFP_PORT_MAX_NUM; port++) {
        rc = onlp_sfpi_dom_read(port, data);
        if (rc < 0) {
            printf("[PASSED] Port= %d is QSFP, QSFP not supported by onlp_sfpi_dom_read() is correct\n", port);
        } else {
            printf("[FAILED] Port= %d is QSFP, QSFP should not support onlp_sfpi_dom_read() but it seems to support\n", port);
        }
    }

    /* Error Case - undefined port */
    int port=-1;
    rc = onlp_sfpi_dom_read(port, data);
    if (rc < 0) {
        printf("[PASSED] Port= %d is not a valid port, shall not supported by onlp_sfpi_dom_read() is correct\n", port);
    } else {
        printf("[FAILED] Port= %d is not a valid port, shall not support onlp_sfpi_dom_read() but it seems to support\n", port);
    }

    port=35;
    rc = onlp_sfpi_dom_read(port, data);
    if (rc < 0) {
        printf("[PASSED] Port= %d is not a valid port, shall not supported by onlp_sfpi_dom_read() is correct\n", port);
    } else {
        printf("[FAILED] Port= %d is not a valid port, shall should not support onlp_sfpi_dom_read() but it seems to support\n", port);
    }
    

    onlp_denit();
    printf("De-initialization done\n");
    return 0;
}
