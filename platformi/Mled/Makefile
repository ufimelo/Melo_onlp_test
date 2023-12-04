.PHONY: all clean

CC = gcc
CFLAGS = -g3 -lm
LIBS = -L./lib/x86_64-linux-gnu/ -lonlp-platform -lonlp
CONFIG_LIB = ../platformi/cjson/cJSON.c

all:
#	gcc -g3 -lm -o 1_onlp_ledi_init_RESULT 1_onlp_ledi_init.c -L/lib/x86_64-linux-gnu/ -lonlp-platform -lonlp
	$(CC) $(CFLAGS) -o 2_onlp_ledi_info_get_RESULT 2_onlp_ledi_info_get.c $(CONFIG_LIB) $(LIBS)
#	gcc -g3 -lm -o 2_onlp_ledi_info_get_RESULT 2_onlp_ledi_info_get.c cjson/cJSON.c -L./lib/x86_64-linux-gnu/ -lonlp-platform -##lonlp
#	gcc -g3 -lm -o 3_onlp_ledi_status_get_RESULT 3_onlp_ledi_status_get.c -L/lib/x86_64-linux-gnu/ -lonlp-platform -lonlp
#	gcc -g3 -lm -o 4_onlp_ledi_hdr_get_RESULT 4_onlp_ledi_hdr_get.c -L/lib/x86_64-linux-gnu/ -lonlp-platform -lonlp
#	gcc -g3 -lm -o 5_onlp_ledi_set_RESULT 5_onlp_ledi_set.c -L/lib/x86_64-linux-gnu/ -lonlp-platform -lonlp
	$(CC) $(CFLAGS) -o 6_onlp_ledi_mode_set_RESULT 6_onlp_ledi_mode_set.c $(CONFIG_LIB) $(LIBS)
#	gcc -g3 -lm -o 6_onlp_ledi_mode_set_RESULT 6_onlp_ledi_mode_set.c cjson/cJSON.c -L/lib/x86_64-linux-gnu/ -lonlp-platform -lonlp

# -L/lib/x86_64-linux-gnu/ -lonlp-platform -lonlp => 代表要到-L/lib/x86_64-linux-gnu/ 路徑下查找文件

#2, 6 有

clean:
	rm -f *.o *~ core config.h *_RESULT