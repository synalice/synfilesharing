#ifndef SYNDBUS_SYNFILESHARING_H
#define SYNDBUS_SYNFILESHARING_H

#include "builders/server_builder.h"

namespace synfs {
    /**
     * Возвращает создатель для создания сервера.
     * */
    synfs::ServerBuilder makeServer();
}

#endif //SYNDBUS_SYNFILESHARING_H
