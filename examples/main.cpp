#include <iostream>
#include "synfilesharing/synfs.h"

int main(int argc, char *argv[]) {
    std::vector<std::string> allowedMimeTypes = {
            "application/pdf",
            "image/svg+xml",
    };

    auto onReceiveFiles = [](const std::vector<std::string> &filePaths) {
        for (const std::string &filePath: filePaths) {
            std::cout << filePath << '\n';
        }
    };

    std::unique_ptr<synfs::IServer> server = synfs::makeServer()
            .setAllowedMimeTypes(allowedMimeTypes)
            .setOnReceiveFiles(onReceiveFiles)
            .build();
}
