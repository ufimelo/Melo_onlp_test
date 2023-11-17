.PHONY: help all FAN LED clean

help:
	@echo "Hey Darling! This is your kindest Makefile Angel, my name is Yvonne <3"
	@echo "Please Type: make [help | all | FAN | LED | config.h | clean]"


config.h: config.txt
	sed -n -e 's/^\s*\([^#]\+\)\s*=\s*\(.*\)\s*$$/#define \1 \2/p' config.txt > config.h

FAN: config.h
	gcc -g3 -lm -o m_fan_test_result ./Mfan/M_fan_test.c -L/lib/x86_64-linux-gnu/ -lonlp-platform -lonlp


LED: config.h
	gcc -g3 -lm -o test_led_info_get_result ./Mled/TEST_onlp_ledi_info_get.c -L/lib/x86_64-linux-gnu/ -lonlp-platform -lonlp
	gcc -g3 -lm -o test_led_mode_set_result ./Mled/TEST_onlp_ledi_mode_set.c -L/lib/x86_64-linux-gnu/ -lonlp-platform -lonlp

all: FAN LED

clean:
#	rm *.o *~ core config.h
	rm -f *.o *~ core config.h m_fan_test_result