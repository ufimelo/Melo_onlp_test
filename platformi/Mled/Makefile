#.PHONY: all clean

#all:
#	gcc -g3 -lm -o 1_onlp_ledi_init_RESULT 1_onlp_ledi_init.c -L/lib/x86_64-linux-gnu/ -lonlp-platform -lonlp
#	gcc -g3 -lm -o 2_onlp_ledi_info_get_RESULT 2_onlp_ledi_info_get.c -I./cjson -L/lib/x86_64-linux-gnu/ -lonlp-platform -lonlp
#	gcc -g3 -lm -o 2_onlp_ledi_info_get_RESULT 2_onlp_ledi_info_get.c cjson/cJSON.c -L./lib/x86_64-linux-gnu/ -lonlp-platform -##lonlp
#	gcc -g3 -lm -o 3_onlp_ledi_status_get_RESULT 3_onlp_ledi_status_get.c -L/lib/x86_64-linux-gnu/ -lonlp-platform -lonlp
#	gcc -g3 -lm -o 4_onlp_ledi_hdr_get_RESULT 4_onlp_ledi_hdr_get.c -L/lib/x86_64-linux-gnu/ -lonlp-platform -lonlp
#	gcc -g3 -lm -o 5_onlp_ledi_set_RESULT 5_onlp_ledi_set.c -L/lib/x86_64-linux-gnu/ -lonlp-platform -lonlp
#	gcc -g3 -lm -o 6_onlp_ledi_mode_set_RESULT 6_onlp_ledi_mode_set.c cjson/cJSON.c -L/lib/x86_64-linux-gnu/ -lonlp-platform -lonlp

# -L/lib/x86_64-linux-gnu/ -lonlp-platform -lonlp => 代表要到-L/lib/x86_64-linux-gnu/ 路徑下查找文件

#2, 6 有

#clean:
#	rm -f *.o *~ core config.h *_RESULT
.PHONY all clean

CC = gcc
CFLAGS = -g3 -lm
LIBS = -L./lib/x86_64-linux-gnu/ -lonlp-platform -lonlp
SRC_DIR = .
OBJ_DIR = ./OBJ_DIR

# 列举所有源文件
SOURCES = $(wildcard $(SRC_DIR)/*.c)
# 生成所有源文件对应的目标文件
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(oBJ_DIR)/%.o, $(SOURCES))
# 列举所有目标文件
TARGETS = $(patsubst $(SRC_DIR)/%.c, %_RESULT, $(SOURCES))


all: $(TARGETS)

%_RESULT: $(OBJ_DIR)/%.o
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJ_DIR)/*.o *~ core config.h $(TARGETS)