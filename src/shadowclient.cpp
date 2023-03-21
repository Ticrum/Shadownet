#include <shadownet.hh>

ef::shadowclient::shadowclient(int myip,
                               int myport)
    : ip(myip), port(myport), isdownloading(false), waiting(false)
{
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    fcntl(0, F_SETFL, O_NONBLOCK);
    fds[0].fd = fd;
    fds[0].events = POLLOUT | POLLIN;
    mysock.sin_family = AF_INET;
    mysock.sin_port = (in_port_t)myport;
    mysock.sin_addr = (struct in_addr)ip.full;//INADDR_ANY;

    isdownloading = false;
    waiting = false;
    sockget = mysock;
    s = sizeof(struct sockaddr);
    bind(fd, (struct sockaddr *)&mysock, (socklen_t)s);
}


