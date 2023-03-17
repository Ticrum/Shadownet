#include <shadownet.hh>

void ef::shadowclient::forgetfile(char *file)
{
    int index;
    char *tempchar;
    fileinfo *tempfileinfo;

    index = find_knownfile(file);
    if (index == -1)
    {
        printf("file %s not found\n", file);
        return;
    }
    knownfile[index]->hasfile.clear();
    tempfileinfo = knownfile[index];
    knownfile[index] = knownfile.back();
    knownfile.back() = tempfileinfo;
    knownfile.pop_back();
    index = find_myfile(file);
    if (index != -1)
    {
        tempchar = myfile[index];
        myfile[index] = myfile.back();
        myfile.back() = tempchar;
        myfile.pop_back();
    }
    printf("forgeting %s\n", file);
}

