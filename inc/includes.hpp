#ifndef _INCLUDES_HPP_
#define _INCLUDES_HPP_


#include <sys/socket.h> // for socket(), bind(), listen(), accept(), send(), recv()
#include <netinet/in.h> // for sockaddr_in and inet_ntoa()
#include <arpa/inet.h>  // for htons(), htonl(), ntohs(), ntohl(), inet_addr()
#include <sys/epoll.h> // for epoll_create(), epoll_ctl(), epoll_wait()
#include <unistd.h>    // for close()
#include <netdb.h>     //
#include <fcntl.h>     // for fcntl()
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>


using namespace std;

#endif