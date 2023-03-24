#include <shadownet.hh>

void ef::shadowclient::timeout(void)
{
    int compt;
    int compt2;
    int index;
    packet pack;
    request *req;

    compt = 0;
    while (compt < (int)messagesent.size())
    {
        //printf("tourverif\n");
        if (messagesent[compt]->type == 2)
        {
            //printf("enter verif\n");
            if (messagesent[compt]->sendto[0]->time + 3 <= time(NULL))
            {
                printf("timeout %ld %d!!\n", time(NULL), messagesent[compt]->sendto[0]->time);
                index = find_knownfile(messagesent[compt]->filename);
                //printf("before modif ok %d %d %d\n", knownfile[index]->compt, knownfile[index]->hasfile[knownfile[index]->compt]->isvalid == 2, (int)knownfile[index]->hasfile.size());
                //printf("before modif ok %d %d %d\n", knownfile[index]->compt, knownfile[index]->hasfile[1]->isvalid == 2, (int)knownfile[index]->hasfile.size());
                knownfile[index]->hasfile[knownfile[index]->compt]->isvalid = 2;
                //printf("before pass ok %d %d %d\n", knownfile[index]->compt, knownfile[index]->hasfile[knownfile[index]->compt]->isvalid == 2, (int)knownfile[index]->hasfile.size());
                knownfile[index]->compt += 1;
                if (knownfile[index]->compt >= (int)knownfile[index]->hasfile.size())
                    knownfile[index]->compt = 0;
                compt2 = 0;
                //printf("first pass ok %d %d %d\n", knownfile[index]->compt, knownfile[index]->hasfile[knownfile[index]->compt]->isvalid == 2, (int)knownfile[index]->hasfile.size());
                while (compt2 < (int)knownfile[index]->hasfile.size() && knownfile[index]->hasfile[knownfile[index]->compt]->isvalid == 2)
                {
                    knownfile[index]->compt += 1;
                    if (knownfile[index]->compt >= (int)knownfile[index]->hasfile.size())
                        knownfile[index]->compt = 0;
                    //printf("tour %d %d\n", knownfile[index]->compt, knownfile[index]->hasfile[knownfile[index]->compt]->isvalid == 2);
                    compt2 += 1;
                }
                if (compt2 >= (int)knownfile[index]->hasfile.size())
                {
                    //printf("command fail, no friends has the file %s anymore\n", messagesent[compt]->filename);
                    if (messagesent[compt]->origin.ip.full == ip.full && messagesent[compt]->origin.port == port)
                    {
                        close(filefd);
                        isdownloading = false;
                        waiting = false;
                    }
                    req = messagesent[compt];
                    messagesent[compt] = messagesent.back();
                    messagesent.back() = req;
                    messagesent.pop_back();
                    return;
                }
                printf("timeout: retrying\n");
                messagesent[compt]->sendto[0]->user.ip.full = knownfile[index]->hasfile[knownfile[index]->compt]->ip.full;
                messagesent[compt]->sendto[0]->user.port = knownfile[index]->hasfile[knownfile[index]->compt]->port;
                messagesent[compt]->sendto[0]->time = time(NULL);
                strcpy(pack.filename, messagesent[compt]->filename);
                pack.type = messagesent[compt]->type;
                pack.iporigin = messagesent[compt]->origin.ip.full;
                pack.portorigin = messagesent[compt]->origin.port;
                pack.nbrpacket = messagesent[compt]->nbrpacket;
                sockget.sin_port = (in_port_t)htons(knownfile[index]->hasfile[knownfile[index]->compt]->port);
                sockget.sin_addr = (struct in_addr)knownfile[index]->hasfile[knownfile[index]->compt]->ip.full;
                sendto(fd, (char *)&pack, sizeof(pack), 0, (struct sockaddr *)&sockget, (socklen_t)s);
                knownfile[index]->compt += 1;
                /*
                if (knownfile[index]->compt >= (int)knownfile[index]->hasfile.size())
                    knownfile[index]->compt = 0;
                compt2 = 0;
                while (compt2 < (int)knownfile[index]->hasfile.size() && knownfile[index]->hasfile[knownfile[index]->compt]->isvalid == 2)
                {
                    knownfile[index]->compt += 1;
                    if (knownfile[index]->compt >= (int)knownfile[index]->hasfile.size())
                        knownfile[index]->compt = 0;
                    compt2 += 1;
                }
                */
            }
        }
        compt += 1;
    }
}

