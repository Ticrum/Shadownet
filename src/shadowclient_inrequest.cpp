#include <shadownet.hh>

static ef::request *new_request(struct sockaddr_in & soget,
                                uint32_t & cimp,
                                uint16_t & purt,
                                char *file)
{
    ef::request *ne;

    ne = new(ef::request);
    ne->from.ip.full = *(uint32_t*)&soget.sin_addr;
    ne->from.port = (uint16_t)ntohs(soget.sin_port);
    ne->from.isvalid = 0;
    ne->origin.ip.full = cimp;
    ne->origin.port = purt;
    ne->origin.isvalid = 0;
    strcpy(ne->filename, file);
    ne->type = 1;
    ne->nbrpacket = 0;
    return ne;
}

void ef::shadowclient::inrequest(ef::packet & pack)
{
    int compt[2];
    request *ne;
    subrequest *nesub;

    if(pack.nbrpacket == 0)
        return;
    if(find_myfile(pack.filename) != -1 || find_knownfile(pack.filename) != -1)
        {
            pack.type = 3;
            pack.nbrpacket = 2;
            sendto(fd, (char *)&pack, sizeof(pack), 0, (struct sockaddr *)&sockget, (socklen_t)s);
            return;
        }
    if(find_messagesent(pack.filename, pack.type) != -1 || (int)friends.size() == 0)
        {
            pack.type = 3;
            pack.nbrpacket = 0;
            sendto(fd, (char *)&pack, sizeof(pack), 0, (struct sockaddr *)&sockget, (socklen_t)s);
            return;
        }
    compt[1] = friends.size();
    compt[0] = 0;
    ne = new_request(sockget, pack.iporigin, pack.portorigin, pack.filename);
    while (compt[0] < compt[1])
        {
            while(friends[compt[0]]->isvalid != 1 ||
                  (friends[compt[0]]->ip.full == (uint32_t)ne->from.ip.full &&  friends[compt[0]]->port == ne->from.port))
                compt[0] ++;
            if (compt[0] < compt[1])
            {
                nesub = new subrequest;
                nesub->time = time(NULL);
                nesub->user.ip.full = friends[compt[0]]->ip.full;
                nesub->user.port = friends[compt[0]]->port;
                nesub->user.isvalid = 0;
                ne->sendto.push_back(nesub);
                sockget.sin_port = (in_port_t)htons(friends[compt[0]]->port);
                sockget.sin_addr = (struct in_addr) friends[compt[0]]->ip.full;
                sendto(fd, (char *)&pack, sizeof(pack), 0, (struct sockaddr *)&sockget, (socklen_t)s);
                compt[0] ++;
            }
        }
    messagesent.push_back(ne);
}
