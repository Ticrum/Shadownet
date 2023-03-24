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
    while (strcmp(command, "exit") != 0)
    {
        poll(client.fds, 1, 1);
        out(client, command, param);
        in(client);
        command[0] = '\0';
        data[0] = '\0';
        data2[0] = '\0';
        scanf("%s %s %s", command, param[0], param[1]);
    }
    return 1;
}

