/*
    Date: 2018/01/18
    Author: shpdqyfan
    profile: define basic behavior of socket   
*/

#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h>

namespace IpcMsg{
namespace Socket{
    const int MAX_CONN_NUM = 5;

    int createSock(sa_family_t family, int stype);
    int setNonBlock(int sfd);
    int bindTo(int sfd, const struct sockaddr* saddr, int len);
    int listenTo(int sfd);
    int acceptFrom(int sfd, struct sockaddr* saddr);
    int connectTo(int sfd, const struct sockaddr* saddr);
    void closeFd(int sfd);
    void shutdownFd(int sfd, int flag);
    ssize_t recvMsgFrom(int sfd, void* buf, int size);
    //Used in unix domain socket
    ssize_t sendMsgUdsTo(int sfd, const char* sockFile, void* buf, int size);
}
}

#endif

