#include <shadownet.hh>

void ef::out(ef::shadowclient   & client,
             char               *command,
             char               **param)
{
    if (strcmp(command, "help") == 0)
        printf("\nlist of command:\naddfile\nremovefile\nforgetfile\naddfriend\nremovefriend\nrequestfile\ndownload\nresume\n\n");
    else if (strcmp(command, "addfile") == 0)
        client.addfile(param[0]);
    else if (strcmp(command, "removefile") == 0)
        client.removefile(param[0]);
    else if (strcmp(command, "forgetfile") == 0)
        client.forgetfile(param[0]);
    else if (strcmp(command, "addfriend") == 0)
        client.addfriend(param[0], param[1]);
    else if (strcmp(command, "removefriend") == 0)
        client.removefriend(param[0], param[1]);
    else if (strcmp(command, "requestfile") == 0)
    {
        if (client.fds[0].revents & POLLOUT)
            client.requestfile(param[0]);
    }
    else if (strcmp(command, "download") == 0)
    {
        if (client.fds[0].revents & POLLOUT)
            client.download(param[0], false);
    }
    else if (strcmp(command, "resume") == 0)
    {
        if (client.fds[0].revents & POLLOUT)
            client.download(param[0], true);
    }
    else if (strcmp(command, "") != 0)
        printf("unknow command. Type help for more information\n");
    client.timeout();
    client.downloading();
}

