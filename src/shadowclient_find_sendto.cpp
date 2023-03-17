#include <shadownet.hh>

int ef::shadowclient::find_sendto(std::vector<subrequest *> & sendto,
                                  uint32_t     ip,
                                  uint16_t     port)
{
    int compt;

    compt = 0;
    while (compt < (int)sendto.size() && ((sendto[compt]->user.ip.full == ip && sendto[compt]->user.port == port) == 0))
        compt += 1;
    if (compt == (int)sendto.size())
        return -1;
    return compt;
}
