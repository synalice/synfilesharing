#ifndef SYNDBUS_SYNFILESHARING_H
#define SYNDBUS_SYNFILESHARING_H

#include "synfilesharing/builders/server_builder.h"
#include "synfilesharing/builders/client_builder.h"
#include "synfilesharing/implementations/server.h"
#include "synfilesharing/implementations/client.h"
#include "synfilesharing/interfaces/i_server.h"
#include "synfilesharing/interfaces/i_client.h"
#include "synfilesharing/constants.h"

namespace synfs {
    [[maybe_unused]] void helloWorld();

    /**
     * Возвращает создатель для создания сервера.
     * */
    synfs::ServerBuilder makeServer();

    /**
     * Возвращает создатель для создания клиента.
     * */
    synfs::ClientBuilder makeClient();
}

#endif //SYNDBUS_SYNFILESHARING_H
