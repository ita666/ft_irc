#ifndef _INCLUDES_HPP_
#define _INCLUDES_HPP_


#include <sys/socket.h> // for socket(), bind(), listen(), accept(), send(), recv()
#include <netinet/in.h> // for sockaddr_in and inet_ntoa()
#include <arpa/inet.h>  // for htons(), htonl(), ntohs(), ntohl(), inet_addr()
#include <sys/epoll.h> // for epoll_create(), epoll_ctl(), epoll_wait()
#include <unistd.h>     // for close()
#include <fcntl.h>      // for fcntl()
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

#endif