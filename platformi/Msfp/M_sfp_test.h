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

#define ONLP_CONFIG_INFO_STR_MAX 64

/* printf with timestamp in microseconds (Melo)
***********************************************
     (1 second = 1,000,000 microseconds) */
void t_printf(const char* format, ...) {
    struct timeval tv;
    struct tm* tm_info;

    // 取得當前時間
    gettimeofday(&tv, NULL);
    tm_info = localtime(&tv.tv_sec);

    // 印出時間戳記（包括微秒）
    printf("[%04d/%02d/%02d %02d:%02d:%02d.%06ld]  ", 
           tm_info->tm_year + 1900, tm_info->tm_mon + 1, tm_info->tm_mday,
           tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec, tv.tv_usec);

    // 使用可變引數列表處理訊息
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    printf("\n");
}
/*void t_printf(const char* format, ...) {
    // 開始測量時間
    struct timeval start_time;
    gettimeofday(&start_time, NULL);

    // 使用可變引數列表處理訊息
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    // 結束測量時間
    struct timeval end_time;
    gettimeofday(&end_time, NULL);

    // 計算所經過的時間（以微秒為單位）
    long elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000000 +
                        (end_time.tv_usec - start_time.tv_usec);

    // 印出執行時間
    printf("\nExecution Time: %ld ms\n", elapsed_time);
}*/


//read config file
void readConfigFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[256];

    while (fgets(line, sizeof(line), file)) {
        // Ignore comments and empty lines
        if (line[0] == '#' || line[0] == '\n') {
            continue;
        }

        // Parse each line and extract configuration data
        char *key = strtok(line, "=");
        char *value = strtok(NULL, "=");

        // Remove leading and trailing whitespaces from key and value
        key = strtok(key, " \t\n\r");
        value = strtok(value, " \t\n\r");

        // Process key and value as needed
        printf("Key: %s, Value: %s\n", key, value);
    }

    fclose(file);
}


/* Test funciton */
extern int onlp_sfpi_dom_read(int port, uint8_t data[256]);

extern int onlp_init(void);
extern int onlp_denit(void);