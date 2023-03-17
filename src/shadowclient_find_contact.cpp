#include <shadownet.hh>

int ef::shadowclient::find_hasfile(ef::fileinfo *file,
                                   uint32_t     ip,
                                   uint16_t     port)
{
    int compt;

    compt = 0;
    while (compt < (int)file->hasfile.size() && ((file->hasfile[compt]->ip.full == ip && file->hasfile[compt]->port == port) == 0))
        compt += 1;
    if (compt == (int)file->hasfile.size())
        return -1;
    return compt;
}
