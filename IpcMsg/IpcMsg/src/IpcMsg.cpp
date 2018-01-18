/*
    Date: 2018/01/18
    Author: shpdqyfan
    profile: define APIs for the operation of socket of IpcMsg lib  
*/

#include <iostream>
#include <sys/un.h>
#include <string.h>
#include <stddef.h>

#include "Socket.h"
#include "IpcMsg/IpcMsg.h"

using namespace IpcMsg;

int IpcMsg::createUdsIpc(const char* sockFile)
{
    //create unix socket
    int sfd = Socket::createSock(AF_UNIX, SOCK_DGRAM);
    if(0 > sfd)
    {
        std::cout<<"createUdsIpc, create socket error"<<std::endl;
        return -1;
    }

    //bind sfd to addr
    struct sockaddr_un saddr;
    saddr.sun_family = AF_UNIX;
    strcpy(saddr.sun_path, sockFile);
    std::cout<<"createUdsIpc, uds file="<<saddr.sun_path<<std::endl;

    int len = offsetof(struct sockaddr_un, sun_path) + sizeof(saddr.sun_path);
    if(0 > Socket::bindTo(sfd, (struct sockaddr*)&saddr, len))
    {
        std::cout<<"createUdsIpc, bind error"<<std::endl;
        Socket::closeFd(sfd);
        return -1;
    }
    
    return sfd;
}

int IpcMsg::sendUdsIpcMsg(int sfd, const char* sockFile, void* buf, int size)
{
    if(-1 == Socket::sendMsgUdsTo(sfd, sockFile, buf, size))
    {
        std::cout<<"sendUdsIpcMsg, error"<<std::endl;
        return -1;
    }

    return 0;
}

int IpcMsg::recvUdsIpcMsg(int sfd, void* buf, int size)
{
    if(-1 == Socket::recvMsgFrom(sfd, buf, size))
    {
        std::cout<<"recvUdsIpcMsg, error"<<std::endl;
        return -1;
    }
    
    return 0;
}

void IpcMsg::closeIpc(int sfd, int flag)
{
    Socket::shutdownFd(sfd, flag);
    Socket::closeFd(sfd);
}

void IpcMsg::close(int sfd)
{
    Socket::closeFd(sfd);
}

