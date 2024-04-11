
#include <string>
#include <vector>
#include <iostream>
#include "synfilesharing/implementations/client.h"
#include "synfilesharing/constants.h"

namespace synfs::internal {
    void Client::sendFiles(std::vector<std::string> filePaths) {
        std::unique_ptr<sdbus::IProxy> fsProxy = createProxy(synfs::constants::DEFAULT_SERVER_NAME);
        try {
            fsProxy->callMethod(synfs::constants::METHOD_SENDFILES_NAME)
                    .onInterface(synfs::constants::INTERFACE_NAME)
                    .withArguments(filePaths);
        } catch (const sdbus::Error &e) {
            std::cerr << "Получена ошибка " << e.getName() << " с сообщением " << e.getMessage() << std::endl;
        }
    }

    void Client::setDBusName(const std::string &name) {
        this->_clientName = name;
    }

    void Client::createConnection() {
        if (this->_clientName.empty()) {
            this->_dbusConnection = sdbus::createSessionBusConnection();
        } else {
            this->_dbusConnection = sdbus::createSessionBusConnection(this->_clientName);
        }
    }

    std::unique_ptr<sdbus::IProxy> Client::createProxy(const std::string &destination) {
        return sdbus::createProxy(
                std::move(this->_dbusConnection), destination, synfs::constants::OBJECT_PATH
        );
    }

    Client::Client() = default;
}