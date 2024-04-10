#include <iostream>
#include <vector>
#include <memory>
#include "synfilesharing/synfilesharing.h"

int main(int argc, char *argv[]) {
    std::vector<std::string> allowedFileExtensions = {
            ".pdf",
            ".svg",
    };

    auto onReceiveFiles = [](const std::vector<std::string> &filePaths) {
        for (std::string_view filePath: filePaths) {
            std::cout << filePath << '\n';
        }
    };

    std::unique_ptr<synfs::IServer> server = synfs::makeServer()
            .setAllowedFileExtensions(allowedFileExtensions)
            .setOnReceiveFiles(onReceiveFiles)
            .build();

    server->runIfFlagIsSet(argc, argv);

    std::cout << "Флага не было и сервер не запустился. Привет, Мир!" << '\n';
}
