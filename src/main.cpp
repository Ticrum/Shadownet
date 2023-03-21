#include <shadownet.hh>

int main(int    a,
         char   **inputs)
{
    char command[60];
    char *param[2];
    char data[60];
    char data2[60];
    ef::addrip myip;
    int myport;

    if (a != 3)
        return 0;
    chartoip(inputs[1], myip);
    myport = atoi(inputs[2]);
    printf("%d %d.%d.%d.%d port %d\n", myip.full, myip.split[0], myip.split[1], myip.split[2], myip.split[3], myport);
    ef::shadowclient client(myip.full, myport);//48879

    command[0] = '\0';
    data[0] = '\0';
    data2[0] = '\0';
    param[0] = data;
    param[1] = data2;
/*
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    fcntl(0, F_SETFL, O_NONBLOCK);
    fds[0].fd = fd;
    fds[0].events = POLLOUT | POLLIN;
    mysock.sin_family = AF_INET;
    mysock.sin_port = (in_port_t)htons(48879);
    mysock.sin_addr = (struct in_addr)myip.full;//INADDR_ANY;

    sockget = mysock;
    s = sizeof(struct sockaddr);
    bind(fd, (struct sockaddr *)&mysock, (socklen_t)s);
*/
    //scanf("%s %s %s", command, param[0], param[1]);
    while (strcmp(command, "exit") != 0)
    {
        poll(client.fds, 1, 1);
        //printf("%s\n", command);
        //printf("%s %s %s\n", command, param[0], param[1]);
        out(client, command, param);
        in(client);
        command[0] = '\0';
        data[0] = '\0';
        data2[0] = '\0';
        scanf("%s %s %s", command, param[0], param[1]);
    }
    return 1;
}

