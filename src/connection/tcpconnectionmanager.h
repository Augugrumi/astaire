#ifndef TCPCONNECTIONMANAGER_H
#define TCPCONNECTIONMANAGER_H

#include <memory>
#include <pistache/endpoint.h>
#include <pistache/router.h>

#include "connectionmanager.h"

namespace connection {

namespace PConn = Pistache::Http;
namespace PReq = Pistache::Rest;

class TCPConnectionManager : public ConnectionManager
{
public:
    TCPConnectionManager(const Pistache::Address &,
                         const PReq::Router &,
                         const PConn::Endpoint::Options&);

    void run();
    void stop();

private:
    const std::unique_ptr<PConn::Endpoint> server;
    const std::unique_ptr<const PReq::Router> router;
};
}

#endif // TCPCONNECTIONMANAGER_H
