#include <iostream>
#include "synfilesharing/synfilesharing.h"

int main() {
    std::string pathToHome = std::getenv("HOME");

    std::vector<std::string> paths = {
            pathToHome + "/text_file.txt",
            pathToHome + "/markdown_file.md"
    };

    std::unique_ptr<synfs::IClient> client = synfs::makeClient().build();
    client->sendFiles(paths);

    std::cout << "КЛИЕНТ: Файлы успешно отправлены!" << '\n';
}
