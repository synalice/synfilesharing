#include "synfilesharing/synfilesharing.h"

int main() {
    std::unique_ptr<synfs::IServer> client = synfs::makeClient().build();
    client.
}