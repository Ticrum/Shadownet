#include <shadownet.hh>

int ef::shadowclient::find_myfile(char *file)
{
    int compt;

    compt = 0;
    while (compt < (int)myfile.size() && strcmp(myfile[compt], file) != 0)
        compt += 1;
    if (compt == (int)myfile.size())
        return -1;
    return compt;
}
