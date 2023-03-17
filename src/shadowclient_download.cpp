#include <shadownet.hh>

void ef::shadowclient::download(char *file)
{
    int index;

    if (isdownloading)
    {
        printf("file %s is already downloading", filename);
        return;
    }
    index = find_knownfile(file);
    if (index == -1)
    {
        printf("file %s is not known try using requestfile first\n", file);
        return;
    }
    isdownloading = true;
    waiting = false;
    strcpy(filename, file);
    currpacket = 0;
    curfileinfo = knownfile[index];
    printf("downloading %s\n", file);
}
