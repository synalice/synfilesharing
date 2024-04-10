#include "synfilesharing/synfilesharing.h"

namespace synfs {
    synfs::ServerBuilder &synfs::ServerBuilder::setDBusName(std::string_view name) {
        this->_dBusName = name;
        return *this;
    }

    synfs::ServerBuilder &synfs::ServerBuilder::setExecFlag(std::string_view execFlag) {
        this->_execFlag = execFlag;
        return *this;
    }

    synfs::ServerBuilder &synfs::ServerBuilder::setAllowedMimeTypes(const std::vector<std::string> &allowedMimeTypes) {
        this->_server->setAllowedMimeTypes(allowedMimeTypes);
        return *this;
    }

    synfs::ServerBuilder &synfs::ServerBuilder::setOnReceiveFiles(
            const std::function<void(std::vector<std::string>)> &callback
    ) {
        this->onReceiveFiles = callback;
        return *this;
    }

    std::unique_ptr<synfs::IServer> synfs::ServerBuilder::build() {
        this->_server->setDBusName(this->_dBusName);
        this->_server->setExecFlag(this->_execFlag);

        generateServiceFile();

        this->_server->createConnection();
        this->_server->setOnReceiveFiles(this->onReceiveFiles);

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