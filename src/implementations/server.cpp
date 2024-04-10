#include "synfilesharing/implementations/server.h"

namespace synfs::internal {
    void synfs::internal::Server::runIfFlagIsSet(int argc, char **argv) {
        if (argv[1] != this->_execFlag) {
            return;
        }
        this->_dbusConnection->enterEventLoop();
    }

    void synfs::internal::Server::setDBusName(const std::string &name) {
        this->_serverName = name;
    }

    void synfs::internal::Server::setAllowedMimeTypes(std::vector<std::string> allowedMimeTypes) {
        this->_allowedMimeTypes = std::move(allowedMimeTypes);
    }

    void synfs::internal::Server::setOnReceiveFiles(const std::function<void(std::vector<std::string>)> &callback) {
        this->_fileSharingObject->registerMethod(synfs::constants::METHOD_SENDFILES_NAME)
                .onInterface(synfs::constants::INTERFACE_NAME)
                .implementedAs(callback);
    }

    void synfs::internal::Server::setExecFlag(const std::string &execFlag) {
        this->_execFlag = execFlag;
    }

    void synfs::internal::Server::createConnection() {
        this->_dbusConnection = sdbus::createSessionBusConnection(this->_serverName);
        this->_fileSharingObject = sdbus::createObject(
                *this->_dbusConnection, synfs::constants::OBJECT_PATH
        );
    }
}