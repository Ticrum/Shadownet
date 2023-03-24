#include <shadownet.hh>

int ef::shadowclient::find_sendto(std::vector<subrequest *> & sendto,
                                  uint32_t     ip,
                                  uint16_t     port)
{
    int compt;

    compt = 0;
    printf("find sendto ipc %d ip %d portc %d portc %d\n", sendto[compt]->user.ip.full, ip, sendto[compt]->user.port, port);
    while (compt < (int)sendto.size() && (sendto[compt]->user.ip.full != ip || sendto[compt]->user.port != port))
        compt += 1;
    if (compt == (int)sendto.size())
        return -1;
    return compt;
}
