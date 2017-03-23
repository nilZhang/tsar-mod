CFLAGS = -Wall -fPIC --shared -g -O2
CC = gcc
INCLUDE_DIR = /usr/local/tsar/devel
LINK = $(CC) -I$(INCLUDE_DIR) $(CFLAGS)


OBJS =  mod_php_fpm.so

all: $(OBJS)

$(OBJS): %.so: %.c
	$(LINK) $< -o $@
clean:
	rm -f *.so;
install:
	mkdir -p /etc/tsar/conf.d/
	cp ./mod_php_fpm.so /usr/local/tsar/modules/
	cp ./mod_php_fpm.conf /etc/tsar/conf.d/php_fpm.conf
uninstall:
	rm /usr/local/tsar/modules/mod_php_fpm.so
	rm /etc/tsar/conf.d/php_fpm.conf
