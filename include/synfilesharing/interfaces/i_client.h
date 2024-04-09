#ifndef SYNFILESHARING_I_CLIENT_H
#define SYNFILESHARING_I_CLIENT_H

#include <vector>
#include <string>

namespace synfs {
    class IClient {
    public:
        /**
         * Данный метод отправляет файлы на указанный сервер. Если конфигурация сервера
         * не разрешает некоторые из переданных файлов, то будет получена ошибка.
         * */
        virtual void sendFiles(std::string serverName, std::vector<std::string> filePaths) = 0;
    };
};

#endif //SYNFILESHARING_I_CLIENT_H
