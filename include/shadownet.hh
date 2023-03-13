#ifndef     SHADOWNET_HH
#define     SHADOWNET_HH

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <poll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <list>

namespace ef
{
    union addrip
    {
        uint32_t full;
        unsigned char split[4];
    };

    struct packet
    {
        char filename[60];
        uint8_t type; // 0 normal, 1 request, 2 call, 3 response
        uint32_t iporigin;
        uint16_t portorigin;
        uint32_t nbrpacket;
        uint32_t maxpacket;

        uint16_t datalen;
        char data[1024];
    };

    struct contact
    {
        addrip ip;
        uint16_t port;
        uint8_t isvalid;
    };

    struct fileinfo
    {
        char filename[60];
        std::list<contact> hasfile;
        int compt;
    };

    struct subrequest
    {
        contact user;
        int time;
    };

    struct request
    {
        contact from;
        addrip iporigin;
        uint16_t portorigin;
        char filename[60];
        uint8_t type;
        uint32_t nbrpacket;
        std::list<subrequest> sendto;
    };

    class shadowclient
    {
    public:
        shadowclient(int ip,
                     int port);
        void addfriend(int ip,
                       int port);
        void removefriend(int ip,
                          int port);
        void requestfile();

        int fd;
        int s;
        struct pollfd fds[1];
        struct sockaddr_in mysock;
        struct sockaddr_in sockget;
    private:
        addrip ip;
        uint16_t port;
        std::list<contact> friends;
        std::list<fileinfo> knownfile;
        std::list<request> messagesent;
        std::list<char> *myfile;
    };

    void chartoip(char          *ip,
                  addrip        & myip);

    void out(shadowclient       & client,
             char               *command,
             char               **param);

    void in(shadowclient        & client);
};// !ef

#endif //   SHADOWNET_HH
