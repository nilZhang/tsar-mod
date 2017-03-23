# tsar-mod


<pre>
[zhangzhong@h8-vm5:/home/zhangzhong/tsar-mod/php_fpm]tsar -l
Time              ---cpu-- ---mem-- ---tcp-- -----traffic---- ---load- ------nginx----- -----php-fpm----
Time                util     util   retran    bytin  bytout    load1      qps      rt    slowR     qps
23/03/17-17:09:22   9.76    77.48     0.00     6.3K    3.2K     9.28     0.60    1.6K     0.00    0.00
</pre>

<pre>
[zhangzhong@h8-vm5:/home/zhangzhong/tsar-mod/php_fpm]tsar -l --nginx -i1
Time              ----------------------------------nginx---------------------------------
Time              accept  handle    reqs  active    read   write    wait     qps      rt
23/03/17-17:09:00   1.00    1.00    1.00    1.00    0.00    1.00    0.00    1.00   47.00
23/03/17-17:09:01   1.00    1.00    1.00    1.00    0.00    1.00    0.00    1.00    1.00
23/03/17-17:09:02   1.00    1.00    1.00    1.00    0.00    1.00    0.00    1.00   83.00


</pre>
<pre>
Time              -----------------------------------------php-fpm----------------------------------------
Time              accept   queue    maxq    qlen    idle  active   total  mactiv  mreach   slowR     qps
23/03/17-16:44:17   9.00    0.00  104.00  128.00  811.00    1.00  812.00   13.7K    0.00    0.00    1.00
23/03/17-16:44:22  23.00    0.00  104.00  128.00  810.00    2.00  812.00   13.7K    0.00    0.00    4.00
23/03/17-16:44:27  30.00    0.00  104.00  128.00  810.00    2.00  812.00   13.7K    0.00    0.00    6.00
23/03/17-16:44:32  19.00    0.00  104.00  128.00  811.00    1.00  812.00   13.7K    0.00    0.00    3.00
</pre>