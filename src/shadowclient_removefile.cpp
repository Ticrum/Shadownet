#include <shadownet.hh>

void ef::shadowclient::removefile(char *file)
{
    int index;
    int index2;
    char *tempchar;
    contact *tempcontact;
    fileinfo *tempfileinfo;

    index = find_myfile(file);
    if (index == -1)
    {
        printf("file %s not found\n", file);
        return;
    }
    tempchar = myfile[index];
    myfile[index] = myfile.back();
    myfile.back() = tempchar;
    myfile.pop_back();
    index = find_knownfile(file);
    index2 = find_hasfile(knownfile[index], ip.full, port);
    tempcontact = knownfile[index]->hasfile[index2];
    knownfile[index]->hasfile[index2] = knownfile[index]->hasfile.back();
    knownfile[index]->hasfile.back() = tempcontact;
    knownfile[index]->hasfile.pop_back();
    if (knownfile[index]->hasfile.size() == 0)
    {
        tempfileinfo = knownfile[index];
        knownfile[index] = knownfile.back();
        knownfile.back() = tempfileinfo;
        knownfile.pop_back();
    }
    printf("file %s deleted\n", file);
}

