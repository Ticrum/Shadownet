#include <shadownet.hh>

int ef::shadowclient::find_knownfile(char *file)
{
    int compt;

    compt = 0;
    while (compt < (int)knownfile.size() && strcmp(knownfile[compt]->filename, file) != 0)
        compt += 1;
    if (compt == (int)knownfile.size())
        return -1;
    return compt;
}

