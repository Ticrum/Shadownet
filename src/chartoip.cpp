#include <shadownet.hh>

void ef::chartoip(char          *ip,
                  ef::addrip    & myip)
{
    int compt;
    int pos;
    int posin;
    char str[4][4];

    compt = 0;
    pos = 0;
    posin = 0;
    while (ip[compt] != '\0')
    {
        if (ip[compt] == '.')
        {
            str[pos][posin] = '\0';
            pos += 1;
            posin = 0;
        }
        else
        {
            str[pos][posin] = ip[compt];
            posin += 1;
        }
        compt += 1;
    }
    str[pos][posin] = '\0';
    myip.split[0] = atoi(str[0]);
    myip.split[1] = atoi(str[1]);
    myip.split[2] = atoi(str[2]);
    myip.split[3] = atoi(str[3]);
}

