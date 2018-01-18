/*
    Date: 2018/01/18
    Author: shpdqyfan
    profile: define APIs for the operation of socket of IpcMsg lib  
*/

#ifndef IPCMSG_H
#define IPCMSG_H

#include <string>

namespace IpcMsg{
    int createUdsIpc(const char* sockFile);
    int sendUdsIpcMsg(int sfd, const char* sockFile, void* buf, int size);
    int recvUdsIpcMsg(int sfd, void* buf, int size);
    void closeIpc(int sfd, int flag);
    void close(int sfd);
}

#endif

