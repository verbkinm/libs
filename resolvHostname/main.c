// C program to display hostname
// and IP address

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int resolvHostName(char *hostname, char ***ipList)
{
    if (hostname == NULL || ipList == NULL || *ipList != NULL)
        return -1;

    struct hostent *host_entry;
    int count = 0;

    host_entry = gethostbyname(hostname);
    if (host_entry == NULL)
        return -1;

    char **ptr = host_entry->h_addr_list;

    for (; *ptr != NULL; ++ptr, ++count);
    if (count == 0)
        return 0;

    *ipList = malloc(sizeof(char *) * count);
    if (*ipList == NULL)
        return -1;

    ptr = host_entry->h_addr_list;
    for (int i = 0; *ptr != NULL; ++ptr, ++i)
    {
        if (*ptr == NULL)
            break;


        char *ip_str = inet_ntoa(*(struct in_addr *)(*ptr));
        int ip_str_len = strlen(ip_str);

        (*ipList)[i] = (char *)calloc(1, ip_str_len + 1);
        if ((*ipList)[i] != NULL)
            strlcpy((*ipList)[i], ip_str, ip_str_len + 1);
    }

    return count;
}

void freeIpList(char **ipList, int count)
{
    if (ipList == NULL)
        return;

    if (count > 0)
    {
        for (int i = 0; i < count; ++i)
        {
            if (ipList[i] != NULL)
                free(ipList[i]);
        }

    }
    free(ipList);
}

int main()
{
    char **ipList = NULL;

    struct sockaddr_in dest_addr;

//    int count = resolvHostName("127.0.0.1", &ipList);
    int count = resolvHostName("ya.ru", &ipList);

    printf("count = %d\n", count);
    if (ipList != NULL)
    {
        for (int i = 0; i < count; ++i)
        {
            if (ipList[i] != NULL)
                printf("%d - %s\n", i, ipList[i]);
        }
    }

    freeIpList(ipList, count);

    return 0;
}
