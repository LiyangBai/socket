// Client.cpp : 定义控制台应用程序的入口点
//sockets编程发生在应用层和传输层之间
//客户端调用API次序：WSAStartup()->socket()->connect()->send()->closesocket()->WSACleanup()
#include <stdio.h>
#define    BUF_SZIE    64
#include "winsock2.h"
#pragma comment(lib, "ws2_32.lib")      //告诉编译器先去链接lib这个文件库

int main(int argc, char* argv[])
{
    WSADATA            wsad;             //WSADATA变量
    SOCKET             sHost;            //服务器套接字
    SOCKADDR_IN        servAddr;         //服务器地址
    char            buf[BUF_SZIE];       //接收数据缓冲区
    int                retVal;           //返回值
    
    //初始化套接字动态库
    if (WSAStartup(MAKEWORD(2,2), &wsad) != 0)
    {
        printf("初始化套接字失败!\n");
        return -1;
    }
    
    //创建套接字
    sHost=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);    
    if(INVALID_SOCKET == sHost)
    {
        printf("创建套接字失败!\n");
        WSACleanup();//释放套接字资源
        return  -1;
    }

    //设置服务器地址
    servAddr.sin_family =AF_INET;                //TCP/IP协议族
    servAddr.sin_addr.s_addr = inet_addr("49.140.161.140");  //IP地址
    servAddr.sin_port = htons((short)2016);   //端口号
    int    nServAddlen  = sizeof(servAddr);

    //连接服务器
    retVal=connect(sHost,(LPSOCKADDR)&servAddr, sizeof(servAddr));    //LPSOCKADDR指向一个内存插槽的指针
    if(SOCKET_ERROR == retVal)
    {
        printf("连接服务器失败!\n");    
        closesocket(sHost);    //关闭套接字
        WSACleanup();        //释放套接字资源
        return -1;
    }
	else	printf("连接成功，主人您可以通信了......\n\**************************************************************************************************\n");

    //向服务器发送数据
	while(1){
		ZeroMemory(buf, BUF_SZIE);    //将系统分配的内存清零
		scanf("%s", buf);
		retVal = send(sHost, buf, strlen(buf), 0);
		if (SOCKET_ERROR == retVal)
		{
			printf("发送数据失败!\n");
			closesocket(sHost);    //关闭套接字
			WSACleanup();        //释放套接字资源
			return -1;
		}	
	}

    //退出
    closesocket(sHost);    //关闭套接字
    WSACleanup();        //释放套接字资源
    return 0;
}