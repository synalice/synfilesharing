#ifndef SYNFILESHARING_SERVER_H
#define SYNFILESHARING_SERVER_H

#include "synfilesharing/interfaces/i_server.h"
#include "sdbus-c++/sdbus-c++.h"

namespace synfs::internal {
    class Server : public synfs::IServer {
    public:
        Server() = default;

        void runIfFlagIsSet(int argc, char **argv) override;

        void setDBusName(const std::string &name);

        void setAllowedMimeTypes(std::vector<std::string> allowedMimeTypes);

        void setOnReceiveFiles(const std::function<void(std::vector<std::string>)> &callback);

        void setExecFlag(const std::string &execFlag);

        void createConnection();

    private:
        static void preCallbackExecution(const std::vector<std::string> &filePaths) {
            verifyMimeTypes(filePaths);
        };

        static void verifyMimeTypes(const std::vector<std::string> &filePaths) {
            for (std::string filePath : filePaths) {
            }
        };

        std::string _serverName;
        std::string _execFlag;
        std::vector<std::string> _allowedMimeTypes;

        std::unique_ptr<sdbus::IConnection> _dbusConnection;
        std::unique_ptr<sdbus::IObject> _fileSharingObject;
    };
}

#endif //SYNFILESHARING_SERVER_H
