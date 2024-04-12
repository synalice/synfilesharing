#include <iostream>
#include "synfilesharing/synfilesharing.h"

namespace synfs {
    [[maybe_unused]] void helloWorld() {
        std::cout << "Привет, Мир!" << std::endl;
    }

    synfs::ServerBuilder makeServer() {
        return {};
    }

    synfs::ClientBuilder makeClient() {
        return {};
    }
}