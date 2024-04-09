//
// Created by synalice on 09.04.24.
//

#ifndef SYNFILESHARING_CLIENT_H
#define SYNFILESHARING_CLIENT_H

#include <string>
#include <utility>
#include <vector>
#include "sdbus-c++/sdbus-c++.h"
#include <iostream>
#include <functional>

namespace synfs::internal {
    class Manager {
    public:
        Manager() {
            this->dbusConnection = sdbus::createSessionBusConnection();
        };

        explicit Manager(std::string serviceName) : serviceName(std::move(serviceName)) {
            this->dbusConnection = sdbus::createSessionBusConnection(this->serviceName);
            this->fileSharingObject = createFileSharingObject();
        };

        void setAllowedMimeTypes(std::vector<std::string> mimeTypes) {
            this->allowedMimeTypes = std::move(mimeTypes);
            this->fileSharingObject = createFileSharingObject();
        }

        void sendFiles(const std::string &destinationBusName, const std::vector<std::string> &filePaths) {
            std::unique_ptr<sdbus::IProxy> fileSharingProxy = createFileSharingProxy(destinationBusName);
            try {
                fileSharingProxy->callMethod(this->METHOD_SENDFILES_NAME)
                        .onInterface(this->INTERFACE_NAME)
                        .withArguments(filePaths);
            } catch (const sdbus::Error &e) {
                std::cerr << "Error \""
                          << e.getName()
                          << "\" while sending files. Message: \""
                          << e.getMessage()
                          << "\""
                          << std::endl;
            }
        };

        void setOnSendFiles(const std::function<void(std::vector<std::string>)>& callback) {
            this->fileSharingObject->registerMethod(this->METHOD_SENDFILES_NAME)
                    .onInterface(this->INTERFACE_NAME)
                    .implementedAs(callback);
        };

        void run() {
            this->dbusConnection->enterEventLoop();
        }
    private:
        std::unique_ptr<sdbus::IProxy> createFileSharingProxy(const std::string &destinationBusName) {
            return sdbus::createProxy(
                    std::move(this->dbusConnection),
                    destinationBusName,
                    this->OBJECT_PATH
            );
        }

        std::unique_ptr<sdbus::IObject> createFileSharingObject() {
            return sdbus::createObject(*this->dbusConnection, this->OBJECT_PATH);
        }

        const std::string INTERFACE_NAME = "ru.synfs.FileSharing";
        const std::string OBJECT_PATH = "/ru/synfs/filesharing";
        const std::string METHOD_SENDFILES_NAME = "sendFiles";

        std::string serviceName;
        std::vector<std::string> allowedMimeTypes;

        std::unique_ptr<sdbus::IConnection> dbusConnection;
        std::unique_ptr<sdbus::IObject> fileSharingObject;
    };
}

#endif //SYNFILESHARING_CLIENT_H
