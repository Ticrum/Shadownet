#include <shadownet.hh>

void ef::shadowclient::inmessage(ef::packet & pack)
{
    int index;
    std::string str;

    index = find_messagesent(pack.filename, 2);
    if (index == -1)
        return;
    if (pack.iporigin == ip.full && pack.portorigin == port)
    {
        str.append("out/");
        str.append(pack.filename);
        if (currpacket == 0)
        {
            filefd = open(&str[0], O_CREAT | O_APPEND | O_WRONLY, 0666);
            maxpacket = pack.maxpacket;
        }
        write(filefd, pack.data, pack.datalen);
        waiting = false;
        currpacket += 1;
        if (currpacket >= maxpacket)
        {
            isdownloading = false;
            close(filefd);
        }
    }
    else
    {
        sockget.sin_port = (in_port_t)htons(messagesent[index]->sendto[0]->user.port);
        sockget.sin_addr = (struct in_addr)messagesent[index]->sendto[0]->user.ip.full;
        sendto(fd, (char *)&pack, sizeof(pack), 0, (struct sockaddr *)&sockget, (socklen_t)s);
    }
}
