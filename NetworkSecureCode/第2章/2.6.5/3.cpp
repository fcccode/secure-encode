//--------------------------------------------------------------------//
//                ���ߣ�������                                        //
//                �鼮�������簲ȫ��̼�����ʵ����                    //
//--------------------------------------------------------------------//
#include "winsock.h" 
#include <stdio.h>
#include <iphlpapi.h>
#pragma comment(lib,"iphlpapi.lib")
void main()
{
    IP_ADAPTER_INFO Interface[20];
    PIP_ADAPTER_INFO NetInterface = NULL;
    DWORD Result = 0;
    unsigned long Length = sizeof(Interface);
    Result = GetAdaptersInfo(Interface, &Length);
    if (Result != NO_ERROR)
    {
        printf("GetAdaptersInfo failed error.\n");
    }
    else
    {
        NetInterface = Interface;
        while (NetInterface)
        {
            static int number;
            number++;
            printf("��%d������ӿ���Ϣ:\n", number);
            printf("���ƣ�%s\n", NetInterface->AdapterName);
            printf("��Ϣ��%s\n", NetInterface->Description);
            printf("��ַ��%ld\n", NetInterface->Address);
            printf("MAC��ַ:%02X:%02X:%02X:%02X:%02X:%02X\n", NetInterface->Address[0], NetInterface->Address[1], NetInterface->Address[2], NetInterface->Address[3], NetInterface->Address[4], NetInterface->Address[5]);
            printf("IP��ַ��%s\n", NetInterface->IpAddressList.IpAddress.String);
            printf("IP��ַ����:%s\n", NetInterface->IpAddressList.IpMask.String);
            printf("����:%s\n", NetInterface->GatewayList.IpAddress.String);
            if (NetInterface->DhcpEnabled)
            {
                printf("DHCP���ã�\n");
                printf("������:%s\n", NetInterface->DhcpServer.IpAddress.String);
                printf("����:%ld\n", NetInterface->LeaseObtained);
            }
            else
                printf("��DHCP����\n");
            if (NetInterface->HaveWins)
            {
                printf("Wins����:\n");
                printf("��Wins������:%s\n", NetInterface->PrimaryWinsServer.IpAddress.String);
                printf("��Wins������:%s\n", NetInterface->SecondaryWinsServer.IpAddress.String);
            }
            else
                printf("�޷���������\n");
            NetInterface = NetInterface->Next;
        }
    }
}
