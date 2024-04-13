#include <utility>

#include "synfilesharing/synfilesharing.h"

namespace synfs {
    [[maybe_unused]] synfs::ServerBuilder &synfs::ServerBuilder::setDBusName(std::string_view name) {
        this->_dBusName = name;
        return *this;
    }

    synfs::ServerBuilder &synfs::ServerBuilder::setExecFlag(std::string_view execFlag) {
        this->_execFlag = execFlag;
        return *this;
    }

    synfs::ServerBuilder &synfs::ServerBuilder::saveRunViaDBusTo(bool &runViaDBus) {
        this->_saveRunViaDBusTo = &runViaDBus;
        return *this;
    }

    synfs::ServerBuilder &
    synfs::ServerBuilder::setAllowedFileExtensions(const std::vector<std::string> &allowedFileExtensions) {
        this->_server->setAllowedFileExtensions(allowedFileExtensions);
        return *this;
    }

    synfs::ServerBuilder &synfs::ServerBuilder::saveResultsTo(
            std::shared_ptr<std::vector<std::string>> saveTo
    ) {
        this->_saveResultsTo = std::move(saveTo);
        return *this;
    }

    std::unique_ptr<synfs::IServer> synfs::ServerBuilder::build() {
        this->_server->setDBusName(this->_dBusName);
        this->_server->setExecFlag(this->_execFlag);

        generateServiceFile();

        this->_server->createConnection();
        this->_server->onReceiveFiles(this->_saveResultsTo);
        this->_server->setSaveRunViaDBusTo(this->_saveRunViaDBusTo);

        return std::move(this->_server);
    }

    void synfs::ServerBuilder::generateServiceFile() {
        std::string pathToExecutable = getPathToCurrentExecutable();
        std::string pathToOtherServiceFiles = getPathToOtherServiceFiles();
        writeServiceFile(pathToExecutable, pathToOtherServiceFiles, this->_dBusName, _execFlag);
    }

    std::string synfs::ServerBuilder::getPathToCurrentExecutable() {
        return std::filesystem::canonical("/proc/self/exe");
    }

    std::string synfs::ServerBuilder::getPathToOtherServiceFiles() {
        char *envVar = std::getenv("XDG_DATA_HOME");

        if (envVar == nullptr) {
            std::stringstream tmp_ss;
            tmp_ss << std::getenv("HOME") << "/.local/share/dbus-1/services";
            return tmp_ss.str();
        }

        return {envVar};
    }

    void synfs::ServerBuilder::writeServiceFile(
            std::string_view pathToExecutable,
            std::string_view pathToOtherServiceFiles,
            std::string_view dBusName,
            std::string_view execFlag
    ) {
        std::string fileName = std::string(dBusName) + ".service";
        std::string pathToServiceFile = std::string(pathToOtherServiceFiles) + "/" + fileName;
        std::ofstream serviceFile(pathToServiceFile);

        serviceFile << "[D-BUS Service]" << '\n';
        serviceFile << "Name=" << dBusName << '\n';
        serviceFile << "Exec=" << pathToExecutable << " " << execFlag << '\n';
        serviceFile.close();
    }
}