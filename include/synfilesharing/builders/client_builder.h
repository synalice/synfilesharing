#ifndef SYNFILESHARING_CLIENT_BUILDER_CPP
#define SYNFILESHARING_CLIENT_BUILDER_CPP

#include <memory>

#include "synfilesharing/interfaces/i_client.h"
#include "synfilesharing/implementations/client.h"
#include "synfilesharing/constants.h"

namespace synfs {
    class ClientBuilder {
    public:
        ClientBuilder() = default;

        synfs::ClientBuilder &setDBusName(std::string_view name);

        std::unique_ptr<synfs::IClient> build();

    private:
        std::string _dBusName = synfs::constants::DEFAULT_SERVER_NAME;
        std::unique_ptr<synfs::internal::Client> _client = std::make_unique<synfs::internal::Client>();
    };
}


#endif //SYNFILESHARING_CLIENT_BUILDER_CPP
