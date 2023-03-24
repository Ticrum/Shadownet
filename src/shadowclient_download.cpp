#include <shadownet.hh>

void ef::shadowclient::download(char *file,
                                bool resume)
{
    int index;
    std::string str;

    if (isdownloading)
    {
        printf("file %s is already downloading\n", filename);
        return;
    }
    index = find_knownfile(file);
    if (index == -1 && resume == false)
    {
        printf("file %s is not known try using requestfile first\n", file);
        return;
    }
    isdownloading = true;
    waiting = false;
    if (resume == false)
    {
        strcpy(filename, file);
        currpacket = 0;
        curfileinfo = knownfile[index];
    }
    else
    {
        str.append("out/");
        str.append(filename);
        filefd = open(&str[0], O_APPEND | O_WRONLY);
        printf("filefd %d", filefd);
    }
    printf("downloading %s\n", file);
}
