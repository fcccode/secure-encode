
//--------------------------------------------------------------------//
//                ���ߣ�������                                        //
//                �鼮�������簲ȫ��̼�����ʵ����                    //
//--------------------------------------------------------------------//

#include "stdafx.h"
#include "ProtocolanalysisDlg.h"
#include <stdio.h>
#include "sniffer.h"
#include "arpprotocol.h"
struct arpheader DisplayARP;
extern HWND hWnd;
void ARPOperation(const unsigned char* packetdata)
{
	unsigned short Protocol;
	unsigned short Hardware;
	unsigned short Operation;
	struct ARP *Arp;
	sprintf(DisplayARP.HardwareLength, "%s", "");
	sprintf(DisplayARP.Hardware, "%s", "");
	sprintf(DisplayARP.OperationCode, "%s", "");
	sprintf(DisplayARP.ProtocolLength, "%s", "");
	sprintf(DisplayARP.Protocol, "%s", "");
	sprintf(DisplayARP.OperationInformatin, "%s", "");
	Arp = (struct ARP *) packetdata;
	Hardware = ntohs(Arp->Hardware);
	Protocol = ntohs(Arp->Protocol);
	Operation = ntohs(Arp->OperationCode);
	sprintf(DisplayARP.HardwareLength, "%d", ntohs(Arp->HardwareLength));
	sprintf(DisplayARP.ProtocolLength, "%d", ntohs(Arp->ProtocolLength));
	sprintf(DisplayARP.Hardware, "%d", Hardware);
	sprintf(DisplayARP.Protocol, "%d", Protocol);
	sprintf(DisplayARP.OperationCode, "%d", Operation);
	switch (Operation)
	{
	case 1:
		sprintf(DisplayARP.OperationInformatin, "%s", "ARP����");
		::PostMessage(hWnd, WM_MY_MESSAGE_ARP, 0, 0);
		break;
	case 2:
		sprintf(DisplayARP.OperationInformatin, "%s", "ARPӦ��");
		::PostMessage(hWnd, WM_MY_MESSAGE_ARP, 0, 0);
		break;
	case 3:
		printf("(RARP request)\n");
		sprintf(DisplayARP.OperationInformatin, "%s", "RARP����");
		::PostMessage(hWnd, WM_MY_MESSAGE_ARP, 0, 0);
		break;
	case 4:
		sprintf(DisplayARP.OperationInformatin, "%s", "RARPӦ��");
		::PostMessage(hWnd, WM_MY_MESSAGE_ARP, 0, 0);
		break;
	default:
		sprintf(DisplayARP.OperationInformatin, "%s", "δ֪");
		::PostMessage(hWnd, WM_MY_MESSAGE_ARP, 0, 0);
		return ;
	}
}
