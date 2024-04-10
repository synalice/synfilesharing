#include "synfilesharing/implementations/server.h"
#include "synfilesharing/constants.h"

namespace synfs::internal {
    void Server::runIfFlagIsSet(int argc, char **argv) {
        if (argc < 2 || argv[1] != this->_execFlag) {
            return;
        }
        this->_dbusConnection->enterEventLoop();
    }

    void Server::setDBusName(const std::string &name) {
        this->_serverName = name;
    }

    void Server::setAllowedFileExtensions(std::vector<std::string> allowedFileExtensions) {
        this->_allowedFileExtensions = std::move(allowedFileExtensions);
    }

    void Server::setOnReceiveFiles(const std::function<void(std::vector<std::string>)> &callback) {
        this->_fileSharingObject->registerMethod(synfs::constants::METHOD_SENDFILES_NAME)
                .onInterface(synfs::constants::INTERFACE_NAME)
                .withNoReply()
                .withInputParamNames("filePaths")
                .implementedAs([callback](const std::vector<std::string>& filePaths) {
                    preCallbackExecution(filePaths);
                    callback(filePaths);
                });
        this->_fileSharingObject->finishRegistration();
    }

    void Server::setExecFlag(const std::string &execFlag) {
        this->_execFlag = execFlag;
    }

    void Server::createConnection() {
        this->_dbusConnection = sdbus::createSessionBusConnection(this->_serverName);
        this->_fileSharingObject = sdbus::createObject(
                *this->_dbusConnection, synfs::constants::OBJECT_PATH
        );
    }
}