CFLAGS = -Wall -fPIC --shared -g -O2
CC = gcc
INCLUDE_DIR = /usr/local/tsar/devel
LINK = $(CC) -I$(INCLUDE_DIR) $(CFLAGS)


OBJS =  mod_nginx.so

all: $(OBJS)

$(OBJS): %.so: %.c
	$(LINK) $< -o $@
clean:
	rm -f *.so;
install:
	mkdir -p /etc/tsar/conf.d/
	cp ./mod_nginx.so /usr/local/tsar/modules/
	cp ./mod_nginx.conf /etc/tsar/conf.d/nginx.conf
uninstall:
	rm /usr/local/tsar/modules/mod_nginx.so
	rm /etc/tsar/conf.d/nginx.conf
