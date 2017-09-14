//--------------------------------------------------------------------//
//                ���ߣ�������                                        //
//                �鼮�������簲ȫ��̼�����ʵ����                    //
//--------------------------------------------------------------------//
#include <winsock2.h>
#include <ws2tcpip.h> 
#include <stdio.h>
#pragma comment(lib,"Ws2_32.lib")
int main()
{
    WSADATA wsaData;
    SOCKET socket;
    INTERFACE_INFO netinterface[10];
    DWORD dwBytesReturned;
    int InterfaceCount;
    int Result;
    Result = WSAStartup(MAKEWORD(2, 1), &wsaData);
    if (Result == SOCKET_ERROR)
    {
        printf("WSAStartup failed with error %d\n", Result);
        return 1;
    }
    socket = WSASocket(AF_INET, SOCK_DGRAM, 0, 0, 0, 0);
    if (socket == INVALID_SOCKET)
    {
        printf("WSASocket failed with error %d\n\n", WSAGetLastError());
        return 1;
    }
    Result = WSAIoctl(socket, SIO_GET_INTERFACE_LIST, 0, 0, &netinterface, sizeof(netinterface), &dwBytesReturned, 0, 0);
    if (Result == SOCKET_ERROR)
    {
        printf("WSAIoctl failed with error %d \n", WSAGetLastError());
        return 1;
    }
    InterfaceCount = dwBytesReturned / sizeof(INTERFACE_INFO);
    printf("����ӿڸ�����%d\n", InterfaceCount);
    for (int i = 0; i < InterfaceCount; i++)
    {
        printf("\n��%d������ӿ�:\n", i + 1);
        printf("IP��ַΪ��%s\n", inet_ntoa(netinterface[i].iiAddress.AddressIn .sin_addr));
        printf("�㲥��ַΪ��%s\n", inet_ntoa(netinterface[i].iiBroadcastAddress .AddressIn .sin_addr));
        printf("��������Ϊ��%s\n", inet_ntoa(netinterface[i].iiNetmask .AddressIn .sin_addr));
        if (netinterface[i].iiFlags &IFF_POINTTOPOINT)
            printf("Point to Point����ӿ�\n");
        if (netinterface[i].iiFlags &IFF_LOOPBACK)
            printf("�ػ��ӿ�\n");
        if (netinterface[i].iiFlags &IFF_BROADCAST)
            printf("֧�ֹ㲥\n");
        if (netinterface[i].iiFlags &IFF_MULTICAST)
            printf("֧�ֶಥ\n");
        if (netinterface[i].iiFlags &IFF_UP)
            printf("�ӿ�״̬��UP\n");
        else
            printf("�ӿ�״̬��DOWN\n");
    }
    if (WSACleanup() == SOCKET_ERROR)
    {
        printf("WSACleanup failed with error %d\n", WSAGetLastError());
        return 1;
    }
    return 0;
}
