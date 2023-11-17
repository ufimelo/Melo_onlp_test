
# config.h: config.txt
#	sed -n -e 's/^\s*ONLP_TOTAL_FAN_NUMBER\s*=\s*\(.*\)\s*$$/#define ONLP_TOTAL_FAN_NUMBER \1/p' config.txt > config.h
#	Only translate ONLP_TOTAL_FAN_NUMBER into config.h

.PHONY: help all clean

help:
	@echo "Hey Darling! This is your kindest Makefile Angel, my name is Yvonne <3"
	@echo "Please Type: make [help | all | config.h | clean]"


config.h: config.txt
	sed -n -e 's/^\s*\([^#]\+\)\s*=\s*\(.*\)\s*$$/#define \1 \2/p' config.txt > config.h


all: config.h
	gcc -g3 -lm -o 1_onlp_fani_init_RESULT 1_onlp_fani_init.c -L/lib/x86_64-linux-gnu/ -lonlp-platform -lonlp
	gcc -g3 -lm -o 2_onlp_fani_info_get_RESULT 2_onlp_fani_info_get.c -L/lib/x86_64-linux-gnu/ -lonlp-platform -lonlp
#	gcc -g3 -lm -o 3_onlp_fani_status_get_RESULT 3_onlp_fani_status_get.c -L/lib/x86_64-linux-gnu/ -lonlp-platform -lonlp
#	gcc -g3 -lm -o 4_onlp_fani_hdr_get_RESULT 4_onlp_fani_hdr_get.c -L/lib/x86_64-linux-gnu/ -lonlp-platform -lonlp


clean:
#	rm *.o *~ core config.h
#	rm -f *.o *~ core config.h 1_onlp_fani_init_RESULT 2_onlp_fani_info_get_RESULT 3_onlp_fani_status_get_RESULT 4_onlp_fani_hdr_get_RESULT
	rm -f *.o *~ core config.h *_RESULT
