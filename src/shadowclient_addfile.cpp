#include <shadownet.hh>

void ef::shadowclient::addfile(char *file)
{
    char *filename;
    int index;
    fileinfo *newfile;
    contact *selfref;
    int tempfd;

    index = find_myfile(file);
    if (index != -1)
    {
        printf("file %s already added\n", file);
        return;
    }
    if ((tempfd = open(file, O_RDONLY)) == -1)
    {
        printf("file %s not found\n", file);
        return;
    }
    else
        close(tempfd);
    filename = new char[strlen(file)];
    strcpy(filename, file);
    myfile.push_back(filename);
    index = find_knownfile(file);
    if (index == -1)
    {
        newfile = new fileinfo;
        strcpy(newfile->filename, file);
        newfile->compt = 0;
        knownfile.push_back(newfile);
        index = knownfile.size() - 1;
    }
    selfref = new contact;
    selfref->ip = ip;
    selfref->port = port;
    selfref->isvalid = 1;
    knownfile[index]->hasfile.push_back(selfref);
    printf("file %s added\n", file);
}

