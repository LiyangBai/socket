// Server.cpp : �������̨Ӧ�ó������ڵ�
// �������˵��ô���WSAStartup()->Socket()->Bind()->Listen()->Accept()->Recv()->CloseSocket()->WSACleanup()
#include "stdio.h"
#include "winsock2.h"
#define  BUF_SZIE     64
#pragma comment(lib, "ws2_32.lib")

int main(int argc, char* argv[])
{
    WSADATA            wsad;            //WSADATA����
    SOCKET            Server;           //�������׽���
    SOCKET            Client;           //�ͻ����׽���
    SOCKADDR_IN        addrServ;        //��������ַ
    char            buf[BUF_SZIE];      //�������ݻ�����
    int                retVal;          //����ֵ

    //��ʼ���׽��ֶ�̬��
    if (WSAStartup(MAKEWORD(2,2),&wsad) != 0)
    {
        printf("��ʼ���׽��ֶ�̬��ʧ��!\n");
        return 1;
    }
    
    //�����׽���
    Server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);    
    if(INVALID_SOCKET == Server)
    {
        printf("�����׽���ʧ��!\n");
        WSACleanup();//�ͷ��׽�����Դ;
        return  -1;
    }
    
    //�������׽��ֵ�ַ 
    addrServ.sin_family = AF_INET;
    addrServ.sin_port = htons(2016);
    addrServ.sin_addr.s_addr = INADDR_ANY;        
    retVal = bind(Server, (LPSOCKADDR)&addrServ, sizeof(SOCKADDR_IN));       //���׽���
    if(SOCKET_ERROR == retVal)
    {    
        printf("���׽���ʧ��!\n");
        closesocket(Server);    //�ر��׽���
        WSACleanup();            //�ͷ��׽�����Դ
        return -1;
    }
    
    //��ʼ���� 
    retVal = listen(Server,1);   //�������ӵĸ���
    if(SOCKET_ERROR == retVal)
    {
        printf("����ʧ��!\n");        
        closesocket(Server);    //�ر��׽���
        WSACleanup();            //�ͷ��׽�����Դ
        return -1;
    }
    else	printf("���ڼ���......\n");

    //���ܿͻ�������
    sockaddr_in addrClient;
    int addrClientlen = sizeof(addrClient);
    Client = accept(Server,(sockaddr FAR*)&addrClient, &addrClientlen);
    if(INVALID_SOCKET == Client)
    {
        printf("���ܿͻ�������ʧ��!\n");        
        closesocket(Server);    //�ر��׽���
        WSACleanup();            //�ͷ��׽�����Դ
        return -1;
    }
    else	printf("���ӳɹ�������������ͨ����......\n\**************************************************************************************************\n");

    //���տͻ�������
	while(1){
		ZeroMemory(buf, BUF_SZIE);           //��ϵͳ������ڴ�����
		retVal = recv(Client, buf, BUF_SZIE, 0);
		if (SOCKET_ERROR == retVal)
		{
			printf("���տͻ�������ʧ��!\n");        
			closesocket(Server);    //�ر��׽���
			closesocket(Client);    //�ر��׽���        
			WSACleanup();            //�ͷ��׽�����Դ
			return -1;
		}
		printf("%s\n", buf);    //�������Client���ַ���  
	}

    //�˳�
    closesocket(Server);    //�ر��׽���
    closesocket(Client);    //�ر��׽���
    WSACleanup();            //�ͷ��׽�����Դ
    return 0;
}