#include <iostream>
#include <vector>
#include <memory>
#include "synfilesharing/synfilesharing.h"

int main(int argc, char *argv[]) {
    std::vector<std::string> allowedFileExtensions = {".pdf", ".svg",};

    std::vector<std::string> receivedFiles;

    auto onReceiveFiles = [&receivedFiles](const std::vector<std::string>& filePaths) {
        receivedFiles = filePaths;
    };

    std::unique_ptr<synfs::IServer> server = synfs::makeServer()
            .setAllowedFileExtensions(allowedFileExtensions)
            .setOnReceiveFiles(onReceiveFiles)
            .setExecFlag(synfs::constants::DEFAULT_EXEC_FLAG)
            .build();

    server->runIfFlagIsSet(argc, argv);

    for (const auto &item: receivedFiles) {
        std::cout << item;
        if (&item != &receivedFiles.back()) {
            std::cout << ", ";
        }
    }

    std::cout << "Привет, Мир!" << '\n';
}
