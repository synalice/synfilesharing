#include "synfilesharing/synfilesharing.h"

int main() {
    std::vector<std::string> paths = {
            "aboba",
            "helloword",
            "womp-womp"
    };

    std::unique_ptr<synfs::IClient> client = synfs::makeClient().build();
    client->sendFiles(synfs::constants::DEFAULT_SERVER_NAME, paths);
}