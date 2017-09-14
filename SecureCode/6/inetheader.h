#ifndef _INETHEADER_H
#define _INETHEADER_H

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;

#pragma pack(1) 
typedef struct ether_header_t{
    BYTE des_hw_addr[6];    //Ŀ��MAC��ַ
    BYTE src_hw_addr[6];    //ԴMAC��ַ
    WORD frametype;         //���ݳ��Ȼ�����
} ether_header_t;   //header of the ethernet frame

typedef struct arp_header_t{
    WORD hw_type;           //16λӲ������
    WORD prot_type;         //16λЭ������
    BYTE hw_addr_len;       //8λӲ����ַ����
    BYTE prot_addr_len;     //8λЭ���ַ����
    WORD flag;              //16λ������
    BYTE send_hw_addr[6];   //ԴEthernet����ַ
    DWORD send_prot_addr;   //ԴIP��ַ
    BYTE des_hw_addr[6];    //Ŀ��Ethernet����ַ
    DWORD des_prot_addr;    //Ŀ��IP��ַ
} arp_header_t;

typedef struct ip_header_t{
    BYTE hlen_ver;          //ͷ�����ȺͰ汾��Ϣ
    BYTE tos;               //8λ��������
    WORD total_len;         //16λ�ܳ���
    WORD id;                //16λ��ʶ��
    WORD flag;              //3λ��־+13λƬƫ��
    BYTE ttl;               //8λ����ʱ��
    BYTE protocol;          //8λ�ϲ�Э���    
    WORD checksum;          //16λУ���
    DWORD src_ip;           //32λԴIP��ַ
    DWORD des_ip;           //32λĿ��IP��ַ
} ip_header_t;

typedef struct udp_header_t{
    WORD src_port;          //Դ�˿�
    WORD des_port;          //Ŀ�Ķ˿� 
    WORD len;               //���ݰ��ܳ���
    WORD checksum;          //У���
} udp_header_t;

typedef struct tcp_header_t{
    WORD src_port;          //Դ�˿�
    WORD des_port;          //Ŀ�Ķ˿�
    DWORD seq;              //seq��
    DWORD ack;              //ack��
    BYTE len_res;           //ͷ����
    BYTE flag;              //��־�ֶ� 
    WORD window;            //���ڴ�С
    WORD checksum;          //У���
    WORD urp;               //����ָ�� 
} tcp_header_t;

typedef struct icmp_header_t{
    BYTE type;              //8λ����     
    BYTE code;              //8λ����
    WORD checksum;          //16λУ���
    WORD id;                //16λ��ʶ��   
    WORD seq;               //16λ���к�
} icmp_header_t;

typedef struct arp_packet_t{
    ether_header_t etherheader;
    arp_header_t arpheader;
} arp_packet_t;

typedef struct ip_packet_t{
    ether_header_t etherheader;
    ip_header_t ipheader;
} ip_packet_t;

typedef struct tcp_packet_t{
    ether_header_t etherheader;
    ip_header_t ipheader;
    tcp_header_t tcpheader;
} tcp_packet_t;

typedef struct udp_packet_t{
    ether_header_t etherheader;
    ip_header_t ipheader;
    udp_header_t udpheader;
} udp_packet_t;

typedef struct icmp_packet_t{
    ether_header_t etherheader;
    ip_header_t ipheader;
    icmp_header_t icmpheader;
} icmp_packet_t;

#pragma pack()

#endif
