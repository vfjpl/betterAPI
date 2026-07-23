#ifndef TCP_UTILS_H_INCLUDED
#define TCP_UTILS_H_INCLUDED

#include <arpa/inet.h>
#include <stdbool.h>
#include <unistd.h>
#include <netdb.h>

int tcp_client_connect(const char* host, const char* port);
int tcp_client_connect_u16(const char* host, uint16_t port);

int tcp_server_create(uint16_t port, bool set_NONBLOCK);
int tcp_server_accept(int server_fd, struct sockaddr* addr, socklen_t* addrlen, bool set_NONBLOCK);

#endif // TCP_UTILS_H_INCLUDED
