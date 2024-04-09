#ifndef SYNFILESHARING_SERVER_BUILDER_H
#define SYNFILESHARING_SERVER_BUILDER_H

#include <memory>

#include "synfilesharing/implementations/server.h"
#include "synfilesharing/interfaces/i_server.h"

namespace synfs {
    class ServerBuilder {
    public:
        ServerBuilder() = delete;

        synfs::ServerBuilder& setDBusName(const std::string &name) {
            this->_dBusName = name;
            return *this;
        }

        synfs::ServerBuilder& setExecFlag(const std::string &execFlag = synfs::constants::DEFAULT_EXEC_FLAG) {
            this->_execFlag = execFlag;
            return *this;
        }

        synfs::ServerBuilder& setAllowedMimeTypes(const std::vector<std::string> &allowedMimeTypes) {
            this->_server.setAllowedMimeTypes(allowedMimeTypes);
            return *this;
        }

        synfs::ServerBuilder& setOnReceiveFiles(const std::function<void(std::vector<std::string>)> &callback) {
            this->_server.setOnReceiveFiles(callback);
            return *this;
        }

        std::unique_ptr<synfs::IServer> build() {
            this->_server.setDBusName(this->_dBusName);
            this->_server.setExecFlag(this->_execFlag);

            generateServiceFile();

            this->_server.createConnection();
            return std::make_unique<synfs::internal::Server>(std::move(this->_server));
        }
    private:
        std::string _dBusName = synfs::constants::DEFAULT_SERVER_NAME;
        std::string _execFlag = synfs::constants::DEFAULT_EXEC_FLAG;
        synfs::internal::Server _server;
    private:
        void generateServiceFile() {
            
        }
    };
}

#endif //SYNFILESHARING_SERVER_BUILDER_H
