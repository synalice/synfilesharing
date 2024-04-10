#include <string_view>
#include "synfilesharing/builders/client_builder.h"

namespace synfs {
    synfs::ClientBuilder &synfs::ClientBuilder::setDBusName(std::string_view name) {
        return *this;
    }

    std::unique_ptr<synfs::IClient> synfs::ClientBuilder::build() {
        this->_client->setDBusName(this->_dBusName);
        this->_client->createConnection();

        return std::move(this->_client);
    }
}