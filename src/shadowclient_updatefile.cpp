#include <shadownet.hh>

void ef::shadowclient::updatefile(int index,
                                  char *file)
{
    int compt;
    int index2;
    int index3;
    fileinfo *newfile;
    contact *newcont;
    subrequest *tempreq;

    index2 = find_knownfile(file);
    if (index2 == -1)
    {
        newfile = new fileinfo;
        strcpy(newfile->filename, file);
        newfile->compt = 0;
        knownfile.push_back(newfile);
        index2 = knownfile.size() - 1;
    }
    compt = 0;
    while (compt < (int)messagesent[index]->sendto.size())
    {
        if (messagesent[index]->sendto[compt]->user.isvalid == 1)
        {
            index3 = find_hasfile(knownfile[index2], messagesent[index]->sendto[compt]->user.ip.full, messagesent[index]->sendto[compt]->user.port);
            if (index3 == -1)
            {
                newcont = new contact;
                newcont->ip.full = messagesent[index]->sendto[compt]->user.ip.full;
                newcont->port = messagesent[index]->sendto[compt]->user.port;
                newcont->isvalid = 1;
                knownfile[index2]->hasfile.push_back(newcont);
                index3 = knownfile[index2]->hasfile.size() - 1;
            }
            knownfile[index2]->hasfile[index3]->isvalid = 1;
            tempreq = messagesent[index]->sendto.back();
            messagesent[index]->sendto.back() = messagesent[index]->sendto[compt];
            messagesent[index]->sendto[compt] = tempreq;
            messagesent[index]->sendto.pop_back();
        }
    }
}
