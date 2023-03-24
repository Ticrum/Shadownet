#include <shadownet.hh>

static int filelen(char *name)
{
    int len;
    int lu;
    int fd;
    char tab[256];

    if ((fd = open(name, O_RDONLY)) == -1)
        return -1;
    lu = 1;
    len = 0;
    while (lu != 0)
    {
        lu = read(fd, tab, 256);
        len += lu;
    }
    close(fd);
    return len;
}

static int readfromfile(ef::packet & pack,
                        ef::packet & newpack)
{
    int fd;
    int compt;
    int len;
    int lu;

    if ((fd = open(pack.filename, O_RDONLY)) == -1)
        return -1;
    len = filelen(pack.filename);
    newpack.maxpacket = len / 1024;
    newpack.nbrpacket = pack.nbrpacket;
    strcpy(newpack.filename, pack.filename);
    newpack.iporigin = pack.iporigin;
    newpack.portorigin = pack.portorigin;
    if (len % 1024 != 0)
        newpack.maxpacket += 1;
    if (pack.nbrpacket >= newpack.maxpacket)
        return -1;
    compt = 0;
    while (compt < (int)pack.nbrpacket)
    {
        read(fd, newpack.data, 1024);
        compt += 1;
    }
    lu = read(fd, newpack.data, 1024);
    newpack.datalen = lu;
    close(fd);
    return 1;
}

void ef::shadowclient::incall(ef::packet & pack)
{
    int index;
    packet newpack;
    request *req;
    subrequest *sub;
    int compt;

    index = find_myfile(pack.filename);
    if (index != -1)
    {
        readfromfile(pack, newpack);
        newpack.type = 0;
        sendto(fd, (char *)&newpack, sizeof(newpack), 0, (struct sockaddr *)&sockget, (socklen_t)s);
    }
    else if ((index = find_knownfile(pack.filename)) != -1)
    {
        req = new request;
        req->from.ip.full = *(uint32_t *)&sockget.sin_addr;
        req->from.port = (uint16_t)ntohs(sockget.sin_port);
        req->origin.ip.full = pack.iporigin;
        req->origin.port = pack.portorigin;
        strcpy(req->filename, pack.filename);
        req->type = 2;
        req->nbrpacket = pack.nbrpacket;
        sub = new subrequest;
        sub->user.ip.full = knownfile[index]->hasfile[knownfile[index]->compt]->ip.full;
        sub->user.port = knownfile[index]->hasfile[knownfile[index]->compt]->port;
        sub->time = time(NULL);
        req->sendto.push_back(sub);
        messagesent.push_back(req);

        sockget.sin_port = (in_port_t)htons(knownfile[index]->hasfile[knownfile[index]->compt]->port);
        sockget.sin_addr = (struct in_addr)knownfile[index]->hasfile[knownfile[index]->compt]->ip.full;
        knownfile[index]->compt += 1;
        if (knownfile[index]->compt == (int)knownfile[index]->hasfile.size())
            knownfile[index]->compt = 0;
        compt = 0;
        while (knownfile[index]->hasfile[knownfile[index]->compt]->isvalid == 0 && compt < (int)knownfile[index]->hasfile.size())
        {
            knownfile[index]->compt += 1;
            if (knownfile[index]->compt == (int)knownfile[index]->hasfile.size())
                knownfile[index]->compt = 0;
            compt += 1;
        }
        sendto(fd, (char *)&pack, sizeof(pack), 0, (struct sockaddr *)&sockget, (socklen_t)s);
    }
}
