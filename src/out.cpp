#include <shadownet.hh>

void ef::out(ef::shadowclient   & client,
             char               *command,
             char               **param)
{
    if (strcmp(command, "help") == 0)
    {
        printf("\nlist of command:\naddfile\nremovefile\nforgetfile\naddfriend\nremovefriend\nrequestfile\ndownload\n\n");
    }
    else if (strcmp(command, "addfile") == 0)
    {
        printf("file %s added\n", param[0]);
        //add file in list myfile
        //add self contact to file in list knownfile if not exist create it and
        //then add the contact
    }
    else if (strcmp(command, "removefile") == 0)
    {
        printf("file %s deleted\n", param[0]);
        //del file in list myfile
        //del self contact to file in list knownfile if no contact delete file
        //in list knownfile
    }
    else if (strcmp(command, "forgetfile") == 0)
    {
        printf("forgeting %s\n", param[0]);
        //remove file in list knownfile
    }
    else if (strcmp(command, "addfriend") == 0)
    {
        printf("friend %s %s added\n", param[0], param[1]);
        //add new contact in friends
    }
    else if (strcmp(command, "removefriend") == 0)
    {
        printf("friend %s %s deleted\n", param[0], param[1]);
        //del contact in friends
    }
    else if (strcmp(command, "requestfile") == 0)
    {
        if (client.fds[0].revents & POLLOUT)
            printf("file %s requested\n", param[0]);
    }
    else if (strcmp(command, "download") == 0)
    {
        if (client.fds[0].revents & POLLOUT)
        {
            printf("downloading %s\n", param[0]);
            sendto(client.fd, "pute\n", 5, 0, (struct sockaddr *)&client.mysock, (socklen_t)client.s);
        }
    }
    else if (strcmp(command, "") != 0)
        printf("unknow command. Type help for more information\n");
}

