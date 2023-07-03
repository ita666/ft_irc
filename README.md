# ft_irc
ft_irc


Sure, let's break down each of the points and provide some initial directions and resources that may be helpful:

1. **Creating a server in C++98**: Here is a general tutorial on how to create a basic TCP server in C++ - [Simple C++ class example using serial port, ROS compatible](https://www.egr.msu.edu/classes/ece480/capstone/fall15/group01/doc/ROS%20Compatible%20C++%20Serial%20Class.pdf). Please remember that you must restrict yourself to C++98 features and libraries. 

2. **Handling multiple clients**: The server needs to handle multiple clients concurrently. This will involve setting up "worker" threads or using non-blocking IO and multiplexing. Here's an article that may be helpful - [Guide to Socket Programming in C++](https://www.geekhideout.com/sock.shtml).

3. **Non-blocking I/O operations**: Here is a guide on non-blocking IO in Linux, including some C code examples - [Non-blocking IO on Linux](https://www.scottklement.com/rpg/socktut/nonblocking.html). The principles apply equally to C++.

4. **Using poll(), select(), kqueue(), or epoll()**: This is part of handling multiple clients. They are system calls that allow your program to wait for events on a set of file descriptors (in this case, connections from clients). Here's a good comparison of these mechanisms - [select / poll / epoll: practical difference for system architects](https://medium.com/@copyconstruct/the-method-to-epolls-madness-d9d2d6378642). 

5. **Choosing an IRC client**: There are many open-source IRC clients out there. A popular one is irssi - [IRSSI User's Guide](https://irssi.org/documentation/startup/). You'll need to understand how to use this (or your chosen client) to connect to an IRC server, and what commands it sends over the wire.

6. **TCP/IP communication**: This is the fundamental protocol for sending data over the internet. Here's a basic guide on TCP/IP - [TCP/IP in C++](https://www.codeproject.com/Articles/5277553/Transmission-Control-Protocol-TCP-IP-in-Cplusplus).

7. **Implementing IRC features**: This will require you to understand the IRC protocol, specifically the commands and responses that you need to implement. Here is the IRC protocol specification - [Internet Relay Chat: Client Protocol](https://tools.ietf.org/html/rfc2812).

8. **Use of fcntl() for MacOS**: Here is the manual page for fcntl() - [fcntl man page](https://man7.org/linux/man-pages/man2/fcntl.2.html). You'll need to use it in non-blocking mode.

Please keep in mind that all these resources are to provide you with an initial understanding and starting point. You'll likely need to dig deeper into some topics as you progress with your project. Feel free to ask more specific questions as they come up.