#ifndef SYNFILESHARING_SERVER_BUILDER_H
#define SYNFILESHARING_SERVER_BUILDER_H

#include <filesystem>
#include <fstream>
#include <vector>
#include <functional>

#include "synfilesharing/interfaces/i_server.h"
#include "synfilesharing/implementations/server.h"
#include "synfilesharing/constants.h"

namespace synfs {
    class ServerBuilder {
    public:
        ServerBuilder() = default;

        [[maybe_unused]] synfs::ServerBuilder &setDBusName(std::string_view name);

        synfs::ServerBuilder &setExecFlag(std::string_view execFlag = synfs::constants::DEFAULT_EXEC_FLAG);

        synfs::ServerBuilder &saveRunViaDBusTo(bool &runViaDBus);

        synfs::ServerBuilder &setAllowedFileExtensions(const std::vector<std::string> &allowedFileExtensions);

        synfs::ServerBuilder &saveResultsTo(std::shared_ptr<std::vector<std::string>> saveTo);

        std::unique_ptr<synfs::IServer> build();

    private:
        std::string _dBusName = synfs::constants::DEFAULT_SERVER_NAME;
        std::string _execFlag = synfs::constants::DEFAULT_EXEC_FLAG;
        std::shared_ptr<std::vector<std::string>> _saveResultsTo;
        bool *_saveRunViaDBusTo = nullptr;
        std::unique_ptr<synfs::internal::Server> _server = std::make_unique<synfs::internal::Server>();
    private:
        void generateServiceFile();

        static std::string getPathToCurrentExecutable();

        static std::string getPathToOtherServiceFiles();

        static void writeServiceFile(
                std::string_view pathToExecutable,
                std::string_view pathToOtherServiceFiles,
                std::string_view dBusName,
                std::string_view execFlag
        );
    };
}

#endif //SYNFILESHARING_SERVER_BUILDER_H
