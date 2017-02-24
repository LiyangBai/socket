// Client.cpp : �������̨Ӧ�ó������ڵ�
//sockets��̷�����Ӧ�ò�ʹ����֮��
//�ͻ��˵���API����WSAStartup()->socket()->connect()->send()->closesocket()->WSACleanup()
#include <stdio.h>
#define    BUF_SZIE    64
#include "winsock2.h"
#pragma comment(lib, "ws2_32.lib")      //���߱�������ȥ����lib����ļ���

int main(int argc, char* argv[])
{
    WSADATA            wsad;             //WSADATA����
    SOCKET             sHost;            //�������׽���
    SOCKADDR_IN        servAddr;         //��������ַ
    char            buf[BUF_SZIE];       //�������ݻ�����
    int                retVal;           //����ֵ
    
    //��ʼ���׽��ֶ�̬��
    if (WSAStartup(MAKEWORD(2,2), &wsad) != 0)
    {
        printf("��ʼ���׽���ʧ��!\n");
        return -1;
    }
    
    //�����׽���
    sHost=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);    
    if(INVALID_SOCKET == sHost)
    {
        printf("�����׽���ʧ��!\n");
        WSACleanup();//�ͷ��׽�����Դ
        return  -1;
    }

    //���÷�������ַ
    servAddr.sin_family =AF_INET;                //TCP/IPЭ����
    servAddr.sin_addr.s_addr = inet_addr("49.140.161.140");  //IP��ַ
    servAddr.sin_port = htons((short)2016);   //�˿ں�
    int    nServAddlen  = sizeof(servAddr);

    //���ӷ�����
    retVal=connect(sHost,(LPSOCKADDR)&servAddr, sizeof(servAddr));    //LPSOCKADDRָ��һ���ڴ��۵�ָ��
    if(SOCKET_ERROR == retVal)
    {
        printf("���ӷ�����ʧ��!\n");    
        closesocket(sHost);    //�ر��׽���
        WSACleanup();        //�ͷ��׽�����Դ
        return -1;
    }
	else	printf("���ӳɹ�������������ͨ����......\n\**************************************************************************************************\n");

    //���������������
	while(1){
		ZeroMemory(buf, BUF_SZIE);    //��ϵͳ������ڴ�����
		scanf("%s", buf);
		retVal = send(sHost, buf, strlen(buf), 0);
		if (SOCKET_ERROR == retVal)
		{
			printf("��������ʧ��!\n");
			closesocket(sHost);    //�ر��׽���
			WSACleanup();        //�ͷ��׽�����Դ
			return -1;
		}	
	}

    //�˳�
    closesocket(sHost);    //�ر��׽���
    WSACleanup();        //�ͷ��׽�����Դ
    return 0;
}