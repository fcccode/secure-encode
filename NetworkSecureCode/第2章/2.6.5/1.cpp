//--------------------------------------------------------------------//
//                ���ߣ�������                                        //
//                �鼮�������簲ȫ��̼�����ʵ����                    //
//--------------------------------------------------------------------//
#include "winsock.h" 
#include <stdio.h>
#pragma comment(lib,"Ws2_32.lib")
void main()
{
    WSADATA wsaData;
    char HostName[255];
    HOSTENT *Hostent;
    int Result;
    Result = WSAStartup(MAKEWORD(2, 1), &wsaData);
    if (Result == SOCKET_ERROR)
    {
        printf("WSAStartup failed with error %d\n", Result);
        return ;
    }
    Result = gethostname(HostName, 255);
    printf("��������Ϊ��%s\n", HostName);
    if (Result == SOCKET_ERROR)
    {
        printf("gethostname failed with error %d\n", WSAGetLastError());
        return ;
    }
    Hostent = (struct hostent*)malloc(sizeof(struct hostent));
    Hostent = gethostbyname(HostName);
    for (int i = 0;; i++)
    {
        printf("��%d������ӿ�:\n", i + 1);
        printf("IP��ַ��%s\n", inet_ntoa(*(IN_ADDR*)Hostent->h_addr_list[i]));
        if (Hostent->h_addr_list[i] + Hostent->h_length >= Hostent->h_name)
        {
            break;
        } 
    }
    if (WSACleanup() == SOCKET_ERROR)
    {
        printf("WSACleanup failed with error %d\n", WSAGetLastError());
        return ;
    }
}
