curl "http://127.0.0.1/php-fpm-status" -v


* About to connect() to 127.0.0.1 port 80 (#0)
*   Trying 127.0.0.1...
* Connected to 127.0.0.1 (127.0.0.1) port 80 (#0)
> GET /php-fpm-status HTTP/1.1
> User-Agent: curl/7.29.0
> Host: 127.0.0.1
> Accept: */*
>
< HTTP/1.1 200 OK
< Server: nginx
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