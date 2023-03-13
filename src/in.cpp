#include <shadownet.hh>

void ef::in(ef::shadowclient   & client)
{
    int msglu;
    char msg[128];
    addrip ip;

    if (client.fds[0].revents & POLLIN)
    {
        msglu = recvfrom(client.fd, msg, 128, 0, (struct sockaddr *)&client.sockget, (socklen_t *)&client.s);
        write(1, msg, msglu);
        write(1,"\n",1);
        ip.full = *(uint32_t *)&client.sockget.sin_addr;
        printf("addresse sender %d %d ou %d.%d.%d.%d\n", ip.full, ntohs(client.sockget.sin_port), ip.split[0], ip.split[1], ip.split[2], ip.split[3]);
    }
}
