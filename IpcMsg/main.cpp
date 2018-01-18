/*
    Date: 2018/01/18
    Author: shpdqyfan
    profile: test file
*/

#include <iostream>
#include <unistd.h>

#include "IpcMsg/IpcMsg.h"

using namespace IpcMsg;

static const char udsPath[] = "/home/yqian1/testing/Unix_Domain_Socket_Addr/ipc.socket";

int main()
{
    std::cout<<"Test ipcmsg lib"<<std::endl;

    unlink(udsPath);

    int sfd = IpcMsg::createUdsIpc(udsPath);
    if(0 > sfd)
    {
        std::cout<<"createUdsIpc error"<<std::endl;
        return 1;
    }
    else
    {
        std::cout<<"createUdsIpc succ"<<std::endl;
    }

    IpcMsg::close(sfd);

    return 0;
}

