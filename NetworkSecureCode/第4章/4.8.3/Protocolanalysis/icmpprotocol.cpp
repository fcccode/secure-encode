//--------------------------------------------------------------------//
//                ���ߣ�������                                        //
//                �鼮�������簲ȫ��̼�����ʵ����                    //
//--------------------------------------------------------------------// 
#include "stdafx.h"
#include "ProtocolanalysisDlg.h"
#include <stdio.h>
#include <sys/types.h>
#include "icmpprotocol.h"
#include "sniffer.h"
struct IcmpHeader DisplayIcmp;
extern HWND hWnd;
void ICMPOperation(const unsigned char* packetdata)
{
	struct ICMP* Icmp;
	Icmp = (struct ICMP *) packetdata;
	sprintf(DisplayIcmp.type, "%d", Icmp->Type);
	switch (Icmp->Type)
	{
	case 0:
		sprintf(DisplayIcmp.information, "%s", "����Ӧ��");
		break;
	case 8:
		sprintf(DisplayIcmp.information, "%s", "��������");
		break;
	case 13:
		sprintf(DisplayIcmp.information, "%s", "ʱ�������");
		break;
	case 14:
		sprintf(DisplayIcmp.information, "%s", "ʱ���Ӧ��");
		break;
	case 17:
		sprintf(DisplayIcmp.information, "%s", "��ַ��������");
		break;
	case 18:
		sprintf(DisplayIcmp.information, "%s", "��ַ����Ӧ��");
		break;
	default:
		sprintf(DisplayIcmp.information, "%s", "ICMP����δ֪");
		break;
	}
	sprintf(DisplayIcmp.code, "%d", Icmp->Code);
	sprintf(DisplayIcmp.checksum, "%d", ntohs(Icmp->Checksum));
	::PostMessage(hWnd, WM_MY_MESSAGE_ICMP, 0, 0);
	return;
}

