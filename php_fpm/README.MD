
tsar-mod_php-fpm
==============

#php-fpm/tengine module for tsar

Support read data from php-fpm by common socket or unix domain socket.


Quick start
-----------
1. Install [tsar](http://code.taobao.org/p/tsar/src/).

2. get module

2.1. Generate a new module by using [tsardevel].

    >tsardevel php_fpm

    Replace mod_php_fpm.c by (https://github.com/nilZhang/tsar-mod/tree/master/php_fpm)

    > make

    > make install

2.2 get module direct by https://github.com/nilZhang/tsar-mod/tree/master/php_fpm
     > make clean && make && sudo make install && tsar -l --php-fpm
3. >`tsar --php-fpm`

Configuration
-------------
1. Default host is 127.0.0.1 and default port is 80. But we can change both (or one of) the host and port:

evn PHP_FPM_TSAR_HOST

   host = PHP_FPM_TSAR_HOST ?:'127.0.0.1'

evn PHP_FPM_TSAR_PORT
   
   port = PHP_FPM_TSAR_PORT ?: 80

env PHP_FPM_TSAR_URI

    uri = PHP_FPM_TSAR_URI ?: "/php-fpm-status"

    #### modify env 

	> export PHP_FPM_TSAR_HOST=192.168.0.1

 
2. Stub Status module must be included,and add configuration as below:

    
    location = /php-fpm-status {
        access_log off;
        allow 127.0.0.1;
        deny all;

        include        fastcgi_params;
        fastcgi_pass   php_fpm_status_upstream;
        fastcgi_param  SCRIPT_FILENAME  $fastcgi_script_name;
    }

    if you open assess_log ,then the access_log-xxx will have the log as after log.

     127.0.0.1 - - [23/Mar/2017:16:35:30 +0800] "GET /php-fpm-status HTTP/1.0" 200 395 "-" "/1.9" "-" 0.003 "-" "CgALVdKI01j4sQAAxwEAAA--" "1tebjflet5ug4flu&1&uo" "-"

3. We can also using unix domain socket, if we set PHP_FPM_TSAR_HOST to a filesystem path:

    ####example: 
    >`export PHP_FPM_TSAR_HOST=/tmp/php-fpm-tsar.sock`

    php-fpm server(which includes the location /php-fpm-status) must also listen to the unix domain socket path
   
    >`listen unix:/tmp/php-fpm-tsar.sock;`

4. The uri and server name sent to the php-fpm server can alse be changed:

    ####example: 
    >`export PHP_FPM_TSAR_SERVER_NAME=zhangzhong`

    >`export PHP_FPM_TSAR_SERVER_NAME=/php-fpm-status`



5. display 

	shell >  tsar -l --php-fpm


	Time              -----------------------------------------php-fpm----------------------------------------
	Time              accept   queue    maxq    qlen    idle  active   total  mactiv  mreach   slowR     qps
	23/03/17-16:44:17   9.00    0.00  104.00  128.00  811.00    1.00  812.00   13.7K    0.00    0.00    1.00
	23/03/17-16:44:22  23.00    0.00  104.00  128.00  810.00    2.00  812.00   13.7K    0.00    0.00    4.00




6. other


curl  "http://127.0.0.1/php-fpm-status" -v


* About to connect() to 127.0.0.1 port 80 (#0)
*   Trying 127.0.0.1...
* Connected to 127.0.0.1 (127.0.0.1) port 80 (#0)
> GET /php-fpm-status HTTP/1.1
> User-Agent: curl/7.29.0
> Host: 127.0.0.1
> Accept: */*
>
< HTTP/1.1 200 OK
< Server: php-fpm
< Date: Thu, 23 Mar 2017 02:49:10 GMT
< Content-Type: text/plain;charset=UTF-8
< Transfer-Encoding: chunked
< Connection: keep-alive
< Expires: Thu, 01 Jan 1970 00:00:00 GMT
< Cache-Control: no-cache, no-store, must-revalidate, max-age=0
< Set-Cookie: B=1tebjflximfpe5ye&1&s0; expires=Fri, 23-Mar-18 02:49:10 GMT; path=/
<
pool:                 wwwport
process manager:      dynamic
start time:           22/Mar/2017:17:54:46 +0800
start since:          60864
accepted conn:        295165
listen queue:         0
max listen queue:     70
listen queue len:     128
idle processes:       304
active processes:     1
total processes:      305
max active processes: 1170
max children reached: 0
slow requests:        1
* Connection #0 to host 127.0.0.1 left intact



naccepted_conn:        295165
nlisten_queue:         0
nmax_listen_queue:     70
nlisten_queue_len:     128
nidle_processes:       304
nactive_processes:     1
ntotal_processes:      305
nmax_active_processes: 1170
nmax_children_reached: 0
nslow_requests:        1