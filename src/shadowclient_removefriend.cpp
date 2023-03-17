#include <shadownet.hh>

void ef::shadowclient::removefriend(char *ip,
                                    char *port)
{
    int index;
    contact *tempcontact;

    index = find_friends(ip, port);
    if (index == -1)
    {
        printf("friend %s %s not found\n", ip, port);
        return;
    }
    tempcontact = friends[index];
    friends[index] = friends.back();
    friends.back() = tempcontact;
    friends.pop_back();
    printf("friend %s %s deleted\n", ip, port);
}
