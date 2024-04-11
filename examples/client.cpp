#include <iostream>
#include "synfilesharing/synfilesharing.h"

int main() {
    std::vector<std::string> paths = {
            "/some/absolute/path/text_file.txt",
            "/some/absolute/path/markdown_file.md"
    };

    std::unique_ptr<synfs::IClient> client = synfs::makeClient().build();
    client->sendFiles(synfs::constants::DEFAULT_SERVER_NAME, paths);
    std::cout << "Привет, Мир!" << '\n';
}
