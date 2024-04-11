#include <iostream>
#include "synfilesharing/synfilesharing.h"

int main() {
    std::vector<std::string> paths = {
            "/home/synalice/CLionProjects/synfilesharing/examples/example.txt",
            "/home/synalice/CLionProjects/synfilesharing/examples/helloword.md"
    };

    std::unique_ptr<synfs::IClient> client = synfs::makeClient().build();
    client->sendFiles(synfs::constants::DEFAULT_SERVER_NAME, paths);
    std::cout << "Привет, Мир!" << '\n';
}
