#include <shadownet.hh>

void ef::shadowclient::inrequest(ef::packet & pack)
{
    int compt[2];

    if(pack->nbrpacket == 0)
        return;
    if(find_myfile(pack->filename) != -1 || find_messagesent(pack->filename) != -1)
        {
            pack->type = 3;
            pack->nbrpacket = 2;
            sendto(fd, (char *)&pack, sizeof(pack), 0, (struct sockaddr *)&sockget, (socklen_t)s);
            return;
        }
    compt[1] = friends.size();
    compt[0] = 0;
    
}
