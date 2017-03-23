CFLAGS = -Wall -fPIC --shared -g -O2
CC = gcc
INCLUDE_DIR = /usr/local/tsar/devel
LINK = $(CC) -I$(INCLUDE_DIR) $(CFLAGS)


OBJS =  mod_php-fpm.so

all: $(OBJS)

$(OBJS): %.so: %.c
	$(LINK) $< -o $@
clean:
	rm -f *.so;
install:
	mkdir -p /etc/tsar/conf.d/
	cp ./mod_php-fpm.so /usr/local/tsar/modules/
	cp ./mod_php-fpm.conf /etc/tsar/conf.d/php-fpm.conf
uninstall:
	rm /usr/local/tsar/modules/mod_php-fpm.so
	rm /etc/tsar/conf.d/php-fpm.conf
