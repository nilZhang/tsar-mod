CFLAGS = -Wall -fPIC --shared -g -O2
CC = gcc
INCLUDE_DIR = /usr/local/tsar/devel
LINK = $(CC) -I$(INCLUDE_DIR) $(CFLAGS)


OBJS =  mod_ngx.so

all: $(OBJS)

$(OBJS): %.so: %.c
	$(LINK) $< -o $@
clean:
	rm -f *.so;
install:
	mkdir -p /etc/tsar/conf.d/
	cp ./mod_ngx.so /usr/local/tsar/modules/
	cp ./mod_ngx.conf /etc/tsar/conf.d/ngx.conf
uninstall:
	rm /usr/local/tsar/modules/mod_ngx.so
	rm /etc/tsar/conf.d/ngx.conf
