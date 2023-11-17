
# config.h: config.txt
#	sed -n -e 's/^\s*ONLP_TOTAL_FAN_NUMBER\s*=\s*\(.*\)\s*$$/#define ONLP_TOTAL_FAN_NUMBER \1/p' config.txt > config.h
#	Only translate ONLP_TOTAL_FAN_NUMBER into config.h

.PHONY: help all clean

help:
	echo "type make [help | config.h | all | clean]"


config.h: config.txt
	sed -n -e 's/^\s*\([^#]\+\)\s*=\s*\(.*\)\s*$$/#define \1 \2/p' config.txt > config.h


all: config.h
	gcc -g3 -lm -o m_fan_test_result M_fan_test.c -L/lib/x86_64-linux-gnu/ -lonlp-platform -lonlp


clean:
#	rm *.o *~ core config.h
	rm -f *.o *~ core config.h m_fan_test_result