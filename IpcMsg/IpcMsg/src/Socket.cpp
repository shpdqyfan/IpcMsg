/*
    Date: 2018/01/18
    Author: shpdqyfan
    profile: define basic behavior of socket   
*/

#include <iostream>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/un.h>
#include <string.h>

#include "Socket.h"

using namespace IpcMsg;

int Socket::createSock(sa_family_t family, int stype)
{
    int sfd = socket(family, stype, 0);
    if(0 > sfd)
    {
        std::cout<<"createSock, errno="<<errno<<", "<<strerror(errno)<<std::endl;
        return -1;
    }

    std::cout<<"createSock, succ, sfd="<<sfd<<std::endl;
    
    return sfd;
}

int Socket::setNonBlock(int sfd)
{
    int flags = fcntl(sfd, F_GETFL, 0);
    if(0 > fcntl(sfd, F_SETFL, flags | O_NONBLOCK))
    {
        std::cout<<"setNonBlock, sfd="<<sfd<<", errno="<<errno<<", "<<strerror(errno)<<std::endl;
        return -1;
    }

    return 0;
}

int Socket::bindTo(int sfd, const struct sockaddr* saddr, int len)
{
    if(0 > bind(sfd, saddr, len))
    {
        std::cout<<"bindTo, sfd="<<sfd<<", errno="<<errno<<", "<<strerror(errno)<<std::endl;
        return -1;
    }

    return 0;
}

int Socket::listenTo(int sfd)
{
    if(0 > listen(sfd, MAX_CONN_NUM))
    {
        std::cout<<"listenTo, sfd="<<sfd<<", errno="<<errno<<", "<<strerror(errno)<<std::endl;
        return -1;
    }

    return 0;
}

int Socket::acceptFrom(int sfd, struct sockaddr* saddr)
{
    socklen_t slen = sizeof(sockaddr);
    int newfd = accept(sfd, saddr, &slen);
    if(0 > newfd)
    {
        std::cout<<"acceptFrom, sfd="<<sfd<<", errno="<<errno<<", "<<strerror(errno)<<std::endl;
        return -1;
    }

    return newfd;
}

int Socket::connectTo(int sfd, const struct sockaddr* saddr)
{
    int rlt = connect(sfd, saddr, sizeof saddr);
    if(0 > rlt)
    {
        std::cout<<"connectTo, sfd="<<sfd<<", errno="<<errno<<", "<<strerror(errno)<<std::endl;
        return -1;
    }

    return 0;
}

void Socket::closeFd(int sfd)
{
    close(sfd);
    
    std::cout<<"closeFd, sfd="<<sfd<<", errno="<<errno<<", "<<strerror(errno)<<std::endl;
}

void Socket::shutdownFd(int sfd, int flag)
{
    shutdown(sfd, flag);
    
    std::cout<<"shutdownFd, sfd="<<sfd<<", flag="<<flag<<", errno="<<errno<<", "<<strerror(errno)<<std::endl;
}

ssize_t Socket::recvMsgFrom(int sfd, void* buf, int size)
{
    struct iovec ioBuf[1];
    struct msghdr mhdr;

    ioBuf[0].iov_base = buf;
    ioBuf[0].iov_len = size;
    
    mhdr.msg_name = NULL;
    mhdr.msg_namelen = 0;
    mhdr.msg_iov = ioBuf;
    mhdr.msg_iovlen = 1;
    mhdr.msg_control = NULL;
    mhdr.msg_controllen = 0;
    mhdr.msg_flags = 0;
    
    int len = recvmsg(sfd, &(mhdr), 0);
    std::cout<<"recvMsgFrom, sfd="<<sfd<<", len="<<len<<", size="<<size<<std::endl;
    if(0 > len)
    {
        std::cout<<"recvMsgFrom, error1, sfd="<<sfd<<", errno="<<errno<<", "<<strerror(errno)<<std::endl;
        return -1;
    }
    else if(len != size)
    {
        std::cout<<"recvMsgFrom, error2, sfd="<<sfd<<", errno="<<errno<<", "<<strerror(errno)<<std::endl;
        return -1;
    }

    return len;
}

ssize_t Socket::sendMsgUdsTo(int sfd, const char* sockFile, void* buf, int size)
{
    struct sockaddr_un sUnAddr;
    struct iovec ioBuf[1];
    struct msghdr mhdr;

    sUnAddr.sun_family = AF_UNIX;
    strcpy(sUnAddr.sun_path, sockFile);

    ioBuf[0].iov_base = buf;
    ioBuf[0].iov_len = size;
    
    mhdr.msg_name = &sUnAddr;
    mhdr.msg_namelen = sizeof(sockaddr_un);
    mhdr.msg_iov = ioBuf;
    mhdr.msg_iovlen = 1;
    mhdr.msg_control = NULL;
    mhdr.msg_controllen = 0;
    mhdr.msg_flags = 0;
    
    int len = sendmsg(sfd, &(mhdr), 0);
    std::cout<<"sendMsgUdsTo, sfd="<<sfd<<", len="<<len<<std::endl;
    if(0 > len)
    {
        std::cout<<"sendMsgUdsTo, sfd="<<sfd<<", errno="<<errno<<", "<<strerror(errno)<<std::endl;
        return -1;
    }

    return len;
}

