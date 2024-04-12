#include <iostream>
#include "synfilesharing/synfilesharing.h"

namespace synfs {
    [[maybe_unused]] void helloWorld(const std::string& str) {
        std::cout << "Hello, World and " << str << std::endl;
    }

    synfs::ServerBuilder makeServer() {
        return {};
    }

    synfs::ClientBuilder makeClient() {
        return {};
    }
}