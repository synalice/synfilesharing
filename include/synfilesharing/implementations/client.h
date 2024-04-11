#ifndef SYNFILESHARING_CLIENT_H
#define SYNFILESHARING_CLIENT_H

#include "synfilesharing/interfaces/i_client.h"
#include "sdbus-c++/sdbus-c++.h"

namespace synfs::internal {
    class Client : public synfs::IClient {
    public:
        Client();

        void sendFiles(std::vector<std::string> filePaths) override;

        void setDBusName(const std::string &name);

        void createConnection();

        std::unique_ptr<sdbus::IProxy> createProxy(const std::string& destination);
    private:
        std::string _clientName;

        std::unique_ptr<sdbus::IConnection> _dbusConnection;
    };
}

#endif //SYNFILESHARING_CLIENT_H
