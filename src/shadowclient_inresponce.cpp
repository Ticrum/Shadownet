#include <shadownet.hh>

static bool notalreadysent(std::vector<ef::request *>   message,
                           int                          index)
{
    int compt;

    compt = 0;
    while (compt < (int)message[index]->sendto.size())
    {
        if ((int)message[index]->sendto[compt]->user.isvalid == 1)
            return false;
        compt += 1;
    }
    return true;
}

static bool hasfinish(std::vector<ef::subrequest *> sub)
{
    int compt;

    compt = 0;
    while (compt < (int)sub.size())
    {
        if (sub[compt]->user.isvalid == 0)
            return false;
        compt += 1;
    }
    return true;
}

void ef::shadowclient::inresponce(ef::packet & pack)
{
    int index;
    int index2;
    request *req;

    index = find_messagesent(pack.filename, 1);
    if (index == -1)
        return;
    index2 = find_sendto(messagesent[index]->sendto, *(uint32_t *)&sockget.sin_addr, (uint16_t)sockget.sin_port);
    if (index2 == -1)
        return;
    if (pack.nbrpacket == 0)
        messagesent[index]->sendto[index2]->user.isvalid = 2;
    else
    {
        messagesent[index]->sendto[index2]->user.isvalid = 1;
        if ((pack.iporigin != ip.full || pack.portorigin != port) && notalreadysent(messagesent, index))
        {
            sockget.sin_port = (in_port_t)htons(messagesent[index]->from.port);
            sockget.sin_addr = (struct in_addr)messagesent[index]->from.ip.full;
            sendto(fd, (char *)&pack, sizeof(pack), 0, (struct sockaddr *)&sockget, (socklen_t)s);
        }
    }
    if (hasfinish(messagesent[index]->sendto))
    {
        updatefile(index, pack.filename);
        if ((pack.iporigin != ip.full || pack.portorigin != port) && pack.nbrpacket == 0)
        {
            pack.nbrpacket = 0;
            sockget.sin_port = (in_port_t)htons(messagesent[index]->from.port);
            sockget.sin_addr = (struct in_addr)messagesent[index]->from.ip.full;
            sendto(fd, (char *)&pack, sizeof(pack), 0, (struct sockaddr *)&sockget, (socklen_t)s);
        }
        req = messagesent[index];
        messagesent[index] = messagesent.back();
        messagesent.back() = req;
        messagesent.pop_back();
    }
}
