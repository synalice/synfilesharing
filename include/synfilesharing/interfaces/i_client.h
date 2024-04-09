#ifndef SYNFILESHARING_I_CLIENT_H
#define SYNFILESHARING_I_CLIENT_H

#include <vector>
#include <string>

namespace synfs {
    class IClient {
    public:
        /**
         * Отправляет выбранные файлы на указанный в `destination` сервер.
         * Получает ошибку, если указанные файлы не разрешены сервером.
         * */
        virtual void sendFiles(std::string destination, std::vector<std::string> filePaths) = 0;

        virtual ~IClient() = default;
    };
}


#endif //SYNFILESHARING_I_CLIENT_H
