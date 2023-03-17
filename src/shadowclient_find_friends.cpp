#include <shadownet.hh>

int ef::shadowclient::find_friends(char     *cip,
                                   char     *cport)
{
    int compt;
    addrip ip;
    int port;

    compt = 0;
    chartoip(cip, ip);
    port = atoi(cport);
    while (compt < (int)friends.size() && ((friends[compt]->ip.full == ip.full && friends[compt]->port == port) == 0))
        compt += 1;
    if (compt == (int)friends.size())
        return -1;
    return compt;
}
