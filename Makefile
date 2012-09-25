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
