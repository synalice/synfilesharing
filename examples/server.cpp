#include <iostream>
#include <vector>
#include <memory>
#include "synfilesharing/synfilesharing.h"

int main(int argc, char *argv[]) {
    std::vector<std::string> allowedFileExtensions = {".txt", ".md",};

    auto receivedFiles = std::make_shared<std::vector<std::string>>();
    bool runViaDBus = false;

    std::unique_ptr<synfs::IServer> server = synfs::makeServer()
            .setAllowedFileExtensions(allowedFileExtensions)
            .saveRunViaDBusTo(runViaDBus)
            .saveResultsTo(receivedFiles)
            .build();

    server->run(argc, argv);

    if (runViaDBus) {
        for (const std::string &item: *receivedFiles) {
            std::cout << item;
            if (&item != &receivedFiles->back()) {
                std::cout << ", ";
            }
        }
        std::cout << '\n' << "Привет, DBus" << '\n';
    } else {
        std::cout << '\n' << "Привет, Мир!" << '\n';
    }
}
