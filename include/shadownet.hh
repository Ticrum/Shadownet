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
#include <vector>
#include <time.h>
#include <string>

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
        uint8_t type; // 0 message, 1 request (for response), 2 call (formessage), 3 response
        uint32_t iporigin;
        uint16_t portorigin;
        uint32_t nbrpacket;//if request 0=fail, 1=ask, 2=succes
        uint32_t maxpacket;

        uint16_t datalen;
        char data[1024];
    };

    struct contact
    {
        addrip ip;
        uint16_t port;
        uint8_t isvalid; // if request 0=wait, 1=succes, 2=fail
    };

    struct fileinfo
    {
        char filename[60];
        std::vector<contact *> hasfile;
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
        contact origin;
        char filename[60];
        uint8_t type;
        uint32_t nbrpacket;
        std::vector<subrequest *> sendto;
    };

    class shadowclient
    {
    public:
        shadowclient(int ip,
                     int port);
        void addfriend(char *ip,
                       char *port);
        void removefriend(char *ip,
                          char *port);
        void requestfile();

        void addfile(char *file);

        void removefile(char *file);

        void forgetfile(char *file);

        void requestfile(char *file);

        void download(char *file, bool resume);

        void downloading(void);

        void timeout(void);

        void incall(packet & pack);

        void inmessage(packet & pack);

        void inresponce(packet & pack);

        void inrequest(packet & pack);
        int fd;
        int s;
        struct pollfd fds[1];
        struct sockaddr_in mysock;
        struct sockaddr_in sockget;
    private:
        int find_knownfile(char *file);
        int find_myfile(char *file);
        int find_hasfile(fileinfo *file,
                         uint32_t ip,
                         uint16_t port);
        int find_friends(char *ip,
                         char *port);
        int find_messagesent(char   *file,
                             int    type);
        int find_sendto(std::vector<subrequest *> & sendto,
                        uint32_t     ip,
                        uint16_t     port);
        void updatefile(int index,
                        char *file);
        addrip ip;
        uint16_t port;
        bool isdownloading;
        bool waiting;
        char filename[60];
        int filefd;
        int currpacket;
        int maxpacket;
        fileinfo *curfileinfo;
        std::vector<contact *> friends;
        std::vector<fileinfo *> knownfile;
        std::vector<request *> messagesent;
        std::vector<char *> myfile;
    };

    void chartoip(char          *ip,
                  addrip        & myip);

    void out(shadowclient       & client,
             char               *command,
             char               **param);

    void in(shadowclient        & client);
};// !ef

#endif //   SHADOWNET_HH
