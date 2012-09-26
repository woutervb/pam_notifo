# simple make file for the pam_notifo module
CURL_OPTIONS = -lcurl -fno-stack-protector
CC = $(shell curl-config --cc)

all: pam_notifo.so

pam_notifo.so: pam_notifo.o curl_notifo.o
	ld -x --shared -o pam_notifo.so pam_notifo.o -lpam curl_notifo.o $(CURL_OPTIONS)

pam_notifo.o: pam_notifo.c curl_notifo.h
	$(CC) -fPIC -Wall -c $< $(CURL_OPTIONS)

curl_notifo.o: curl_notifo.c curl_notifo.h
	$(CC) -fPIC -Wall -c $< $(CURL_OPTIONS)

clean:
	rm -f *.o *.so test
	
install: all
	@dst="`find /lib*/security /lib*/*/security -maxdepth 1               \
                    -name pam_unix.so -printf '%H' -quit 2>/dev/null`";       \
	[ -d "$${dst}" ] || dst=/lib/security;                                \
	[ -d "$${dst}" ] || dst=/usr/lib;                                     \
	sudo=; if [ $$(id -u) -ne 0 ]; then                                   \
	echo "You need to be root to install this module.";                 \
		if [ -x /usr/bin/sudo ]; then                                       \
			echo "Invoking sudo:";                                            \
			sudo=sudo;                                                        \
		else                                                                \
			exit 1;                                                           \
		fi;                                                                 \
	fi;                                                                   \
	echo cp pam_notifo.so $${dst};                          \
	tar fc - pam_notifo.so | $${sudo} tar ofxC - $${dst};   \
                                                                              \
	$${sudo} chmod 755 $${dst}/pam_notifo.so                
 	

