#include <shadownet.hh>

void ef::shadowclient::inmessage(ef::packet & pack)
{
    int index;
    std::string str;
    request *req;

    index = find_messagesent(pack.filename, 2);
    if (index == -1)
        return;
    if (pack.iporigin == ip.full && pack.portorigin == port)
    {
        str.append("out/");
        str.append(pack.filename);
        if (currpacket == 0)
        {
            filefd = open(&str[0], O_CREAT | O_APPEND | O_WRONLY | O_TRUNC, 0666);
            maxpacket = pack.maxpacket;
        }
        write(filefd, pack.data, pack.datalen);
        waiting = false;
        currpacket += 1;
        if (currpacket >= maxpacket)
        {
            printf("%s has finish downloading\n", filename);
            isdownloading = false;
            close(filefd);
        }
    }
    else
    {
        sockget.sin_port = (in_port_t)htons(messagesent[index]->from.port);
        sockget.sin_addr = (struct in_addr)messagesent[index]->from.ip.full;
        sendto(fd, (char *)&pack, sizeof(pack), 0, (struct sockaddr *)&sockget, (socklen_t)s);
    }
    req = messagesent[index];
    messagesent[index] = messagesent.back();
    messagesent.back() = req;
    messagesent.pop_back();
}
