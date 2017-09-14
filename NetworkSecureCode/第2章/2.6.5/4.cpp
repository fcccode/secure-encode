//--------------------------------------------------------------------//
//                ���ߣ�������                                        //
//                �鼮�������簲ȫ��̼�����ʵ����                    //
//--------------------------------------------------------------------//
#include "stdio.h"
#include "pcap.h"
#pragma comment(lib,"wpcap.lib") 
#pragma comment(lib,"WS2_32.lib") 
int main()
{
    int Result, i;
    char PcapError[PCAP_ERRBUF_SIZE];
    pcap_if_t *Interface;
    pcap_if_t *NetInterface;
    Result = pcap_findalldevs(&NetInterface, PcapError);
    if (Result ==  - 1 || NetInterface == NULL)
        return FALSE;
    for (Interface = NetInterface, i = 0; Interface && i < 10; Interface = Interface->next, i++)
    {
        pcap_addr_t *a;
        printf("��%d������ӿ�:\n", i + 1);
        printf("���ƣ�%s\n", Interface->name);
        if (Interface->description)
            printf("��Ϣ��%s\n", Interface->description);
        for (a = Interface->addresses; a; a = a->next)
        {
            switch (a->addr->sa_family)
            {
                case AF_INET:
                    if (a->addr)
                        printf("IP��ַ:%s\n", inet_ntoa(((struct sockaddr_in*)a->addr)->sin_addr));
                    if (a->netmask)
                        printf("��ַ���룺%s\n", inet_ntoa(((struct sockaddr_in*)a->netmask)->sin_addr));
                    break;
                default:
                    break;
            }
        }
    }
    pcap_freealldevs(NetInterface);
    return 1;
}
