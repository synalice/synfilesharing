#include <iostream>
#include "synfilesharing/synfilesharing.h"

int main() {
    std::vector<std::string> paths = {
            "aboba.pdf",
            "helloword.svg",
    };

    std::unique_ptr<synfs::IClient> client = synfs::makeClient().build();
    client->sendFiles(synfs::constants::DEFAULT_SERVER_NAME, paths);
    std::cout << "Привет, Мир!" << '\n';
}
