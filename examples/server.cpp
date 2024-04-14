#include <iostream>
#include <vector>
#include <memory>
#include "synfilesharing/synfilesharing.h"

int main(int argc, char *argv[]) {
    // Создаём список разрешенных расширений файлов.
    std::vector<std::string> allowedFileExtensions = {".txt", ".md",};

    // Создаём вектор, в который будут сохранены пришедшие от клиента файлы.
    auto receivedFiles = std::make_shared<std::vector<std::string>>();

    // Создаём переменную, которая сообщит, был ли процесс запущен через DBus.
    bool runViaDBus = false;

    // Создаём сервер (используя builder паттерн).
    std::unique_ptr<synfs::IServer> server = synfs::makeServer()
            .setAllowedFileExtensions(allowedFileExtensions)
            .saveRunViaDBusTo(runViaDBus)
            .setExecFlag(synfs::constants::DEFAULT_EXEC_FLAG)
            .saveResultsTo(receivedFiles)
            .build();

    // Если при запуске файла был указан `synfs::constants::DEFAULT_EXEC_FLAG`
    // (или другой выбранный нами флаг), то это значит, что сервер был запущен
    // силами DBus демона и должен принять файлы.
    server->run(argc, argv);

    if (runViaDBus) {
        // Сервер был запущен через DBus. Распечатаем полученные файлы.
        for (const std::string &item: *receivedFiles) {
            std::cout << item;
            if (&item != &receivedFiles->back()) {
                std::cout << ", ";
            }
        }
        std::cout << '\n' << "СЕРВЕР: Я был запущен через DBus!" << '\n';
    } else {
        // Сервер не был запущен через DBus.
        std::cout << '\n' << "СЕРВЕР: Я был запущен вне DBus!" << '\n';
        std::cout << "СЕРВЕР: Чтобы запустить меня так, как будто бы меня вызвал DBus, "
                     "добавьте флаг --launched-via-dbus" << '\n';
    }
}
