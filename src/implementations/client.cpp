
#include <string>
#include <vector>
#include <iostream>
#include "synfilesharing/implementations/client.h"
#include "synfilesharing/constants.h"

namespace synfs::internal {
    synfs::internal::Client::~Client() = default;

    void synfs::internal::Client::sendFiles(std::string destination, std::vector<std::string> filePaths) {
        std::unique_ptr<sdbus::IProxy> fsProxy = createProxy(destination);
        try {
            fsProxy->callMethod(synfs::constants::METHOD_SENDFILES_NAME)
                    .onInterface(synfs::constants::INTERFACE_NAME)
                    .withArguments(filePaths);
        } catch (const sdbus::Error &e) {
            std::cerr << "Получена ошибка " << e.getName() << " с сообщением " << e.getMessage() << std::endl;
        }
    }

    void synfs::internal::Client::setDBusName(const std::string &name) {
        this->_clientName = name;
    }

    void synfs::internal::Client::createConnection() {
        this->_dbusConnection = sdbus::createSessionBusConnection(this->_clientName);
    }

    std::unique_ptr<sdbus::IProxy> synfs::internal::Client::createProxy(const std::string &destination) {
        return sdbus::createProxy(
                std::move(this->_dbusConnection), destination, synfs::constants::OBJECT_PATH
        );
    }

    synfs::internal::Client::Client() = default;
}