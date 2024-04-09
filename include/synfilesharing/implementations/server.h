#ifndef SYNFILESHARING_SERVER_H
#define SYNFILESHARING_SERVER_H

#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <functional>

#include "sdbus-c++/sdbus-c++.h"

#include "synfilesharing/constants.h"
#include "synfilesharing/interfaces/i_server.h"

namespace synfs::internal {
    class Server : public synfs::IServer {
    public:
        void perform(int argc, char **argv) override {

        }

    public:
        Server() = default;

        void setDBusName(const std::string &name) {
            this->_serverName = name;
        }

        void setAllowedMimeTypes(std::vector<std::string> allowedMimeTypes) {
            this->_allowedMimeTypes = std::move(allowedMimeTypes);
        }

        void setOnReceiveFiles(const std::function<void(std::vector<std::string>)> &callback) {
            this->_fileSharingObject->registerMethod(synfs::constants::METHOD_SENDFILES_NAME)
                    .onInterface(synfs::constants::INTERFACE_NAME)
                    .implementedAs(callback);
        };

        void setExecFlag(const std::string &execFlag) {
            this->_execFlag = execFlag;
        }

        void createConnection() {
            this->_dbusConnection = sdbus::createSessionBusConnection(this->_serverName);
            this->_fileSharingObject = sdbus::createObject(
                    *this->_dbusConnection, synfs::constants::OBJECT_PATH
            );
        }
    private:
        std::string _serverName;
        std::string _execFlag;
        std::vector<std::string> _allowedMimeTypes;

        std::unique_ptr<sdbus::IConnection> _dbusConnection;
        std::unique_ptr<sdbus::IObject> _fileSharingObject;
    };
};

#endif //SYNFILESHARING_SERVER_H
