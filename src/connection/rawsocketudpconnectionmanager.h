#ifndef RAWSOCKETUDPCONNECTIONMANAGER_H
#define RAWSOCKETUDPCONNECTIONMANAGER_H

#include "config.h"
#if HAS_UDP

#include <poll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <cstring>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

#include "udpconnectionmanager.h"
#include "log.h"
#include "asynctaskexecutor.h"
#include "handler/abshandler.h"

// FIXME for test purpose only
#include <chrono>
#include <atomic>
#include <iostream>
// END FIXME

//#include "handler/abshandler.h"

namespace connection {
class RawSocketUDPConnectionManager : public UDPConnectionManager
{
public:
    RawSocketUDPConnectionManager(uint32_t, unsigned short int, handler::AbsHandler*);
    ~RawSocketUDPConnectionManager();

    void run();
    void stop();

    // TODO use promise for the async send?
    void send(int, const char*, size_t, sockaddr_in*, std::function<void(ssize_t)>&) const;
    ssize_t send(int, const char*, size_t, sockaddr_in*) const;
    ssize_t send(const char*, size_t, const char*, unsigned short int) const;

    ssize_t sound_send(int, const char*, size_t, sockaddr_in*, short = 0);

    static void counter_printer(int);

private:
    struct pollfd pollfd;
    struct sockaddr_in addr;
    socklen_t addrlen;
    char* buf;
    handler::AbsHandler* handler;
    static std::atomic_int_fast64_t ct;

};
}

#endif
#endif // RAWSOCKETUDPCONNECTIONMANAGER_H
