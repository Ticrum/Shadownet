#include <shadownet.hh>

int ef::shadowclient::find_messagesent(char *file,
                                       int  type)
{
    int compt;

    compt = 0;
    while (compt < (int)messagesent.size() && (strcmp(messagesent[compt]->filename, file) != 0 || messagesent[compt]->type != type))
        compt += 1;
    if (compt == (int)messagesent.size())
        return -1;
    return compt;
}
