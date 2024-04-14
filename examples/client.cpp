#include <iostream>
#include "synfilesharing/synfilesharing.h"

int main() {
    // В README.md мы создаём файлы "~/text_file.txt" и "~/markdown_file.md".
    // Поскольку метод `sendFiles` требует абсолютного пути до файла
    // мы конвертируем "~" в "/home/<user>".
    std::string pathToHome = std::getenv("HOME");
    std::vector<std::string> paths = {
            pathToHome + "/text_file.txt",
            pathToHome + "/markdown_file.md"
    };

    // Создаём клиент и отправляем файлы.
    std::unique_ptr<synfs::IClient> client = synfs::makeClient().build();
    client->sendFiles(paths);

    std::cout << "КЛИЕНТ: Файлы успешно отправлены!" << '\n';
}
