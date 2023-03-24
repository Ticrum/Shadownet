#include <shadownet.hh>

void ef::shadowclient::downloading(void)
{
    packet pack;
    int compt;
    request *req;
    subrequest *sub;

    if (isdownloading == false)
        return;
    if (waiting)
        return;
    strcpy(pack.filename, filename);
    pack.type = 2;
    pack.iporigin = ip.full;
    pack.portorigin = port;
    pack.nbrpacket = currpacket;
    req = new request;
    req->from.ip.full = ip.full;
    req->from.port = port;
    req->origin.ip.full = ip.full;
    req->origin.port = port;
    strcpy(req->filename, filename);
    req->type = 2;
    req->nbrpacket = currpacket;
    sub = new subrequest;
    sub->user.ip.full = curfileinfo->hasfile[curfileinfo->compt]->ip.full;
    sub->user.port = curfileinfo->hasfile[curfileinfo->compt]->port;
    sub->time = time(NULL);
    req->sendto.push_back(sub);
    messagesent.push_back(req);

    sockget.sin_port = (in_port_t)htons(curfileinfo->hasfile[curfileinfo->compt]->port);
    sockget.sin_addr = (struct in_addr)curfileinfo->hasfile[curfileinfo->compt]->ip.full;
    sendto(fd, (char *)&pack, sizeof(pack), 0, (struct sockaddr *)&sockget, (socklen_t)s);
    waiting = true;
    curfileinfo->compt += 1;
    if (curfileinfo->compt == (int)curfileinfo->hasfile.size())
        curfileinfo->compt = 0;
    compt = 0;
    while (curfileinfo->hasfile[curfileinfo->compt]->isvalid == 2 && compt < (int)curfileinfo->hasfile.size())
    {
        curfileinfo->compt += 1;
        if (curfileinfo->compt == (int)curfileinfo->hasfile.size())
            curfileinfo->compt = 0;
        compt += 1;
    }
}
