#ifndef SYNFILESHARING_SERVER_H
#define SYNFILESHARING_SERVER_H

#include "synfilesharing/interfaces/i_server.h"
#include "sdbus-c++/sdbus-c++.h"

namespace synfs::internal {
    class Server : public synfs::IServer {
    public:
        Server() = default;

        void run(int argc, char **argv) override;

        void setDBusName(const std::string &name);

        void setAllowedFileExtensions(std::vector<std::string> allowedFileExtensions);

        void onReceiveFiles(std::shared_ptr<std::vector<std::string>> saveTo);

        void setExecFlag(const std::string &execFlag);

        void createConnection();

    private:
        void preCallbackExecution(const std::vector<std::string> &filePaths);

        void verifyPathValidity(const std::vector<std::string> &filePaths);

        void verifyFileExtensions(const std::vector<std::string> &filePaths);

    private:
        std::string _serverName;
        std::string _execFlag;
        std::vector<std::string> _allowedFileExtensions;

        std::shared_ptr<std::vector<std::string>> _saveTo;

        std::unique_ptr<sdbus::IConnection> _dbusConnection;
        std::unique_ptr<sdbus::IObject> _fileSharingObject;
    };
}

#endif //SYNFILESHARING_SERVER_H
