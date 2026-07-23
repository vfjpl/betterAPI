#include "tcp_utils.h"
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

///https://en.wikipedia.org/wiki/Berkeley_sockets


int tcp_client_connect(const char* host, const char* port)
{
	struct addrinfo hints =
	{
		/*.ai_flags =*/ 0,
		/*.ai_family =*/ PF_INET,
		/*.ai_socktype =*/ SOCK_STREAM,
		/*.ai_protocol =*/ IPPROTO_TCP,
	};
	struct addrinfo* list;

	int retval = getaddrinfo(host, port, &hints, &list);
	if(retval != 0)
	{
		return -abs(retval);
	}

	for(struct addrinfo* ptr = list; ptr != NULL; ptr = ptr->ai_next)
	{
		int client_fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if(client_fd < 0)
		{
			continue;
		}
		if(fcntl(client_fd, F_SETFD, FD_CLOEXEC) < 0)
		{
			close(client_fd);
			continue;
		}
		if(connect(client_fd, ptr->ai_addr, ptr->ai_addrlen) < 0)
		{
			close(client_fd);
			continue;
		}

		freeaddrinfo(list);
		return client_fd;
	}

	freeaddrinfo(list);
	return 0;
}


int tcp_client_connect_u16(const char* host, uint16_t port)
{
	char buff[16];
	sprintf(buff, "%hu", port);
	return tcp_client_connect(host, buff);
}


int tcp_server_create(uint16_t port, bool set_NONBLOCK)
{
	struct sockaddr_in addr =
	{
		/*.sin_family =*/ AF_INET,
		/*.sin_port =*/ htons(port),
		/*.sin_addr =*/ {/*.s_addr =*/ htonl(INADDR_ANY)},
	};
	int opt = 1;

	int server_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(server_fd < 0)
	{
		return -1;
	}
	if(fcntl(server_fd, F_SETFD, FD_CLOEXEC) < 0)
	{
		close(server_fd);
		return -1;
	}
	if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
	{
		close(server_fd);
		return -1;
	}
	if(bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
	{
		close(server_fd);
		return -1;
	}
	if(listen(server_fd, 1) < 0)
	{
		close(server_fd);
		return -1;
	}
	if(set_NONBLOCK && fcntl(server_fd, F_SETFL, O_NONBLOCK | O_NDELAY) < 0)
	{
		close(server_fd);
		return -1;
	}

	return server_fd;
}


int tcp_server_accept(int server_fd, struct sockaddr* addr, socklen_t* addrlen, bool set_NONBLOCK)
{
	int client_fd = accept(server_fd, addr, addrlen);
	if(client_fd < 0)
	{
		return -1;
	}
	if(fcntl(client_fd, F_SETFD, FD_CLOEXEC) < 0)
	{
		close(client_fd);
		return -1;
	}
	if(set_NONBLOCK && fcntl(client_fd, F_SETFL, O_NONBLOCK | O_NDELAY) < 0)
	{
		close(client_fd);
		return -1;
	}

	return client_fd;
}
