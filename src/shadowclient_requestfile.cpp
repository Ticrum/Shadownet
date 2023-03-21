#include <shadownet.hh>

void ef::shadowclient::requestfile(char *file)
{
    int compt;
    int index;
    request *newreq;
    subrequest *newsub;
    packet pack;

    index = find_messagesent(file, 1);
    if (index != -1)
    {
        printf("request for %s already sent\n", file);
        return;
    }
    newreq = new request;
    newreq->from.ip = ip;
    newreq->from.port = port;
    newreq->origin.ip = ip;
    newreq->origin.port = port;
    strcpy(newreq->filename, file);
    newreq->type = 1;
    compt = 0;
    while (compt < (int)friends.size())
    {
        newsub = new subrequest;
        newsub->user.ip.full = friends[compt]->ip.full;
        newsub->user.port = friends[compt]->port;
        newsub->user.isvalid = 0;
        newsub->time = time(NULL);
        newreq->sendto.push_back(newsub);
        strcpy(pack.filename, file);
        pack.type = 1;
        pack.iporigin = ip.full;
        pack.portorigin = port;
        pack.nbrpacket = 1;
        sockget.sin_port = (in_port_t)htons(friends[compt]->port);
        sockget.sin_addr = (struct in_addr)friends[compt]->ip.full;
        sendto(fd, (char *)&pack, sizeof(pack), 0, (struct sockaddr *)&sockget, (socklen_t)s);
        compt += 1;
    }
    messagesent.push_back(newreq);
    printf("file %s requested\n", file);
}
