#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include "tsar.h"
#include <stdio.h>

struct stats_php_fpm {
    U_64 naccepted_conn;
    U_64 nlisten_queue;
    U_64 nmax_listen_queue;
    U_64 nlisten_queue_len;
    U_64 nidle_processes;
    U_64 nactive_processes;
    U_64 ntotal_processes;
    U_64 nmax_active_processes;
    U_64 nmax_children_reached;
    U_64 nslow_requests;
};


struct hostinfo {
    char *host;
    int port;
    char *server_name;
    char *uri;
};

static char *php_fpm_usage = "    --php-fpm            php_fpm statistics";

static struct mod_info php_fpm_info[] = {
    {"accept", DETAIL_BIT,  0,  STATS_SUB},
    {" queue", DETAIL_BIT,  0,  STATS_SUB},
    {"  maxq", DETAIL_BIT,  0,  STATS_NULL},
    {"  qlen", DETAIL_BIT,  0,  STATS_NULL},
    {"  idle", DETAIL_BIT,  0,  STATS_NULL},
    {"active", DETAIL_BIT,  0,  STATS_NULL},
    {" total", DETAIL_BIT,  0,  STATS_NULL},
    {"mactiv", DETAIL_BIT, 0,  STATS_NULL},
    {"mreach", DETAIL_BIT, 0,  STATS_NULL},
    {" slowR", SUMMARY_BIT, 0,  STATS_NULL},
    {"   qps", SUMMARY_BIT, 0,  STATS_SUB_INTER},
   
};


static void set_php_fpm_record(struct module *mod, double st_array[],
                             U_64 pre_array[], U_64 cur_array[], int inter)
{
    int i;
    for (i = 0; i < 9; i++) {
      st_array[i] = cur_array[i] ;
        
    }
    st_array[0]=(cur_array[0] - pre_array[0]);
    st_array[10]=(cur_array[0] - pre_array[0])/inter;
}

 

 

static void init_php_fpm_host_info(struct hostinfo *p)
{
    char *port;

    p->host = getenv("PHP_FPM_TSAR_HOST");
    p->host = p->host ? p->host : "127.0.0.1";

    port = getenv("PHP_FPM_TSAR_PORT");
    p->port = port ? atoi(port) : 80;

    p->uri = getenv("NGX_TSAR_URI");
    p->uri = p->uri ? p->uri : "/php-fpm-status";

    p->server_name = getenv("NGX_TSAR_SERVER_NAME");
    p->server_name = p->server_name ? p->server_name : "zhangzhong";
}


void read_php_fpm_stats(struct module *mod)
{
    int write_flag = 0, addr_len, domain;
    int m, sockfd, send, pos;
    void *addr;
    char buf[LEN_4096], request[LEN_4096], line[LEN_4096];

    struct sockaddr_in servaddr;
    struct sockaddr_un servaddr_un;
    FILE *stream = NULL;
    struct hostinfo hinfo;
    init_php_fpm_host_info(&hinfo);
    struct stats_php_fpm st_php_fpm;
    memset(&st_php_fpm, 0, sizeof(struct stats_php_fpm));

    if (*hinfo.host == '/') {
        addr = &servaddr_un;
        addr_len = sizeof(servaddr_un);
        bzero(addr, addr_len);
        domain = AF_LOCAL;
        servaddr_un.sun_family = AF_LOCAL;
        strncpy(servaddr_un.sun_path, hinfo.host, sizeof(servaddr_un.sun_path) - 1);

    } else {
        addr = &servaddr;
        addr_len = sizeof(servaddr);
        bzero(addr, addr_len);
        domain = AF_INET;
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(hinfo.port);
        inet_pton(AF_INET, hinfo.host, &servaddr.sin_addr);
    }


    if ((sockfd = socket(domain, SOCK_STREAM, 0)) == -1) {
        goto writebuf;
    }

    sprintf(request,
        "GET %s HTTP/1.0\r\n"
        "User-Agent:/1.9\r\n"
        "Host: %s\r\n"
        "Accept:*/*\r\n"
        "Connection: Close\r\n\r\n",
        hinfo.uri, hinfo.server_name);

    if ((m = connect(sockfd, (struct sockaddr *) addr, addr_len)) == -1 ) {
        goto writebuf;
    }

    if ((send = write(sockfd, request, strlen(request))) == -1) {
        goto writebuf;
    }

    if ((stream = fdopen(sockfd, "r")) == NULL) {
        goto writebuf;
    }

    
    //     if (!strncmp(line, "Active connections:", sizeof("Active connections:") - 1)) {
    //         sscanf(line + sizeof("Active connections:"), "%llu", &st_php_fpm.nactive);
    //     } else if (!strncmp(line, " ", 1)) {
    //         sscanf(line + 1, "%llu %llu %llu %llu",
    //                 &st_php_fpm.naccept, &st_php_fpm.nhandled, &st_php_fpm.nrequest, &st_php_fpm.nrstime);
    //         write_flag = 1;
    //     } else if (!strncmp(line, "Reading:", sizeof("Reading:") - 1)) {
    //         sscanf(line, "Reading: %llu Writing: %llu Waiting: %llu",
    //                 &st_php_fpm.nreading, &st_php_fpm.nwriting, &st_php_fpm.nwaiting);
    //     }
    //     else
    //         ;
    // }

    while (fgets(line, LEN_4096, stream) != NULL) {
             if (!strncmp(line, "accepted conn:        ",21)){ sscanf(line + 22, "%llu", &st_php_fpm.naccepted_conn); write_flag = 1 ;}
        else if (!strncmp(line, "listen queue:         ",21)){ sscanf(line + 22, "%llu", &st_php_fpm.nlisten_queue); }
        else if (!strncmp(line, "max listen queue:     ",21)){ sscanf(line + 22, "%llu", &st_php_fpm.nmax_listen_queue); }
        else if (!strncmp(line, "listen queue len:     ",21)){ sscanf(line + 22, "%llu", &st_php_fpm.nlisten_queue_len); }
        else if (!strncmp(line, "idle processes:       ",21)){ sscanf(line + 22, "%llu", &st_php_fpm.nidle_processes); }
        else if (!strncmp(line, "active processes:     ",21)){ sscanf(line + 22, "%llu", &st_php_fpm.nactive_processes); }
        else if (!strncmp(line, "total processes:      ",21)){ sscanf(line + 22, "%llu", &st_php_fpm.ntotal_processes); }
        else if (!strncmp(line, "max active processes: ",21)){ sscanf(line + 22, "%llu", &st_php_fpm.nmax_active_processes); }
        else if (!strncmp(line, "max children reached: ",21)){ sscanf(line + 22, "%llu", &st_php_fpm.nmax_children_reached); }
        else if (!strncmp(line, "slow requests:        ",21)){ sscanf(line + 22, "%llu", &st_php_fpm.nslow_requests); }
        else
                ;
    }
    
writebuf:
    

    if (stream) {
        fclose(stream);
    }

    if (sockfd != -1) {
        close(sockfd);
    }

    if (write_flag) {
        pos = sprintf(buf, "%lld,%lld,%lld,%lld,%lld,%lld,%lld,%lld,%lld,%lld",
                st_php_fpm.naccepted_conn,
                st_php_fpm.nlisten_queue,
                st_php_fpm.nmax_listen_queue,
                st_php_fpm.nlisten_queue_len,
                st_php_fpm.nidle_processes,
                st_php_fpm.nactive_processes,
                st_php_fpm.ntotal_processes,
                st_php_fpm.nmax_active_processes,
                st_php_fpm.nmax_children_reached,
                st_php_fpm.nslow_requests
                );
        
        buf[pos] = '\0';
        set_mod_record(mod, buf);
    }
}


void mod_register(struct module *mod)
{
    register_mod_fields(mod, "--php-fpm", php_fpm_usage, php_fpm_info, 11, read_php_fpm_stats, set_php_fpm_record);
}
