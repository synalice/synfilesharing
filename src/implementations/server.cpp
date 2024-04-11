#include "synfilesharing/implementations/server.h"
#include "synfilesharing/constants.h"

#include <filesystem>
#include <algorithm>
#include <utility>

namespace synfs::internal {
    void Server::run(int argc, char **argv) {
        if (argc < 2 || argv[1] != this->_execFlag) {
            return;
        }
        this->_dbusConnection->enterEventLoop();
    }

    void Server::setDBusName(const std::string &name) {
        this->_serverName = name;
    }

    void Server::setAllowedFileExtensions(std::vector<std::string> allowedFileExtensions) {
        this->_allowedFileExtensions = std::move(allowedFileExtensions);
    }

    void Server::onReceiveFiles(std::shared_ptr<std::vector<std::string>> saveTo) {
        this->_saveTo = std::move(saveTo);
        this->_fileSharingObject->registerMethod(synfs::constants::METHOD_SENDFILES_NAME)
                .onInterface(synfs::constants::INTERFACE_NAME)
                .withNoReply()
                .withInputParamNames("filePaths")
                .implementedAs([this](const std::vector<std::string> &filePaths)  {
                    preCallbackExecution(filePaths);
                    *this->_saveTo = filePaths;
                    this->_dbusConnection->leaveEventLoop();
                });
        this->_fileSharingObject->finishRegistration();
    }

    void Server::setExecFlag(const std::string &execFlag) {
        this->_execFlag = execFlag;
    }

    void Server::createConnection() {
        this->_dbusConnection = sdbus::createSessionBusConnection(this->_serverName);
        this->_fileSharingObject = sdbus::createObject(
                *this->_dbusConnection, synfs::constants::OBJECT_PATH
        );
    }

    void Server::preCallbackExecution(const std::vector<std::string> &filePaths) {
        verifyPathValidity(filePaths);
        verifyFileExtensions(filePaths);
    }

    void Server::verifyPathValidity(const std::vector<std::string> &filePaths) {
        namespace fs = std::filesystem;
        std::vector<std::string> invalidPaths;

        for (const std::string &strPath: filePaths) {
            fs::path pathPath = fs::path(strPath);

            if (!exists(pathPath) || !is_regular_file(pathPath)) {
                invalidPaths.push_back(strPath);
            }
        }

        if (!invalidPaths.empty()) {
            std::stringstream errorMsg;
            errorMsg << "Данные файлы не существуют: ";

            for (const std::string &path: invalidPaths) {
                errorMsg << "\"" << path << "\"";
                if (&invalidPaths.back() != &path) {
                    errorMsg << ", ";
                }
            }

            this->_dbusConnection->leaveEventLoop();
            throw sdbus::Error(
                    synfs::constants::INTERFACE_NAME + ".Error",
                    errorMsg.str()
            );
        }
    }

    void Server::verifyFileExtensions(const std::vector<std::string> &filePaths) {
        namespace fs = std::filesystem;
        std::vector<std::string> invalidPaths;

        for (const std::string &strPath: filePaths) {
            fs::path pathPath = fs::path(strPath);
            std::string fileExt = std::string(pathPath.extension());

            bool extIsForbidden = std::ranges::find(
                    this->_allowedFileExtensions, fileExt) == this->_allowedFileExtensions.end();

            if (extIsForbidden) {
                invalidPaths.push_back(strPath);
            }
        }

        if (!invalidPaths.empty()) {
            std::stringstream errorMsg;
            errorMsg << "Файлы данных типов запрещены: ";

            for (const std::string &path: invalidPaths) {
                errorMsg << "\"" << path << "\"";
                if (&invalidPaths.back() != &path) {
                    errorMsg << ", ";
                }
            }

            this->_dbusConnection->leaveEventLoop();
            throw sdbus::Error(
                    synfs::constants::INTERFACE_NAME + ".Error",
                    errorMsg.str()
            );
        }
    }
}
