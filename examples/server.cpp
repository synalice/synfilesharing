#include <iostream>
#include <vector>
#include <memory>
#include "synfilesharing/synfilesharing.h"

int main(int argc, char *argv[]) {
    std::vector<std::string> allowedFileExtensions = {".txt", ".md",};
    auto receivedFiles = std::make_shared<std::vector<std::string>>();

    std::unique_ptr<synfs::IServer> server = synfs::makeServer()
            .setAllowedFileExtensions(allowedFileExtensions)
            .setExecFlag(synfs::constants::DEFAULT_EXEC_FLAG)
            .saveResultsTo(receivedFiles)
            .build();

    server->runIfFlagIsSet(argc, argv);

    for (const std::string &item: *receivedFiles) {
        std::cout << item;
        if (&item != &receivedFiles->back()) {
            std::cout << ", ";
        }
    }

    std::cout << '\n' << "Привет, Мир!" << '\n';
}
