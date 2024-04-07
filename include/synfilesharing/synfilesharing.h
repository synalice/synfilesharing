#ifndef SYNDBUS_SYNFILESHARING_H
#define SYNDBUS_SYNFILESHARING_H

#include <string>
#include <utility>
#include <vector>
#include <sdbus-c++/sdbus-c++.h>
#include <iostream>

namespace synfilesharing {
    class Manager {
    public:
        Manager() {
            this->dbusConnection = sdbus::createSessionBusConnection();
        };

        explicit Manager(std::string serviceName) : serviceName(std::move(serviceName)) {
            this->dbusConnection = sdbus::createSessionBusConnection(this->serviceName);
        };

        void setAllowedMimeTypes(std::vector<std::string> mimeTypes) {
            this->allowedMimeTypes = std::move(mimeTypes);
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
    private:
        std::unique_ptr<sdbus::IProxy> createFileSharingProxy(const std::string &destinationBusName) {
            return sdbus::createProxy(
                    std::move(this->dbusConnection),
                    destinationBusName,
                    this->OBJECT_PATH
            );
        }

        const std::string INTERFACE_NAME = "ru.synfilesharing.FileSharing";
        const std::string OBJECT_PATH = "/ru/synfilesharing/filesharing";
        const std::string METHOD_SENDFILES_NAME = "sendFiles";

        std::string serviceName;
        std::vector<std::string> allowedMimeTypes;

        std::unique_ptr<sdbus::IConnection> dbusConnection;
    };
}

#endif //SYNDBUS_SYNFILESHARING_H
