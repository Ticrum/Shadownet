#include <shadownet.hh>

void ef::in(ef::shadowclient   & client)
{
    int msglu;
    packet pack;
    addrip ip;

    if (client.fds[0].revents & POLLIN)
    {
        msglu = recvfrom(client.fd, (char *)&pack, sizeof(packet), 0, (struct sockaddr *)&client.sockget, (socklen_t *)&client.s);
        ip.full = *(uint32_t *)&client.sockget.sin_addr;
        printf("packet:\n\nfilename %s\ntype %d\niporigin %u\nportorigin %d\nnbrpacket %d\nmaxpacket %d\n", pack.filename, pack.type, pack.iporigin, pack.portorigin, pack.nbrpacket, pack.maxpacket);
        if (pack.type == 0)
            write(1, pack.data, pack.datalen);
        printf("addresse sender %d %d ou %d.%d.%d.%d\n", ip.full, ntohs(client.sockget.sin_port), ip.split[0], ip.split[1], ip.split[2], ip.split[3]);

        if (pack.type == 2)
            client.incall(pack);
        else if (pack.type == 0)
            client.inmessage(pack);
        else if (pack.type == 3)
            client.inresponce(pack);
        else if (pack.type == 1)
            client.inrequest(pack);
    }
}
