#ifndef SYNDBUS_SYNFILESHARING_H
#define SYNDBUS_SYNFILESHARING_H

#include "synfilesharing/builders/server_builder.h"
#include "synfilesharing/builders/client_builder.h"

namespace synfs {
    synfs::ServerBuilder makeServer() {
        return {};
    }

    synfs::ClientBuilder makeClient() {
        return {};
    }
};

#endif //SYNDBUS_SYNFILESHARING_H
