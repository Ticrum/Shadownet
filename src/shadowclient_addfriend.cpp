#include <shadownet.hh>

void ef::shadowclient::addfriend(char *ip,
                                 char *port)
{
    int index;
    contact *newcontact;

    index = find_friends(ip, port);
    if (index != -1)
    {
        printf("friend %s %s already added\n", ip, port);
        return;
    }
    newcontact = new contact;
    chartoip(ip, newcontact->ip);
    newcontact->port = atoi(port);
    newcontact->isvalid = 1;
    friends.push_back(newcontact);
    printf("friend %s %s added\n", ip, port);
}
